#include "sstv.hpp"
#include "types.hpp"

#include <csdr/sstv.hpp>
#include <csdr/complex.hpp>

static int SstvDecoder_init(SstvDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"dbgTime",
        (char *)"preferScottieDX",
        NULL
    };

    unsigned int sampleRate = 44100;
    unsigned int dbgTime = 0;
    unsigned int preferSDX = 0;
    unsigned int options = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|Ip", kwlist, &sampleRate, &dbgTime, &preferSDX)) {
        return -1;
    }

    options = (preferSDX? Csdr::SstvDecoder<float>::OPT_VIS63_SCOTTIEDX : 0);

    self->setModule(new Csdr::SstvDecoder<float>(sampleRate, options, dbgTime));

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
