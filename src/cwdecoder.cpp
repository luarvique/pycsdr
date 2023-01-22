#include "cwdecoder.hpp"
#include "types.hpp"

#include <csdr/cw.hpp>

static int CwDecoder_init(CwDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"targetFreq",
        (char *)"targetWidth",
        NULL
    };

    unsigned int sampleRate  = 8000;
    unsigned int targetFreq  = 800;
    unsigned int targetWidth = 100;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|II", kwlist, &sampleRate, &targetFreq, &targetWidth)) {
        return -1;
    }

    self->setModule(new Csdr::CwDecoder(sampleRate, targetFreq, targetWidth));

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;

    return 0;
}

static PyType_Slot CwDecoderSlots[] = {
    {Py_tp_init, (void*) CwDecoder_init},
    {0, 0}
};

PyType_Spec CwDecoderSpec = {
    "pycsdr.modules.CwDecoder",
    sizeof(CwDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    CwDecoderSlots
};
