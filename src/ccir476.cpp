#include "ccir476.hpp"
#include "types.hpp"

#include <csdr/ccir476.hpp>

static int Ccir476Decoder_init(Ccir476Decoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "fec",
        (char*) "strict",
        NULL
    };

    int fec = true;
    int strict = true;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|pp", kwlist, &fec, &strict)) {
        return -1;
    }

    self->inputFormat = FORMAT_CHAR;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::Ccir476Decoder((bool) fec, (bool) strict));

    return 0;
}

static PyType_Slot Ccir476DecoderSlots[] = {
        {Py_tp_init, (void*) Ccir476Decoder_init},
        {0, 0}
};

PyType_Spec Ccir476DecoderSpec = {
        "pycsdr.modules.Ccir476Decoder",
        sizeof(Ccir476Decoder),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
        Ccir476DecoderSlots
};
