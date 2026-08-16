#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <csdr/complex.hpp>
#include <csdr/noisefilter.hpp>

#include "module.hpp"

struct NoiseFilter: Module {
    Csdr::NoiseFilter<float> *noiseFilter = NULL;
    float threshold = 0.0f;
    uint32_t wndSize = 16;
    uint32_t fftSize = 1024;
    float attack = 0.5f;
    float decay = 0.1f;
};

extern PyType_Spec NoiseFilterSpec;
