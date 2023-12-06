#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "module.hpp"

struct Ccir493Decoder: Module {};

extern PyType_Spec Ccir493DecoderSpec;
