#include "cwdecoder.hpp"
#include "types.hpp"

#include <csdr/cw.hpp>

static int CwDecoder_init(CwDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "sampleRate", NULL};

    unsigned int sampleRate = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &sampleRate)) {
        return -1;
    }

    self->setModule(new Csdr::CwDecoder(sampleRate));

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
