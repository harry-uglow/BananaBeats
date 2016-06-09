#include <Python.h>
#include <stdio.h>
#include "initialiser.h"
#include "guiUtils.h"

/** 
 * This function is called when a pin is touched. It takes as an argument the
 * number of the pin which was touched
 */
static PyObject *py_touched(PyObject *self, PyObject *args) {
    int pin; // Pin number touched (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    // TODO: correct sound mode/set
    char *filepath = (char *) SymbolTable_get(pin, set[0]);
    return Py_BuildValue("");
}

// Given pad number, returns address of sound file
static PyObject *py_getSounds(PyObject *self, PyObject *args) {
    int pin; // Pin number touched (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    // TODO: correct sound mode/set
    char *filepath = (char *) SymbolTable_get(pin, set[0]);
    return Py_BuildValue("s", filepath);
}

/** 
 * This function is called when a touched pin is released with the number of the
 * pin concerened.
 */
static PyObject *py_released(PyObject* self, PyObject* args) {
    int pin; // Pin number released (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    return Py_BuildValue("");
}

/**
 * This function is called as a separate process to set up and run the GUI.
 */
static PyObject *py_gui(PyObject *self, PyObject *args) {
    // Initialise GTK+
    gtk_init(0, NULL);

    // Set up the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    gtk_window_set_title(GTK_WINDOW(window), "Sound mode: Drums");

    // Create new vertical box with 1 pixel between elements as default.
    vBoxRadioButtons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_halign(vBoxRadioButtons, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxRadioButtons, GTK_ALIGN_CENTER);

    // Create the radio buttons and pack the into vBoxRadioButtons.
    create_radio_buttons(GTK_BOX(vBoxRadioButtons));

    // When the window is closed exit the program.
    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    // Add the box to the window.
    gtk_container_add(GTK_CONTAINER(window), vBoxRadioButtons);
    // Show the window
    gtk_widget_show_all(window);
    
    // Enter the main loop
    gtk_main();
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
    {"gui", py_gui, METH_VARARGS},
    {"getSounds", py_getSounds, METH_VARARGS},
    {"initSounds", py_initSounds, METH_VARARGS},
    {NULL, NULL}
};

void inittouchHat() {
    (void) Py_InitModule("touchHat", touchHat_methods);
}
