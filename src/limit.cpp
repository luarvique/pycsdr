#include "limit.hpp"
#include "types.hpp"

#include <csdr/limit.hpp>
#include <csdr/window.hpp>

static int Limit_init(Limit* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "format", (char*) "maxAmplitude", NULL};

    float maxAmplitude = 1.0f;
    PyObject* format;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!|f", kwlist, FORMAT_TYPE, &format, &maxAmplitude)) {
        return -1;
    }

    if (format == FORMAT_FLOAT) {
        self->setModule(new Csdr::Limit<float>(maxAmplitude));
    } else if (format == FORMAT_COMPLEX_FLOAT) {
        self->setModule(new Csdr::Limit<Csdr::complex<float>>(maxAmplitude));
    } else {
        PyErr_SetString(PyExc_ValueError, "unsupported limit format");
        return -1;
    }

    Py_INCREF(format);
    self->inputFormat = format;
    Py_INCREF(format);
    self->outputFormat = format;

    return 0;
}

static PyType_Slot LimitSlots[] = {
    {Py_tp_init, (void*) Limit_init},
    {0, 0}
};

PyType_Spec LimitSpec = {
    "pycsdr.modules.Limit",
    sizeof(Limit),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    LimitSlots
};
