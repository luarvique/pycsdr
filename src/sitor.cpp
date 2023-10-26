#include "sitor.hpp"
#include "types.hpp"

#include <csdr/sitor.hpp>

static int SitorDecoder_init(SitorDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "jitter",
        (char*) "invert",
        NULL
    };

    int jitter = 1;
    int invert = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|Ip", kwlist, &jitter, &invert)) {
        return -1;
    }

    // Make sure provided jitter value makes sense
    jitter = jitter<0? 0 : jitter>6? 6 : jitter;

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::SitorDecoder((unsigned char) jitter, (bool) invert));

    return 0;
}

static PyType_Slot SitorDecoderSlots[] = {
    {Py_tp_init, (void*) SitorDecoder_init},
    {0, 0}
};

PyType_Spec SitorDecoderSpec = {
    "pycsdr.modules.SitorDecoder",
    sizeof(SitorDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    SitorDecoderSlots
};
