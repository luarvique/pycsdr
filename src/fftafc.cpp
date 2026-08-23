#include "fftafc.hpp"
#include "types.hpp"

#include <csdr/fftafc.hpp>

static int FftAfc_init(FftAfc* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char *)"updatePeriod",
        (char *)"samplePeriod",
        NULL
    };

    unsigned int updatePeriod = 4;
    unsigned int samplePeriod = 1;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|II", kwlist, &updatePeriod, &samplePeriod)) {
        return -1;
    }

    self->setModule(new Csdr::FftAfc(updatePeriod, samplePeriod));

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
    self->outputFormat = FORMAT_COMPLEX_FLOAT;

    return 0;
}

static PyType_Slot FftAfcSlots[] = {
    {Py_tp_init, (void*) FftAfc_init},
    {0, 0}
};

PyType_Spec FftAfcSpec = {
    "pycsdr.modules.FftAfc",
    sizeof(FftAfc),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    FftAfcSlots
};

