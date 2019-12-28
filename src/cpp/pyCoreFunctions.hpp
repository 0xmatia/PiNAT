#pragma once

#include <Python.h>
#include "coreFunctions.hpp"

extern "C" {
    PyObject* py_initCore(PyObject* self, PyObject* args);
    PyObject* py_getSrcIp(PyObject* self, PyObject* args);
    PyObject* py_getDstIp(PyObject* self, PyObject* args);
    PyObject* py_getSport(PyObject* self, PyObject* args);
    PyObject* py_getDport(PyObject* self, PyObject* args);
    PyObject* py_getSrcMac(PyObject* self, PyObject* args);
    PyObject* py_getDstMac(PyObject* self, PyObject* args);
}