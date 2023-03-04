#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <csdr/complex.hpp>

#include "module.hpp"

struct NoiseBlanker: Module {
    double threshold1 = 10.0;
    double threshold2 = 8.0;
};

extern PyType_Spec NoiseBlankerSpec;
