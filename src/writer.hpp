#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <csdr/writer.hpp>

struct Writer {
    PyObject_HEAD
    Csdr::UntypedWriter* writer = NULL;
    PyObject* writerFormat = NULL;
};

extern PyType_Spec WriterSpec;