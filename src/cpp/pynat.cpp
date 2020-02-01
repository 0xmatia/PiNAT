#include <Python.h>
#include <string>
#include "pySniffer.hpp"
#include "pyCoreFunctions.hpp"


PyMethodDef core_methods[] = {
    {"init_core", (PyCFunction)py_initCore, METH_VARARGS, "Initializes the core function system"},
    {"get_ips", (PyCFunction)py_getIPs, METH_VARARGS, "Gets the src and dst IP of the specified packet"},
    {"get_ports", (PyCFunction)py_getPorts, METH_VARARGS, "Gets the src and dst port of the specified packet"},
    {"get_macs", (PyCFunction)py_getMACs, METH_VARARGS, "Gets the src and dst Mac of the specified packet"},
    {"drop_packet", (PyCFunction)py_dropPacket, METH_VARARGS, "Drops the specified packet"},
    {"check_type", (PyCFunction)py_checkType, METH_VARARGS, "Checks the type of the specified packet"},
    {"get_arp_info", (PyCFunction)py_getArpInfo, METH_VARARGS, "Gets sender and target info from the specified arp packet"},
    {"get_dns_info", (PyCFunction)py_getDNSInfo, METH_VARARGS, "Returns a dictionary with the dns query responses"},
    {"open_db", (PyCFunction)py_openDB, METH_VARARGS, "opens connection to database"},
    {"close_db", (PyCFunction)py_closeDB, METH_VARARGS, "closes connection to database"},
    {"exec_db", (PyCFunction)py_execDB, METH_VARARGS, "executes a command in the database"},
    {NULL}  /* Sentinel */
};


/*
module information.
*/
static struct PyModuleDef pynatModule = {
    PyModuleDef_HEAD_INIT,
    "pynat",
    "Python PiNAT library",
    -1,
    core_methods, 
    NULL, NULL, NULL, NULL
};

/*
python module init function.
returns the new module.
*/
PyMODINIT_FUNC PyInit_pynat(void) {
    PyObject* module = PyModule_Create(&pynatModule);
    if(module == NULL)
        return NULL;

    if(Sniffer_InitType(module) != 0) //initializing our created object
        return NULL;

    return module;
}