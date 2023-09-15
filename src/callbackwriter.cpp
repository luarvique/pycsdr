#include "callbackwriter.hpp"
#include "types.hpp"


static int CallbackWriter_init(CallbackWriter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "format", NULL};

    if (self->writer) {
        delete self->writer;
        self->writer = NULL;
    }

    if (self->writerFormat) {
        Py_DECREF(self->writerFormat);
        self->writerFormat = NULL;
    }

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist, FORMAT_TYPE, &self->writerFormat)) {
        return -1;
    }

    if (self->writerFormat == FORMAT_CHAR) {
        self->writer = new ProxyWriter<unsigned char>(self);
    } else if (self->writerFormat == FORMAT_COMPLEX_FLOAT) {
        self->writer = new ProxyWriter<Csdr::complex<float>>(self);
    } else if (self->writerFormat == FORMAT_COMPLEX_SHORT) {
        self->writer = new ProxyWriter<Csdr::complex<short>>(self);
    } else if (self->writerFormat == FORMAT_FLOAT) {
        self->writer = new ProxyWriter<float>(self);
    } else if (self->writerFormat == FORMAT_SHORT) {
        self->writer = new ProxyWriter<short>(self);
    } else {
        Py_DECREF(self->writerFormat);
        PyErr_SetString(PyExc_ValueError, "unsupported writer format");
        self->writerFormat = NULL;
        return -1;
    }

    return 0;
}

static PyObject* CallbackWriter_write(CallbackWriter* self, PyObject* args, PyObject* kwds) {
    // this is a NOOP, intended to be overridden

    Py_RETURN_NONE;
}

static PyMethodDef CallbackWriter_methods[] = {
    {"write", (PyCFunction) CallbackWriter_write, METH_VARARGS | METH_KEYWORDS,
     "abstract method"
    },
    {NULL}  /* Sentinel */
};

static PyType_Slot CallbackWriterSlots[] = {
    {Py_tp_init, (void*) CallbackWriter_init},
    {Py_tp_methods, CallbackWriter_methods},
    {0, 0}
};

PyType_Spec CallbackWriterSpec = {
    "pycsdr.modules.CallbackWriter",
    sizeof(CallbackWriter),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_FINALIZE,
    CallbackWriterSlots
};

template <typename T>
ProxyWriter<T>::ProxyWriter(CallbackWriter* writer):
    Csdr::Writer<T>(),
    writer(writer)
{
    buffer = (T*) malloc(sizeof(T) * bufferSize);
}

template <typename T>
ProxyWriter<T>::~ProxyWriter() {
    if(buffer) { free(buffer);buffer=NULL; }
}

template <typename T>
size_t ProxyWriter<T>::writeable() {
    return buffer? bufferSize : 0;
}

template <typename T>
T* ProxyWriter<T>::getWritePointer() {
    return buffer;
}

template <typename T>
void ProxyWriter<T>::advance(size_t how_much) {
    // must have buffer
    if (buffer == NULL) return;

    // do not exceed buffer size
    if (how_much > bufferSize) how_much = bufferSize;

    // acquire GIL
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    PyObject* bytes = PyMemoryView_FromMemory((char*) buffer, how_much * sizeof(T), PyBUF_READ);
    // if bytes is NULL, that actually represents an error. unfortunately, we cannot report that anywhere...
    if (bytes != NULL) {
        PyObject* result = PyObject_CallMethod((PyObject*) writer, "write", "O", bytes);
        Py_DECREF(bytes);
        // not interested in the result
        if (result != NULL) Py_DECREF(result);
    }

    /* Release the thread. No Python API allowed beyond this point. */
    PyGILState_Release(gstate);
}