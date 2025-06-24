#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <csdr/complex.hpp>
#include <csdr/noisefilter.hpp>

#include "module.hpp"

struct NoiseFilter: Module {
    Csdr::AFNoiseFilter *noiseFilter = NULL;
    int threshold = 0;
    uint32_t wndSize = 16;
    uint32_t fftSize = 1024;
    uint32_t latency = 3;
};

extern PyType_Spec NoiseFilterSpec;
