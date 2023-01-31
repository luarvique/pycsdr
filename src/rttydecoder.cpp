#include "rttydecoder.hpp"
#include "types.hpp"

#include <csdr/rtty.hpp>

static int RttyDecoder_init(RttyDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"targetFreq",
        (char *)"targetWidth",
        (char *)"baudRate",
        (char *)"reverse",
        NULL
    };

    unsigned int sampleRate  = 8000;
    unsigned int targetFreq  = 450;
    unsigned int targetWidth = 170;
    double baudRate = 45.45;
    bool reverse = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|IIdp", kwlist, &sampleRate, &targetFreq, &targetWidth, &baudRate, &reverse)) {
        return -1;
    }

    self->setModule(new Csdr::RttyDecoder(sampleRate, targetFreq, targetWidth, baudRate, reverse));

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;

    return 0;
}

static PyType_Slot RttyDecoderSlots[] = {
    {Py_tp_init, (void*) RttyDecoder_init},
    {0, 0}
};

PyType_Spec RttyDecoderSpec = {
    "pycsdr.modules.RttyDecoder",
    sizeof(RttyDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    RttyDecoderSlots
};
