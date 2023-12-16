#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "module.hpp"

struct SitorBDecoder: Module {};

extern PyType_Spec SitorBDecoderSpec;
