#include "audioresampler.hpp"
#include "types.hpp"
#include <csdr/audioresampler.hpp>

static int AudioResampler_init(AudioResampler* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "format", (char*) "inputRate", (char*) "outputRate", NULL};

    unsigned int inputRate = 0;
    unsigned int outputRate = 0;
    PyObject* format;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!II", kwlist, FORMAT_TYPE, &format, &inputRate, &outputRate)) {
        return -1;
    }

    if (format == FORMAT_COMPLEX_FLOAT) {
        self->setModule(new Csdr::AudioResampler<complex<float>>(inputRate, outputRate));
    } else if (format == FORMAT_FLOAT) {
        self->setModule(new Csdr::AudioResampler<float>(inputRate, outputRate));
    } else {
        PyErr_SetString(PyExc_ValueError, "unsupported resampler format");
        return -1;
    }

    Py_INCREF(format);
    self->inputFormat = format;
    Py_INCREF(format);
    self->outputFormat = format;

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
