#include "pyCoreFunctions.hpp"

extern "C" 
{
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

    try {
        return PyUnicode_FromString(pinat::getSrcIp(packetID).c_str());
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }
    
}

PyObject* py_getDstIp(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    try {
        return PyUnicode_FromString(pinat::getDstIp(packetID).c_str());
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }
}


PyObject* py_getSport(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    try {
        return PyLong_FromUnsignedLong(pinat::getSrcPort(packetID));
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }
}

PyObject* py_getDport(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    try {
        return PyLong_FromUnsignedLong(pinat::getDstPort(packetID));
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }
}

PyObject* py_getSrcMac(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    try {
        return PyUnicode_FromString(pinat::getSrcMAC(packetID).c_str());
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }
}

PyObject* py_getDstMac(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    try {
        return PyUnicode_FromString(pinat::getDstMAC(packetID).c_str());
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }
}

PyObject* py_checkType(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;
    char* type;

    if(!PyArg_ParseTuple(args, "ks", &packetID, &type)) {
        return NULL;
    }

    try {
        if(pinat::checkType(packetID, type))
        {
            Py_RETURN_TRUE;
        }
        else
        {
            Py_RETURN_FALSE;
        }
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }
}

PyObject* py_dropPacket(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    try {
        pinat::dropPacket(packetID);
    } catch(const char* message) {
        PyErr_SetString(PyExc_KeyError, message);
        return NULL;
    }

    Py_RETURN_NONE;
}
}