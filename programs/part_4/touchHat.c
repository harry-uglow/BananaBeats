#include <Python.h>
#include <stdio.h>
#include <utils.h>

/** 
 *This function is called when a pin is touched. It takes as an argument the
 * number of the pin which was touched, and returns the path to the sound which
 * needs to be played as a string
 */
static PyObject* py_touched(PyObject* self, PyObject* args) {
    int pin; // Pin number touched (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    char *filepath; // Path to sound file
    // TODO: Get filepath from symbol tables
    printf("I was touched in the %d pin lol\n", pin);
    return Py_BuildValue("s", filepath);
}

/** 
 * This function is called when a touched pin is released with the number of the
 * pin concerened.
 */
static PyObject* py_released(PyObject* self, PyObject* args) {
    int pin; // Pin number released (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    printf("ahhhhhh... and release my %d pin\n", pin);
    return Py_BuildValue("");
}

/**
  * Array of methods for integration with Python script
  */
static PyMethodDef touchHat_methods[] = {
    {"touched", py_touched, METH_VARARGS},
    {"released", py_released, METH_VARARGS},
    {NULL, NULL}
};

void inittouchHat() {
    (void) Py_InitModule("touchHat", touchHat_methods);
}