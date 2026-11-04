#include "fskuart.hpp"
#include "types.hpp"

#include <csdr/fskuart.hpp>
#include <cmath>
#include <new>
#include <stdexcept>

static int FskUartDecoder_init(FskUartDecoder* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {
        (char*) "sampleRate", (char*) "baudRate", (char*) "markFreq",
        (char*) "spaceFreq", (char*) "gapChars", (char*) "maxFrame", NULL
    };

    int sampleRate, maxFrame = 264;
    double baudRate = 1200, markFreq = 1300, spaceFreq = 2100, gapChars = 3.5;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "i|ddddi", kwlist,
        &sampleRate, &baudRate, &markFreq, &spaceFreq, &gapChars, &maxFrame)) {
        return -1;
    }
    if (sampleRate <= 0 || maxFrame <= 0 || !std::isfinite(baudRate)
        || !std::isfinite(markFreq) || !std::isfinite(spaceFreq) || !std::isfinite(gapChars)) {
        PyErr_SetString(PyExc_ValueError, "invalid FSK/UART parameters");
        return -1;
    }
    try {
        self->setModule(new Csdr::FskUartDecoder(sampleRate, baudRate, markFreq,
            spaceFreq, gapChars, maxFrame));
    } catch (const std::invalid_argument& error) {
        PyErr_SetString(PyExc_ValueError, error.what());
        return -1;
    } catch (const std::bad_alloc&) {
        PyErr_NoMemory();
        return -1;
    }
    self->inputFormat = FORMAT_FLOAT;
    self->outputFormat = FORMAT_CHAR;

    return 0;
}

static PyType_Slot FskUartDecoderSlots[] = {
    {Py_tp_init, (void*) FskUartDecoder_init},
    {0, 0}
};

PyType_Spec FskUartDecoderSpec = {
    "pycsdr.modules.FskUartDecoder",
    sizeof(FskUartDecoder),
    0,
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_FINALIZE,
    FskUartDecoderSlots
};
