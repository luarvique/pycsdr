#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <csdr/complex.hpp>
#include <csdr/noisefilter.hpp>

#include "module.hpp"

struct NoiseFilter: Module {
    Csdr::AFNoiseFilter *noiseFilter;
    int threshold = 0;
    uint32_t wndSize = 32;
    uint32_t fftSize = 4096;
    uint32_t latency = 5;
};

extern PyType_Spec NoiseFilterSpec;
