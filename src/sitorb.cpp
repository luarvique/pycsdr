#include "sitorb.hpp"
#include "types.hpp"

#include <csdr/sitorb.hpp>

static int SitorBDecoder_init(SitorBDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "jitter",
        (char*) "allowErrors",
        (char*) "invert",
        NULL
    };

    int jitter = 1;
    int allowErrors = 16;
    int invert = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|IIp", kwlist, &jitter, &allowErrors, &invert)) {
        return -1;
    }

    // Make sure provided jitter value makes sense
    jitter = jitter<0? 0 : jitter>6? 6 : jitter;

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::SitorBDecoder(jitter, allowErrors, (bool) invert));

    return 0;
}

static PyType_Slot SitorBDecoderSlots[] = {
    {Py_tp_init, (void*) SitorBDecoder_init},
    {0, 0}
};

PyType_Spec SitorBDecoderSpec = {
    "pycsdr.modules.SitorBDecoder",
    sizeof(SitorBDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    SitorBDecoderSlots
};