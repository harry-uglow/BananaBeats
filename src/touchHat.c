#include <Python.h>
#include <stdio.h>
#include "initialiser.h"
#include "guiUtils.h"

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
static PyMethodDef touchHat_methods[] = {
    {"touched", py_touched, METH_VARARGS},
    {"released", py_released, METH_VARARGS},
    {"getSoundsFromInstrument", py_getSoundsFromInstrument, METH_VARARGS},
    {"initSounds", py_initSounds, METH_VARARGS},
    {NULL, NULL}
};

void inittouchHat() {
    (void) Py_InitModule("touchHat", touchHat_methods);
}
