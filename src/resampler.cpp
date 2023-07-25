#include "resampler.hpp"
#include "types.hpp"
#include <csdr/resampler.hpp>

static int Resampler_init(Resampler* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "inputRate", (char*) "outputRate", NULL};

    unsigned int inputRate = 0;
    unsigned int outputRate = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "II", kwlist, &inputRate, &outputRate)) {
        return -1;
    }

    self->inputFormat = FORMAT_COMPLEX_FLOAT;
    self->outputFormat = FORMAT_COMPLEX_FLOAT;
    self->setModule(new Csdr::Resampler(inputRate, outputRate));

    return 0;
}

static PyType_Slot ResamplerSlots[] = {
        {Py_tp_init, (void*) Resampler_init},
        {0, 0}
};

PyType_Spec ResamplerSpec = {
        "pycsdr.modules.Resampler",
        sizeof(Resampler),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
        ResamplerSlots
};
