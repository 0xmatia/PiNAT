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

PyObject* py_checkType(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;
    char* type;

    if(!PyArg_ParseTuple(args, "ks", &packetID, &type)) {
        return NULL;
    }

    if(pinat::checkType(packetID, type))
    {
        Py_RETURN_TRUE;
    }
    else
    {
        Py_RETURN_FALSE;
    }
    
}

PyObject* py_getDNSNames(PyObject* self, PyObject* args)
{
    unsigned long packetID = 0;
    PyObject *PList = PyList_New(0);

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    std::vector<std::string> names = pinat::getDNSNames(packetID);

    //convert to pylsit
    for(auto it = names.begin(); it != names.end(); it++ )
    {
        PyList_Append(PList, Py_BuildValue("s", (*it).c_str()));
    }
    return PList;
}

PyObject* py_getDNSAddresses(PyObject* self, PyObject* args)
{
        unsigned long packetID = 0;
    PyObject *PList = PyList_New(0);

    if(!PyArg_ParseTuple(args, "k", &packetID)) {
        return NULL;
    }

    std::vector<std::string> ips = pinat::getDNSAddresses(packetID);

    //convert to pylsit
    for(auto it = ips.begin(); it != ips.end(); it++ )
    {
        PyList_Append(PList, Py_BuildValue("s", (*it).c_str()));
    }
    return PList;
}