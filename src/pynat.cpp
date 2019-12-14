#include <Python.h>
#include <string>
#include "pySniffer.hpp"

extern "C" {
	static PyObject *method_Vsniffer(PyObject *self, PyObject *args) {
    	std::string a("what");
   	 	a += "walabi";
    	return PyUnicode_FromString(a.c_str());
	}
}

/*
methods information.
*/
static PyMethodDef pynatMethods[] = {
    {"vsniffer", method_Vsniffer, METH_NOARGS, "Sniffer constructor"},
    {NULL, NULL, 0, NULL}
};

/*
module information.
*/
static struct PyModuleDef pynatModule = {
    PyModuleDef_HEAD_INIT,
    "pynat",
    "Python PiNAT library",
    -1,
    pynatMethods
};

/*
python module init function.
returns the new module.
*/
PyMODINIT_FUNC PyInit_pynat(void) {
    PyObject* module = PyModule_Create(&pynatModule);
    if(module == NULL)
        return NULL;

    if(sniffer_InitType(module) != 0)
        return NULL;

    return module;
}