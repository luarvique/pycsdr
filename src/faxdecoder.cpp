#include "faxdecoder.hpp"
#include "types.hpp"

#include <csdr/fax.hpp>
#include <csdr/complex.hpp>

static int FaxDecoder_init(FaxDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"lpm",
        (char *)"dbgTime",
        NULL
    };

    unsigned int sampleRate = 44100;
    unsigned int lpm        = 120;
    unsigned int dbgTime    = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|II", kwlist, &sampleRate, &lpm, &dbgTime)) {
        return -1;
    }

    self->setModule(new Csdr::FaxDecoder<Csdr::complex<float>>(sampleRate, lpm, 0, dbgTime));

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
    self->outputFormat = FORMAT_CHAR;

    return 0;
}

static PyType_Slot FaxDecoderSlots[] = {
    {Py_tp_init, (void*) FaxDecoder_init},
    {0, 0}
};

PyType_Spec FaxDecoderSpec = {
    "pycsdr.modules.FaxDecoder",
    sizeof(FaxDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    FaxDecoderSlots
};
