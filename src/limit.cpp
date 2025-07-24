#include "limit.hpp"
#include "types.hpp"

#include <csdr/limit.hpp>
#include <csdr/window.hpp>

static int Limit_init(Limit* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "format", (char*) "maxAmplitude", NULL};

    float maxAmplitude = 1.0f;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O!f", kwlist, FORMAT_TYPE, &self->inputFormat, &maxAmplitude)) {
        return -1;
    }

    self->outputFormat = self->inputFormat;

    if (self->inputFormat == FORMAT_FLOAT) {
        self->setModule(new Csdr::Limit<float>(maxAmplitude));
    } else if (self->inputFormat == FORMAT_SHORT) {
        self->setModule(new Csdr::Limit<short>(maxAmplitude));
    } else if (self->inputFormat == FORMAT_COMPLEX_FLOAT) {
        self->setModule(new Csdr::Limit<complex<float>>(maxAmplitude));
    } else if (self->inputFormat == FORMAT_COMPLEX_SHORT) {
        self->setModule(new Csdr::Limit<complex<short>>(maxAmplitude));
    } else {
        PyErr_SetString(PyExc_ValueError, "unsupported format");
        return -1;
    }

    Py_INCREF(self->inputFormat);
    Py_INCREF(self->outputFormat);

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
