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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
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
        } catch(std::exception& e) {
            PyErr_SetString(PyExc_KeyError, e.what());
            return NULL;
        }
    
        Py_RETURN_NONE;
    }

    PyObject* py_getArpInfo(PyObject* self, PyObject* args)
    {
        unsigned long packetID = 0;
    
        if(!PyArg_ParseTuple(args, "k", &packetID)) {
            return NULL;
        }

        PyObject* ret = nullptr;
        std::vector<std::string>* vec = nullptr;

        try {
            vec = pinat::getArpInfo(packetID);
        } catch(std::exception& e) {
            if(vec)
                delete vec;
            PyErr_SetString(PyExc_KeyError, e.what());
            return NULL;
        }
        
        if (vec)
        {
            ret = Py_BuildValue("ssss", vec->at(0).c_str(), vec->at(1).c_str(), vec->at(2).c_str(), vec->at(3).c_str());
            delete vec;
            return ret;
        }
        else
        {
            Py_RETURN_NONE;
        }
    }
    
    PyObject* py_getDNSInfo(PyObject* self, PyObject* args)
    {
        unsigned long packetID = 0;
        PyObject* addresses, *info;
        std::string dname;
        std::vector<std::string>* addressVector;
        int counter = 0;
        
        if(!PyArg_ParseTuple(args, "k", &packetID)) {
            return NULL;
        }
        std::map<std::string, std::vector<std::string>*> dnsInfo = pinat::getDNSInfo(packetID);

        //create the dictionary
        info = PyDict_New();

        //Iterate over the map:
        for (auto i = dnsInfo.begin(); i != dnsInfo.end(); i++)
        {
            dname = i->first;
            addressVector = i->second;

            //create new list:
            addresses = PyList_New(addressVector->size());
            //Now, fill the pylist with the values inside tempAddesses
            for (const auto address : *addressVector)
            {
                PyList_SetItem(addresses, counter, PyUnicode_FromString(address.c_str()));
                counter++;
            }
            counter = 0;
            //FREE the allocated space for the addressVector
            delete addressVector;
            addressVector = NULL;

            //insert vector + dname into the dictionary
            PyDict_SetItem(info, PyUnicode_FromString(dname.c_str()), addresses);
            addresses = NULL; 
            //DON'T delete the ref to the old list (which the dictionary now has 
            // a pointer to), but point to null because in the next iteration
            // we are creating a new list
        }
        return info;
    }

}
