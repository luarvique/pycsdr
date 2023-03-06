#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <csdr/complex.hpp>

#include "module.hpp"

struct NoiseBlanker: Module {
    int threshold1 = 10;
    int threshold2 = 8;
};

extern PyType_Spec NoiseBlankerSpec;
