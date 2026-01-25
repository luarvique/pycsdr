#include "fmstereo.hpp"
#include "types.hpp"

#include <csdr/fmstereo.hpp>
#include <csdr/window.hpp>

template <typename T>
static void setupStereoDecimator(StereoFractionalDecimator* self, float rateMPX, float decimation, float tau, unsigned int numPolyPoints, bool prefilter) {
    Csdr::LowPassFilter<T>* filter = nullptr;
    if (prefilter) {
        auto w = new Csdr::HammingWindow();
        float transition = 0.06f;
        filter = new Csdr::LowPassFilter<T>(0.5 / (decimation - transition), transition, w);
    }
    self->setModule(new Csdr::StereoFractionalDecimator<T>(rateMPX, decimation, tau, numPolyPoints, filter));
}

static int StereoFractionalDecimator_init(StereoFractionalDecimator* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "format",
        (char*) "rateMPX",
        (char*) "decimation",
        (char*) "tau",
        (char*) "numPolyPoints",
        (char*) "prefilter", NULL};

    PyObject* format;
    float rateMPX = 0.0f;
    float decimation = 0.0f;
    float tau = 50e-6f;
    unsigned int numPolyPoints = 12;
    int prefilter = false;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!fff|Ip", kwlist, FORMAT_TYPE, &format, &rateMPX, &decimation, &tau, &numPolyPoints, &prefilter)) {
        return -1;
    }

    if (format == FORMAT_FLOAT) {
        setupStereoDecimator<float>(self, rateMPX, decimation, tau, numPolyPoints, prefilter);
    } else {
        PyErr_SetString(PyExc_ValueError, "unsupported stereo fractional decimator format");
        return -1;
    }

    Py_INCREF(format);
    self->inputFormat = format;
    Py_INCREF(format);
    self->outputFormat = format;

    return 0;
}

static PyType_Slot StereoFractionalDecimatorSlots[] = {
    {Py_tp_init, (void*) StereoFractionalDecimator_init},
    {0, 0}
};

PyType_Spec StereoFractionalDecimatorSpec = {
    "pycsdr.modules.StereoFractionalDecimator",
    sizeof(StereoFractionalDecimator),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    StereoFractionalDecimatorSlots
};