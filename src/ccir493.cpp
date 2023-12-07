#include "ccir493.hpp"
#include "types.hpp"

#include <csdr/ccir493.hpp>

static int Ccir493Decoder_init(Ccir493Decoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "fec",
        (char*) "invert",
        NULL
    };

    int invert = false;
    int fec = true;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|pp", kwlist, &fec, &invert)) {
        return -1;
    }

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::Ccir493Decoder((bool) fec, (bool) invert));

    return 0;
}

static PyType_Slot Ccir493DecoderSlots[] = {
        {Py_tp_init, (void*) Ccir493Decoder_init},
        {0, 0}
};

PyType_Spec Ccir493DecoderSpec = {
        "pycsdr.modules.Ccir493Decoder",
        sizeof(Ccir493Decoder),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
        Ccir493DecoderSlots
};
