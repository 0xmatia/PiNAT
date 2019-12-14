#include "pySniffer.hpp"

int sniffer_InitType(PyObject* module)
{
	pynat_SnifferType.tp_new = PyType_GenericNew;
	if(PyType_Ready(&pynat_SnifferType) < 0)
		return 1;

	Py_INCREF(&pynat_SnifferType);
    PyModule_AddObject(module, "Sniffer", (PyObject *)&pynat_SnifferType);

	return 0;
}