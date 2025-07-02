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
    uint32_t attack  = 2;
    uint32_t decay   = 10;
};

extern PyType_Spec NoiseFilterSpec;
