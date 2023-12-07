#include "dsc.hpp"
#include "types.hpp"

#include <csdr/dsc.hpp>

static int DscDecoder_init(DscDecoder* self, PyObject* args, PyObject* kwds) {
    self->inputFormat = FORMAT_CHAR;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::DscDecoder());

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
