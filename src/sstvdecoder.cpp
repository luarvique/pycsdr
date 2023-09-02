#include "sstvdecoder.hpp"
#include "types.hpp"

#include <csdr/sstv.hpp>
#include <csdr/complex.hpp>

static int SstvDecoder_init(SstvDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"dbgTime",
        NULL
    };

    unsigned int sampleRate = 44100;
    unsigned int dbgTime    = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|I", kwlist, &sampleRate, &dbgTime)) {
        return -1;
    }

    self->setModule(new Csdr::SstvDecoder<float>(sampleRate, dbgTime));

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;

    return 0;
}

static PyType_Slot SstvDecoderSlots[] = {
    {Py_tp_init, (void*) SstvDecoder_init},
    {0, 0}
};

PyType_Spec SstvDecoderSpec = {
    "pycsdr.modules.SstvDecoder",
    sizeof(SstvDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    SstvDecoderSlots
};
