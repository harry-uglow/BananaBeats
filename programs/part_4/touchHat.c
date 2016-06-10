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
    return Py_BuildValue("");
}

// Given pad number, returns address of sound file
static PyObject *py_getSounds(PyObject *self, PyObject *args) {
    int pin; // Pin number touched (0-11)
    PyArg_ParseTuple(args, "i", &pin);
    char *filepath = (char *) SymbolTable_get(pin, set[instrument]);
    return Py_BuildValue("s", filepath);
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
    gtk_container_set_border_width(GTK_CONTAINER(window), WINDOW_BORDER);
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window), "Instrument: Drums");

    // Create new box to hold the widgets
    widgetContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, WIDGET_SPACING);
    gtk_widget_set_halign(widgetContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widgetContainer, GTK_ALIGN_CENTER);
    
    // Create new vertical box with 1 pixel between elements as default.
    vBoxRadioButtons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 
            RADIO_BUTTON_SPACING);
    gtk_widget_set_halign(vBoxRadioButtons, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxRadioButtons, GTK_ALIGN_CENTER);

    // Create new vertical box for volume control
    vBoxVolumeControl = gtk_box_new(GTK_ORIENTATION_VERTICAL,
            VOLUME_CONTROL_SPACING);
    gtk_widget_set_halign(vBoxVolumeControl, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxVolumeControl, GTK_ALIGN_CENTER);

    // Create the radio buttons and pack the into vBoxRadioButtons.
    create_radio_buttons(GTK_BOX(vBoxRadioButtons));

    // Create the volume control and pack it into vBoxVolumeControl
    create_volume_control(GTK_BOX(vBoxVolumeControl));

    // When the window is closed exit the program.
    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    // Add the boxs to the window.
    gtk_container_add(GTK_CONTAINER(widgetContainer), vBoxRadioButtons);
    gtk_container_add(GTK_CONTAINER(widgetContainer), vBoxVolumeControl);
    gtk_container_add(GTK_CONTAINER(window), widgetContainer);

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

static PyObject *py_getInstrument(PyObject *self, PyObject *args) {
    if(instrument == DRUMS) {
	printf("Drums\n");
    }
    return Py_BuildValue("i", instrument);
}

static PyObject *py_getVolume(PyObject *self, PyObject *args) {
    return Py_BuildValue("i", currentVolume);
}

/**
  * Array of methods for integration with Python script
  */
static PyMethodDef touchHat_methods[] = {
    {"touched", py_touched, METH_VARARGS},
    {"released", py_released, METH_VARARGS},
    {"gui", py_gui, METH_VARARGS},
    {"getSounds", py_getSounds, METH_VARARGS},
    {"getSoundsFromInstrument", py_getSoundsFromInstrument, METH_VARARGS},
    {"initSounds", py_initSounds, METH_VARARGS},
    {"getInstrument", py_getInstrument, METH_VARARGS},
    {"getVolume", py_getVolume, METH_VARARGS},
    {NULL, NULL}
};

void inittouchHat() {
    (void) Py_InitModule("touchHat", touchHat_methods);
}
