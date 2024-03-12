#include "ccir493.hpp"
#include "types.hpp"

#include <csdr/ccir493.hpp>

static int Ccir493Decoder_init(Ccir493Decoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "allowErrors",
        (char*) "invert",
        NULL
    };

    int allowErrors = 4;
    int invert = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|Ip", kwlist, &allowErrors, &invert)) {
        return -1;
    }

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::Ccir493Decoder(allowErrors, (bool) invert));

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
