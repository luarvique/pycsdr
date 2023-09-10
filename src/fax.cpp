#include "fax.hpp"
#include "types.hpp"

#include <csdr/fax.hpp>
#include <csdr/complex.hpp>

static int FaxDecoder_init(FaxDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"lpm",
        (char *)"dbgTime",
        (char *)"postProcess",
        (char *)"color",
        (char *)"am",
        NULL
    };

    unsigned int sampleRate  = 44100;
    unsigned int lpm         = 120;
    unsigned int postProcess = 0;
    unsigned int colorMode   = 0;
    unsigned int amMode      = 0;
    unsigned int dbgTime     = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|IIppp", kwlist, &sampleRate, &lpm, &dbgTime, &postProcess, &colorMode, &amMode)) {
        return -1;
    }

    unsigned int options =
        (postProcess? Csdr::FaxDecoder<float>::OPT_POST  : 0) |
        (colorMode?   Csdr::FaxDecoder<float>::OPT_COLOR : 0) |
        (amMode?      Csdr::FaxDecoder<float>::OPT_AM    : 0);

    self->setModule(new Csdr::FaxDecoder<float>(sampleRate, lpm, options, dbgTime));

    self->inputFormat = FORMAT_FLOAT;
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
