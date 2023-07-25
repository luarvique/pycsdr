#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "module.hpp"

struct Resampler: Module {};

extern PyType_Spec ResamplerSpec;
