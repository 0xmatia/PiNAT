#include "pyCoreFunctions.hpp"

PyObject* py_initCore(PyObject* self, PyObject* args)
{
    PyObject* packPoolPointer = 0;

    if(!PyArg_ParseTuple(args, "O", &packPoolPointer)) {
        return NULL;
    }

    void* packetPointer = PyLong_AsVoidPtr(packPoolPointer);   
    pinat::initCore((pinat::PacketPool*)packetPointer);
    Py_RETURN_NONE;
}   

PyObject* py_getSrcIp(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getSrcIp(packetID).c_str());
}

PyObject* py_getDstIp(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getDstIp(packetID).c_str());
}


PyObject* py_getSport(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }
    return PyLong_FromUnsignedLong(pinat::getSrcPort(packetID));
}

PyObject* py_getDport(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }
    return PyLong_FromUnsignedLong(pinat::getDstPort(packetID));
}

PyObject* py_getSrcMac(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getSrcMAC(packetID).c_str());
}

PyObject* py_getDstMac(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    return PyUnicode_FromString(pinat::getDstMAC(packetID).c_str());
}