#include "afc.hpp"
#include "types.hpp"

#include <csdr/afc.hpp>

static int Afc_init(Afc* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"updatePeriod",
        NULL
    };

    unsigned int updatePeriod = 4;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|I", kwlist, &updatePeriod)) {
        return -1;
    }

    self->setModule(new Csdr::Afc(updatePeriod));

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

