#pragma once
#include <Python.h>

typedef struct pynat_SnifferObject{
    PyObject_HEAD
    /* Type-specific fields go here. */
} pynat_SnifferObject;

static PyTypeObject pynat_SnifferType = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "pynat.Sniffer",               	/* tp_name */
    sizeof(pynat_SnifferObject), 	/* tp_basicsize */
    0,                             	/* tp_itemsize */
    0,                             	/* tp_dealloc */
    0,                             	/* tp_print */
    0,                             	/* tp_getattr */
    0,                             	/* tp_setattr */
    0,                             	/* tp_reserved */
    0,                             	/* tp_repr */
    0,                             	/* tp_as_number */
    0,                             	/* tp_as_sequence */
    0,                             	/* tp_as_mapping */
    0,                             	/* tp_hash  */
    0,                             	/* tp_call */
    0,                             	/* tp_str */
    0,                             	/* tp_getattro */
    0,                             	/* tp_setattro */
    0,                             	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,            	/* tp_flags */
    "Sniffer object",				/* tp_doc */
};

int sniffer_InitType(PyObject* module);