#include "dsc.hpp"
#include "types.hpp"

#include <csdr/dsc.hpp>

static int DscDecoder_init(DscDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "invert",
        NULL
    };

    int invert = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|p", kwlist, &invert)) {
        return -1;
    }

    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_SHORT;
    self->setModule(new Csdr::DscDecoder((bool) invert));

    return 0;
}

static PyType_Slot DscDecoderSlots[] = {
    {Py_tp_init, (void*) DscDecoder_init},
    {0, 0}
};

PyType_Spec DscDecoderSpec = {
    "pycsdr.modules.DscDecoder",
    sizeof(DscDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    DscDecoderSlots
};
