#include "afcpll.hpp"
#include "types.hpp"

#include <csdr/afcpll.hpp>

static int AfcPll_init(AfcPll* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate", (char *)"bandwidth", (char *)"dumpingFactor", NULL
    };

    float sampleRate = 12000;
    float bandwidth  = 100.0f;
    float dumpingFactor = 0.3f;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|fff", kwlist, &sampleRate, &bandwidth, &dumpingFactor)) {
        return -1;
    }

    self->setModule(new Csdr::AfcPll(sampleRate, bandwidth, dumpingFactor));

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
    self->outputFormat = FORMAT_COMPLEX_FLOAT;

    return 0;
}

static PyType_Slot AfcPllSlots[] = {
    {Py_tp_init, (void*) AfcPll_init},
    {0, 0}
};

PyType_Spec AfcPllSpec = {
    "pycsdr.modules.AfcPll",
    sizeof(AfcPll),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    AfcPllSlots
};

