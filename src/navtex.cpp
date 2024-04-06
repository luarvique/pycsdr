#include "navtex.hpp"
#include "types.hpp"

#include <csdr/navtex.hpp>

static int NavtexDecoder_init(NavtexDecoder* self, PyObject* args, PyObject* kwds) {
    self->inputFormat = FORMAT_CHAR;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::NavtexDecoder());

    return 0;
}

static PyType_Slot NavtexDecoderSlots[] = {
        {Py_tp_init, (void*) NavtexDecoder_init},
        {0, 0}
};

PyType_Spec NavtexDecoderSpec = {
        "pycsdr.modules.NavtexDecoder",
        sizeof(NavtexDecoder),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
        NavtexDecoderSlots
};
