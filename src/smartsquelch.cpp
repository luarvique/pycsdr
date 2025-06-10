#include "smartsquelch.hpp"
#include "types.hpp"
#include "pycsdr.hpp"

#include <csdr/smartsquelch.hpp>

static void reportPower(SmartSquelch* self, float level) {
    if (--self->reportCounter <= 0) {
        self->reportCounter = self->reportInterval;

        if (self->powerWriter) {
            auto writer = dynamic_cast<Csdr::Writer<float>*>(self->powerWriter->writer);
            if (writer->writeable()) {
                *(writer->getWritePointer()) = level;
                writer->advance(1);
            }
        }
    }
}

static int SmartSquelch_init(SmartSquelch* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "format", (char*)"length", (char*) "decimation", (char*)"hangLength", (char*)"flushLength", (char*) "reportInterval", NULL};

    // default reporting interval
    self->reportInterval = 1;

    PyObject *format = nullptr;
    unsigned int length = 1024;
    unsigned int decimation = 1;
    unsigned int hangLength = 0;
    unsigned int flushLength = 1024 * 5;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!IIIII", kwlist, FORMAT_TYPE, &format, &length, &decimation, &hangLength, &flushLength, &self->reportInterval)) {
        return -1;
    }

    self->inputFormat = format;
    self->outputFormat = format;
    self->reportCounter = self->reportInterval;

    if (format == FORMAT_COMPLEX_FLOAT) {
        self->setModule(new Csdr::SmartSquelch<Csdr::complex<float>>(
            length, hangLength, flushLength,
            [self] (float level) { reportPower(self, level); }
        ));
    } else if (format == FORMAT_FLOAT) {
        self->setModule(new Csdr::SmartSquelch<float>(
            length, hangLength, flushLength,
            [self] (float level) { reportPower(self, level); }
        ));
    } else {
        PyErr_SetString(PyExc_ValueError, "invalid format");
        return -1;
    }

    return 0;
}

static PyObject* SmartSquelch_setSquelchLevel(SmartSquelch* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "level", NULL};

    float level = 0.0f;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "f", kwlist, &level)) {
        return NULL;
    }

    if (self->inputFormat == FORMAT_COMPLEX_FLOAT) {
        dynamic_cast<Csdr::SmartSquelch<Csdr::complex<float>>*>(self->module)->setSquelch(level);
    } else if (self->inputFormat == FORMAT_FLOAT) {
        dynamic_cast<Csdr::SmartSquelch<float>*>(self->module)->setSquelch(level);
    }

    Py_RETURN_NONE;
}

static PyObject* SmartSquelch_setPowerWriter(SmartSquelch* self, PyObject* args, PyObject* kwds) {
    Writer* writer;

    static char* kwlist[] = {(char*) "writer", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist, WriterType, &writer)) {
        return NULL;
    }

    if ((PyObject*) writer != Py_None && writer->writerFormat != FORMAT_FLOAT) {
        PyErr_SetString(PyExc_ValueError, "invalid writer format");
        return NULL;
    }

    if (self->powerWriter != nullptr) {
        Py_DECREF(self->powerWriter);
        self->powerWriter = nullptr;
    }

    if ((PyObject*) writer != Py_None) {
        self->powerWriter = writer;
        Py_INCREF(self->powerWriter);
    }

    Py_RETURN_NONE;
}

static PyObject* SmartSquelch_setReportInterval(SmartSquelch* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*) "reportInterval", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist, &self->reportInterval)) {
        return NULL;
    }
    // reset since this may contain excessively high values
    self->reportCounter = self->reportInterval;

    Py_RETURN_NONE;
}

static PyMethodDef SmartSquelch_methods[] = {
    {"setSquelchLevel", (PyCFunction) SmartSquelch_setSquelchLevel, METH_VARARGS | METH_KEYWORDS,
     "set squelch level"
    },
    {"setPowerWriter", (PyCFunction) SmartSquelch_setPowerWriter, METH_VARARGS | METH_KEYWORDS,
     "set a writer that will receive power level readouts"
    },
    {"setReportInterval", (PyCFunction) SmartSquelch_setReportInterval, METH_VARARGS | METH_KEYWORDS,
     "set the report interval"
    },
    {NULL}  /* Sentinel */
};

static PyType_Slot SmartSquelchSlots[] = {
    {Py_tp_init, (void*) SmartSquelch_init},
    {Py_tp_methods, SmartSquelch_methods},
    {0, 0}
};

PyType_Spec SmartSquelchSpec = {
    "pycsdr.modules.SmartSquelch",
    sizeof(SmartSquelch),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    SmartSquelchSlots
};
