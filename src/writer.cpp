#include "writer.hpp"

static int Writer_finalize(Writer* self) {
    if(self->writer) {
        delete self->writer;
        self->writer = NULL;
    }
    if(self->writerFormat) {
        Py_DECREF(self->writerFormat);
        self->writerFormat = NULL;
    }
    return 0;
}

static PyType_Slot WriterSlots[] = {
    {Py_tp_finalize, (void*) Writer_finalize},
    {0, 0}
};

PyType_Spec WriterSpec {
    "pycsdr.modules.Writer",
    sizeof(Writer),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_FINALIZE,
    WriterSlots
};