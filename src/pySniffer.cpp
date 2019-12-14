#include "pySniffer.hpp"

int Sniffer_InitType(PyObject* module)
{
	if(PyType_Ready(&SnifferType) < 0)
		return 1;

	Py_INCREF(&SnifferType);
    PyModule_AddObject(module, "Sniffer", (PyObject *)&SnifferType);

	return 0;
}

static void Sniffer_dealloc(SnifferObject* self)
{
	delete self->a;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* Sniffer_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	SnifferObject* self;

	self = (SnifferObject*)type->tp_alloc(type, 0);
	if(self != NULL)
	{
		self->a = nullptr;
		try{
			self->a = new int;
		} catch(...) {
			Py_DECREF(self);
            return NULL;
		}

		*(self->a) = 0;
	}

	return (PyObject*)self;
}

static int Sniffer_init(SnifferObject *self, PyObject *args, PyObject *kwds)
{
	int num = 0;
	char *kwlist[] = {(char*)"num", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &num))
		return -1;

	*(self->a) = num;
	return 0;
}

static PyObject* Sniffer_xnum(SnifferObject* self)
{
	return PyLong_FromLong(*(self->a));
}

static PyObject* Sniffer_getnum(SnifferObject *self, void *closure)
{
	return PyLong_FromLong(*(self->a));
}

static int Sniffer_setnum(SnifferObject *self, PyObject *value, void *closure)
{
	int val;

	if(value == NULL)
	{
		PyErr_SetString(PyExc_TypeError, "Cannot delete num");
    	return -1;
	}

	val = (int)PyLong_AsLong(value);
	if(val == -1)
	{
		PyErr_SetString(PyExc_TypeError, "expected a number");
    	return -1;
	}

	*(self->a) = val;
	return 0;
}
