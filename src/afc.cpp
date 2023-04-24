#include "afc.hpp"
#include "types.hpp"

#include <csdr/afc.hpp>

static int Afc_init(Convert* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"sampleRate",
        (char *)"bandwidth",
        (char *)"syncWidth",
        NULL
    };

    unsigned int sampleRate = 22050;
    unsigned int bandwidth  = 8000;
    unsigned int syncWidth  = 200;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I|III", kwlist, &sampleRate, &bandiwdth, &syncWidth)) {
        return -1;
    }

    self->setModule(new Csdr::Afc(sampleRate, bandwidth, syncWidth));

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
    self->outputFormat = FORMAT_COMPLEX_FLOAT;

    return 0;
}

static PyType_Slot AfcSlots[] = {
    {Py_tp_init, (void*) Afc_init},
    {0, 0}
};

PyType_Spec AfcSpec = {
    "pycsdr.modules.Afc",
    sizeof(Afc),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    AfcSlots
};

