#include "throttle.hpp"
#include "types.hpp"

#include <csdr/throttle.hpp>

static int Throttle_init(Throttle* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "format", (char*) "rate", (char*) "chunkSize", NULL};

    size_t rate = 0;
    size_t chunkSize = 8096;
    PyObject* format;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!n|n", kwlist, FORMAT_TYPE, &format, &rate, &chunkSize)) {
        return -1;
    }

    if (format == FORMAT_SHORT) {
        self->setModule(new Csdr::Throttle<short>(rate, chunkSize));
    } else if (format == FORMAT_FLOAT) {
        self->setModule(new Csdr::Throttle<float>(rate, chunkSize));
    } else {
        PyErr_SetString(PyExc_ValueError, "unsupported throttle format");
        return -1;
    }

    Py_INCREF(format);
    self->inputFormat = format;
    Py_INCREF(format);
    self->outputFormat = format;

    return 0;
}

static PyType_Slot ThrottleSlots[] = {
    {Py_tp_init, (void*) Throttle_init},
    {0, 0}
};

PyType_Spec ThrottleSpec = {
    "pycsdr.modules.Throttle",
    sizeof(Throttle),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    ThrottleSlots
};
