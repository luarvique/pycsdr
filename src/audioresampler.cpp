#include "audioresampler.hpp"
#include "types.hpp"
#include <csdr/audioresampler.hpp>

static int AudioResampler_init(AudioResampler* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "inputRate", (char*) "outputRate", (char*) "format", NULL};

    unsigned int inputRate = 0;
    unsigned int outputRate = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "II|O!", kwlist, &inputRate, &outputRate, FORMAT_TYPE, &self->inputFormat)) {
        return -1;
    }

    self->outputFormat = self->inputFormat;

    if (self->inputFormat == FORMAT_FLOAT) {
        self->setModule(new Csdr::AudioResampler<float>(inputRate, outputRate));
    } else if (self->inputFormat == FORMAT_SHORT) {
        self->setModule(new Csdr::AudioResampler<short>(inputRate, outputRate));
    } else if (self->inputFormat == FORMAT_COMPLEX_FLOAT) {
        self->setModule(new Csdr::AudioResampler<complex<float>>(inputRate, outputRate));
    } else if (self->inputFormat == FORMAT_COMPLEX_SHORT) {
        self->setModule(new Csdr::AudioResampler<complex<short>>(inputRate, outputRate));
    } else {
        PyErr_SetString(PyExc_ValueError, "unsupported format");
        return -1;
    }

    Py_INCREF(self->inputFormat);
    Py_INCREF(self->outputFormat);

    return 0;
}

static PyType_Slot AudioResamplerSlots[] = {
        {Py_tp_init, (void*) AudioResampler_init},
        {0, 0}
};

PyType_Spec AudioResamplerSpec = {
        "pycsdr.modules.AudioResampler",
        sizeof(AudioResampler),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
        AudioResamplerSlots
};
