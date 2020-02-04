#pragma once

#include <Python.h>
#include "coreFunctions.hpp"

extern "C" {
    PyObject* py_initCore(PyObject* self, PyObject* args);
    PyObject* py_getIPs(PyObject* self, PyObject* args);
    PyObject* py_getPorts(PyObject* self, PyObject* args);
    PyObject* py_getMACs(PyObject* self, PyObject* args);
    PyObject* py_checkType(PyObject* self, PyObject* args);
    PyObject* py_dropPacket(PyObject* self, PyObject* args);
    PyObject* py_getArpInfo(PyObject* self, PyObject* args);
    PyObject* py_getDNSInfo(PyObject* self, PyObject* args);
    PyObject* py_openDB(PyObject* self, PyObject* args);
    PyObject* py_closeDB(PyObject* self, PyObject* args);
    PyObject* py_execDB(PyObject* self, PyObject* args);
}