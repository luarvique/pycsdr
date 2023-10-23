#include "sitor.hpp"
#include "types.hpp"

#include <csdr/sitor.hpp>

static int SitorDecoder_init(SitorDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "invert", NULL};

    int invert = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|p", kwlist, &invert)) {
        return -1;
    }

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::SitorDecoder((bool) invert));

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
