#include <Python.h>
#include <stdio.h>

int main() {

    return 0;
}

static PyObject* py_touched(PyObject* self, PyObject* args) {
    int pin;
    PyArg_ParseTuple(args, "i", &pin);
    printf("I was touched in the %d pin lol\n", pin);
    return Py_BuildValue("");
}

static PyObject* py_released(PyObject* self, PyObject* args) {
    int pin;
    PyArg_ParseTuple(args, "i", &pin);
    printf("ahhhhhh... and release my %d pin\n", pin);
    return Py_BuildValue("");
}

static PyMethodDef touchHat_methods[] = {
  {"touched", py_touched, METH_VARARGS},
  {"released", py_released, METH_VARARGS},
  {NULL, NULL}
};

void inittouchHat() {
  (void) Py_InitModule("touchHat", touchHat_methods);
}