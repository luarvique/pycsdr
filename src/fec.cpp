#include "fec.hpp"
#include "types.hpp"

#include <csdr/fec.hpp>

static int FecDecoder_init(FecDecoder* self, PyObject* args, PyObject* kwds) {
    self->inputFormat = FORMAT_CHAR;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::FecDecoder());

    return 0;
}

static PyType_Slot FecDecoderSlots[] = {
        {Py_tp_init, (void*) FecDecoder_init},
        {0, 0}
};

PyType_Spec FecDecoderSpec = {
        "pycsdr.modules.FecDecoder",
        sizeof(FecDecoder),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
        FecDecoderSlots
};
