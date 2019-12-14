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
	delete self->sniffer;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* Sniffer_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	SnifferObject* self;

	self = (SnifferObject*)type->tp_alloc(type, 0);
	if(self != NULL)
	{
		self->sniffer = nullptr;
	}

	return (PyObject*)self;
}

static int Sniffer_init(SnifferObject *self, PyObject *args, PyObject *kwds)
{
	char* interface;
	char* filter;
	char *kwlist[] = {(char*)"interface", (char*)"filter", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "ss", kwlist, &interface, &filter))
		return -1;

	self->sniffer = new pinat::Sniffer(interface, filter);

	return 0;
}

static PyObject* Sniffer_getPacket(SnifferObject* self)
{
	Tins::PDU* p = self->sniffer->getPacket();
	PyObject* ret = PyUnicode_FromString(self->sniffer->getLayers(p).c_str());
	delete p;
	return ret;
}
