#include "adpcmencoder.hpp"
#include "types.hpp"
#include <csdr/adpcm.hpp>

static int AdpcmEncoder_init(AdpcmEncoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "format", (char*) "sync", NULL};

    PyObject* format;
    int sync = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!|b", kwlist, FORMAT_TYPE, &format, &sync)) {
        return -1;
    }

    if (format == FORMAT_SHORT) {
        self->setModule(new Csdr::AdpcmEncoder(sync));
    } else if (format == FORMAT_COMPLEX_SHORT) {
        self->setModule(new Csdr::StereoAdpcmEncoder(sync));
    } else {
        PyErr_SetString(PyExc_ValueError, "unsupported adpcm format");
        return -1;
    }

    Py_INCREF(format);
    self->inputFormat = format;
    self->outputFormat = FORMAT_CHAR;

    return 0;
}

static PyType_Slot AdpcmEncoderSlots[] = {
    {Py_tp_init, (void*) AdpcmEncoder_init},
    {0, 0}
};

PyType_Spec AdpcmEncoderSpec = {
    "pycsdr.modules.AdpcmEncoder",
    sizeof(AdpcmEncoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    AdpcmEncoderSlots
};
