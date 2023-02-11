#include "sstvdecoder.hpp"
#include "types.hpp"

#include <csdr/sstv.hpp>
#include <csdr/complex.hpp>

static int SstvDecoder_init(SstvDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        NULL
    };

    unsigned int sampleRate  = 44100;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &sampleRate)) {
        return -1;
    }

    self->setModule(new Csdr::SstvDecoder<Csdr::complex<float>>(sampleRate));

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
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
