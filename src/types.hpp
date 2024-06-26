#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyTypeObject* getFormatType();

#define FORMAT_TYPE getFormatType()

PyObject* getFormat(const char* name);

#define FORMAT_CHAR getFormat("CHAR")
#define FORMAT_SHORT getFormat("SHORT")
#define FORMAT_FLOAT getFormat("FLOAT")
#define FORMAT_COMPLEX_FLOAT getFormat("COMPLEX_FLOAT")
#define FORMAT_COMPLEX_SHORT getFormat("COMPLEX_SHORT")
#define FORMAT_COMPLEX_CHAR getFormat("COMPLEX_CHAR")

PyTypeObject* getAgcProfileType();

#define AGC_PROFILE_TYPE getAgcProfileType()
