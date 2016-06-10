
#include <stdio.h>
#include "initialiser.h"
#include "guiUtils.h"
#include "defs.h"


static PyObject *py_getVolume(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    PyObject *temp;

    if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
        if (!PyCallable_Check(temp)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        Py_XINCREF(temp);         /* Add a reference to new callback */
        Py_XDECREF(pyFunCall);  /* Dispose of previous callback */
        pyFunCall = temp;       /* Remember new callback */
        /* Boilerplate to return "None" */
        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}

/**
  * Array of methods for integration with Python script
  */
static PyMethodDef touchHat_methods[] = {
    {"getVolume", py_getVolume, METH_VARARGS},
    {NULL, NULL}
};
