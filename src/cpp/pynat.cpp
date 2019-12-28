#include <Python.h>
#include <string>
#include "pySniffer.hpp"
#include "pyCoreFunctions.hpp"

/*
module information.
*/
static struct PyModuleDef pynatModule = {
    PyModuleDef_HEAD_INIT,
    "pynat",
    "Python PiNAT library",
    -1,
    NULL, NULL, NULL, NULL, NULL
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