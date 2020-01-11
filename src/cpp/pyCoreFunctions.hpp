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
    PyObject* py_checkType(PyObject* self, PyObject* args);
}


PyMethodDef core_methods[] = {
    {"init_core", (PyCFunction)py_initCore, METH_VARARGS, "Initializes the core function system"},
    {"get_src_ip", (PyCFunction)py_getSrcIp, METH_VARARGS, "Gets the src IP of the specified packet"},
    {"get_dst_ip", (PyCFunction)py_getDstIp, METH_VARARGS, "Gets the dst IP of the specified packet"},
    {"get_src_port", (PyCFunction)py_getSport, METH_VARARGS, "Gets the src port of the specified packet"},
    {"get_dst_port", (PyCFunction)py_getDport, METH_VARARGS, "Gets the dst port of the specified packet"},
    {"get_src_mac", (PyCFunction)py_getSrcMac, METH_VARARGS, "Gets the src Mac of the specified packet"},
    {"get_dst_mac", (PyCFunction)py_getDstMac, METH_VARARGS, "Gets the dst Mac of the specified packet"},
    {"check_type", (PyCFunction)py_getDstMac, METH_VARARGS, "Checks the type of the specified packet"},
    {NULL}  /* Sentinel */
};