#include "cw.hpp"
#include "types.hpp"

#include <csdr/cw.hpp>
#include <csdr/complex.hpp>

static int CwDecoder_init(CwDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"showCw",
        NULL
    };

    unsigned int sampleRate = 8000;
    int showCw = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|p", kwlist, &sampleRate, &showCw)) {
        return -1;
    }

    self->setModule(new Csdr::CwDecoder<Csdr::complex<float>>(sampleRate, (bool) showCw));

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
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
