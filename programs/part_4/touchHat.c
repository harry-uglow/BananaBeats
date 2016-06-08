#include <Python.h>
#include <stdio.h>

int main() {

    return 0;
}

static PyObject* py_touched(PyObject* self, PyObject* args) {
    int x;
    PyArg_ParseTuple(args, "i", &x);
    printf("I was touched in the %d pin lol\n", x);
    return Py_BuildValue("");
}

static PyObject* py_released(PyObject* self, PyObject* args) {
    printf("ahhhhhh... and release\n");
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