#include "noiseblanker.hpp"
#include "types.hpp"

#include <csdr/filter.hpp>
#include <csdr/noiseblanker.hpp>

static int NoiseBlanker_init(NoiseBlanker* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*)"threshold1", (char*)"threshold2", NULL
    };

    self->threshold1 = 10;
    self->threshold2 = 8;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ii", kwlist, &self->threshold1, &self->threshold2)) {
        return -1;
    }

    Csdr::Filter<Csdr::complex<float>>* filter =
        new Csdr::RFNoiseBlanker(self->threshold1, self->threshold2);

    self->setModule(new Csdr::FilterModule<Csdr::complex<float>>(filter));

    Py_INCREF(FORMAT_COMPLEX_FLOAT);
    self->inputFormat = FORMAT_COMPLEX_FLOAT;
    self->outputFormat = FORMAT_COMPLEX_FLOAT;

    return 0;
}

static PyObject* NoiseBlanker_setThreshold1(NoiseBlanker* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { (char*)"threshold", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &self->threshold1)) {
        return NULL;
    }

    Csdr::Filter<Csdr::complex<float>>* filter =
        new Csdr::RFNoiseBlanker(self->threshold1, self->threshold2);

    dynamic_cast<Csdr::FilterModule<Csdr::complex<float>>*>(self->module)->setFilter(filter);

    Py_RETURN_NONE;
}

static PyObject* NoiseBlanker_setThreshold2(NoiseBlanker* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = { (char*)"threshold", NULL };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &self->threshold2)) {
        return NULL;
    }

    Csdr::Filter<Csdr::complex<float>>* filter =
        new Csdr::RFNoiseBlanker(self->threshold1, self->threshold2);

    dynamic_cast<Csdr::FilterModule<Csdr::complex<float>>*>(self->module)->setFilter(filter);

    Py_RETURN_NONE;
}

static PyMethodDef NoiseBlanker_methods[] = {
    { "setThreshold1", (PyCFunction) NoiseBlanker_setThreshold1, METH_VARARGS | METH_KEYWORDS, "set first noise blanking threshold" },
    { "setThreshold2", (PyCFunction) NoiseBlanker_setThreshold2, METH_VARARGS | METH_KEYWORDS, "set second noise blanking threshold" },
    { NULL }  /* Sentinel */
};

static PyType_Slot NoiseBlankerSlots[] = {
    { Py_tp_init, (void*) NoiseBlanker_init },
    { Py_tp_methods, NoiseBlanker_methods },
    { 0, 0 }
};

PyType_Spec NoiseBlankerSpec = {
    "pycsdr.modules.NoiseBlanker",
    sizeof(NoiseBlanker),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    NoiseBlankerSlots
};