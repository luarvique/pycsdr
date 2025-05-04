#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "module.hpp"

struct Squelch: Module {
    Writer* powerWriter;
    unsigned int reportInterval = 1;
    int reportCounter;
};

extern PyType_Spec SquelchSpec;
