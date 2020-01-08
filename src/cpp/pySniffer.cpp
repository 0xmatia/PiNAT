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
	char* sendingInterface;
	char *kwlist[] = {(char*)"interface", (char*)"filter", (char*) "sinterface", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "sss", kwlist, &interface, &filter, &sendingInterface))
		return -1;

	self->sniffer = new pinat::Sniffer(interface, filter, sendingInterface);

	return 0;
}

static PyObject* Sniffer_getPacket(SnifferObject* self)
{
	unsigned long p = self->sniffer->getPacket();
	PyObject* ret = PyLong_FromUnsignedLong(p);
	return ret;
}

static PyObject* Sniffer_forwardPacket(SnifferObject* self, PyObject* args)
{
	unsigned long id = 0;
	if(!PyArg_ParseTuple(args, "k", &id)) {
        return NULL;
    }

	self->sniffer->forwardPacket(id);
	return PyLong_FromUnsignedLong(id);
}

static PyObject* Sniffer_getPool(SnifferObject* self)
{
	return PyLong_FromVoidPtr(self->sniffer->getPacketPool());
}