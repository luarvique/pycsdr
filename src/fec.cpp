#include "fec.hpp"
#include "types.hpp"

#include <csdr/fec.hpp>

static int FecDecoder_init(FecDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"size",
        NULL
    };

    unsigned int fecSize = 5;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|I", kwlist, &fecSize)) {
        return -1;
    }

    self->inputFormat = FORMAT_CHAR;
    self->outputFormat = FORMAT_CHAR;
    self->setModule(new Csdr::FecDecoder(fecSize));

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
