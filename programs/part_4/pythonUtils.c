#include <Python.h>
#include "guiUtils.h"


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
 * This function is called when a pin is touched. It takes as an argument the
 * number of the pin which was touched. It will be used for future GUI functions
 */
static PyObject *py_touched(PyObject *self, PyObject *args) {
    int pin; // Pin number touched (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    return Py_BuildValue("");
}

// Given pad number and instrument mode number, returns address of sound file
static PyObject *py_getSoundsFromInstrument(PyObject *self, PyObject *args) {
    int pin; // Pin number touched (0-11)
    int instr; // Instrument mode number
    PyArg_ParseTuple(args, "ii", &pin, &instr);
    char *filepath = (char *) SymbolTable_get(pin, set[instr]);
    return Py_BuildValue("s", filepath);
}

/** 
 * This function is called when a touched pin is released with the number of the
 * pin concerened. It will be used for future GUI functions
 */
static PyObject *py_released(PyObject* self, PyObject* args) {
    int pin; // Pin number released (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    return Py_BuildValue("");
}

/**
 * Initialise the map of sound files
 */
static PyObject *py_initSounds(PyObject *self, PyObject *args) {
    initialiseSymbolTables();
    return Py_BuildValue("");
}


/**
  * Array of methods for integration with Python script
  */
static PyMethodDef HUtouchHat_methods[] = {
    {"touched", py_touched, METH_VARARGS},
    {"released", py_released, METH_VARARGS},
    {"getSoundsFromInstrument", py_getSoundsFromInstrument, METH_VARARGS},
    {"initSounds", py_initSounds, METH_VARARGS},
    {"getVolume", py_getVolume, METH_VARARGS},
    {NULL, NULL}
};

void initHUtouchHat() {
    (void) Py_InitModule("HUtouchHat", HUtouchHat_methods);
}
