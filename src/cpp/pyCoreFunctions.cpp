#include "pyCoreFunctions.hpp"

static PyObject* py_initCore(PyObject* self, PyObject* args)
{
    PyObject* packPoolPointer = 0;

    if(!PyArg_ParseTuple(args, "O", &packPoolPointer)) {
        return NULL;
    }

    void* packetPointer = PyLong_AsVoidPtr(packPoolPointer);   
    pinat::initCore((pinat::PacketPool*)packetPointer);
    return 0; //?
}   

static PyObject* py_getSrcIp(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getSrcIp(packetID).c_str());
}

static PyObject* py_getDstIp(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getDstIp(packetID).c_str());
}


static PyObject* py_getSport(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }
    return PyLong_FromUnsignedLong(pinat::getSrcPort(packetID));
}

static PyObject* py_getDport(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }
    return PyLong_FromUnsignedLong(pinat::getDstPort(packetID));
}

static PyObject* py_getSrcMac(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getSenderMAC(packetID).c_str());
}

static PyObject* py_getDstMac(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getTargetMAC(packetID).c_str());
}