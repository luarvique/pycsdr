#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "module.hpp"

struct FskUartDecoder: Module {};

extern PyType_Spec FskUartDecoderSpec;
