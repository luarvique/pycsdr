#include "jkrtty.hpp"
#include "types.hpp"

#include <csdr/jkrtty.hpp>

static int JKRttyDecoder_init(JKRttyDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "invert", NULL};

    int invert = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|p", kwlist, &invert)) {
        return -1;
    }

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::JKRttyDecoder((bool) invert));

    return 0;
}

static PyType_Slot JKRttyDecoderSlots[] = {
    {Py_tp_init, (void*) JKRttyDecoder_init},
    {0, 0}
};

PyType_Spec JKRttyDecoderSpec = {
    "pycsdr.modules.JKRttyDecoder",
    sizeof(JKRttyDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    JKRttyDecoderSlots
};
