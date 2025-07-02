#include "noisefilter.hpp"
#include "types.hpp"

#include <csdr/filter.hpp>
#include <csdr/noisefilter.hpp>

static int NoiseFilter_init(NoiseFilter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*)"threshold", (char*)"fftSize", (char*)"wndSize",
        (char*)"decay", (char*)"attack", NULL
    };

    self->threshold = 0;
    self->fftSize = 1024;
    self->wndSize = 16;
    self->attack  = 2;
    self->decay   = 10;
    self->noiseFilter = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iIIII", kwlist, &self->threshold, &self->fftSize, &self->wndSize, &self->decay, &self->attack)) {
        return -1;
    }

    self->noiseFilter = new Csdr::AFNoiseFilter(self->fftSize, self->wndSize, self->decay, self->attack);
    self->setModule(new Csdr::FilterModule<float>(self->noiseFilter));
    self->noiseFilter->setThreshold(self->threshold);

    Py_INCREF(FORMAT_FLOAT);
    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_FLOAT;

    return 0;
}

static PyObject* NoiseFilter_setThreshold(NoiseFilter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { (char*)"threshold", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &self->threshold)) {
        return NULL;
    }

    if (self->noiseFilter) {
        self->noiseFilter->setThreshold(self->threshold);
    }

    Py_RETURN_NONE;
}

static PyObject* NoiseFilter_setWndSize(NoiseFilter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { (char*)"wndSize", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &self->wndSize)) {
        return NULL;
    }

    self->noiseFilter = new Csdr::AFNoiseFilter(self->fftSize, self->wndSize, self->decay, self->attack);
    dynamic_cast<Csdr::FilterModule<float>*>(self->module)->setFilter(self->noiseFilter);
    self->noiseFilter->setThreshold(self->threshold);

    Py_RETURN_NONE;
}

static PyObject* NoiseFilter_setFftSize(NoiseFilter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { (char*)"fftSize", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &self->fftSize)) {
        return NULL;
    }

    self->noiseFilter = new Csdr::AFNoiseFilter(self->fftSize, self->wndSize, self->decay, self->attack);
    dynamic_cast<Csdr::FilterModule<float>*>(self->module)->setFilter(self->noiseFilter);
    self->noiseFilter->setThreshold(self->threshold);

    Py_RETURN_NONE;
}

static PyObject* NoiseFilter_setDecay(NoiseFilter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { (char*)"decay", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &self->decay)) {
        return NULL;
    }

    self->noiseFilter = new Csdr::AFNoiseFilter(self->fftSize, self->wndSize, self->decay, self->attack);
    dynamic_cast<Csdr::FilterModule<float>*>(self->module)->setFilter(self->noiseFilter);
    self->noiseFilter->setThreshold(self->threshold);

    Py_RETURN_NONE;
}

static PyObject* NoiseFilter_setAttack(NoiseFilter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { (char*)"attack", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &self->attack)) {
        return NULL;
    }

    self->noiseFilter = new Csdr::AFNoiseFilter(self->fftSize, self->wndSize, self->decay, self->attack);
    dynamic_cast<Csdr::FilterModule<float>*>(self->module)->setFilter(self->noiseFilter);
    self->noiseFilter->setThreshold(self->threshold);

    Py_RETURN_NONE;
}

static PyMethodDef NoiseFilter_methods[] = {
    { "setThreshold", (PyCFunction) NoiseFilter_setThreshold, METH_VARARGS | METH_KEYWORDS, "set filtering threshold in dB" },
    { "setWndSize", (PyCFunction) NoiseFilter_setWndSize, METH_VARARGS | METH_KEYWORDS, "set window size in buckets" },
    { "setFftSize", (PyCFunction) NoiseFilter_setFftSize, METH_VARARGS | METH_KEYWORDS, "set FFT size in buckets" },
    { "setAttack", (PyCFunction) NoiseFilter_setAttack, METH_VARARGS | METH_KEYWORDS, "set filter attack rate in FFTs" },
    { "setDecay", (PyCFunction) NoiseFilter_setDecay, METH_VARARGS | METH_KEYWORDS, "set filter decay rate in FFTs" },
    { NULL }  /* Sentinel */
};

static PyType_Slot NoiseFilterSlots[] = {
    { Py_tp_init, (void*) NoiseFilter_init },
    { Py_tp_methods, NoiseFilter_methods },
    { 0, 0 }
};

PyType_Spec NoiseFilterSpec = {
    "pycsdr.modules.NoiseFilter",
    sizeof(NoiseFilter),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    NoiseFilterSlots
};
