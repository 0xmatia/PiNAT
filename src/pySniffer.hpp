#pragma once

#include <Python.h>
#include <structmember.h>
#include "sniffer.hpp"

typedef struct snifferObject{
    PyObject_HEAD
    int* a;
} SnifferObject;

int Sniffer_InitType(PyObject* module);

extern "C" {
	static void Sniffer_dealloc(snifferObject* self);
	static PyObject* Sniffer_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
	static int Sniffer_init(SnifferObject *self, PyObject *args, PyObject *kwds);
	static PyObject* Sniffer_xnum(SnifferObject* self);
	static PyObject* Sniffer_getnum(SnifferObject *self, void *closure);
	static int Sniffer_setnum(SnifferObject *self, PyObject *value, void *closure);
}

static PyMethodDef Sniffer_methods[] = {
    {"xnum", (PyCFunction)Sniffer_xnum, METH_NOARGS, "Returns num"},
    {NULL}  /* Sentinel */
};

static PyGetSetDef Sniffer_getseters[] = {
    {(char*)"num", (getter)Sniffer_getnum, (setter)Sniffer_setnum, (char*)"sniffer num", NULL},
    {NULL}  /* Sentinel */
};

static PyTypeObject SnifferType = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "pynat.Sniffer",               	/* tp_name */
    sizeof(SnifferObject), 			/* tp_basicsize */
    0,                             	/* tp_itemsize */
    (destructor)Sniffer_dealloc,	/* tp_dealloc */
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
    0,                           	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,            	/* tp_flags */
    "Sniffer object",				/* tp_doc */
	0,                 		        /* tp_traverse */
    0,                 		        /* tp_clear */
    0,                 		        /* tp_richcompare */
    0,                  		    /* tp_weaklistoffset */
    0,                 		        /* tp_iter */
    0,                 		        /* tp_iternext */
    Sniffer_methods,				/* tp_methods */
    0,			     		        /* tp_members */
    Sniffer_getseters,				/* tp_getset */
    0,                 		        /* tp_base */
    0,                 		        /* tp_dict */
    0,                 		        /* tp_descr_get */
    0,                 		        /* tp_descr_set */
    0,                 		        /* tp_dictoffset */
    (initproc)Sniffer_init,			/* tp_init */
    0,                 		        /* tp_alloc */
    Sniffer_new,					/* tp_new */
};
