#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "module.hpp"

struct Ccir476Decoder: Module {};

extern PyType_Spec Ccir476DecoderSpec;
