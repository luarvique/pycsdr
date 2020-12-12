#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "buffer.h"

typedef struct {
    PyObject_HEAD
    int port;
    int socket;
    Buffer* buffer;
} SocketClient;

int SocketClient_traverse(SocketClient* self, visitproc visit, void* arg);
int SocketClient_clear(SocketClient* self);
void SocketClient_dealloc(SocketClient* self);
PyObject* SocketClient_new(PyTypeObject* type, PyObject* args, PyObject* kwds);
int SocketClient_init(SocketClient* self, PyObject* args, PyObject* kwds);
PyObject* SocketClient_getBuffer(SocketClient* self, PyObject* Py_UNUSED(ignored));

extern PyTypeObject SocketClientType;