#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "module.hpp"

struct FractionalDecimator: Module {};
struct StereoFractionalDecimator: Module {};

extern PyType_Spec FractionalDecimatorSpec;
extern PyType_Spec StereoFractionalDecimatorSpec;