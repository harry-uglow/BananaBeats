#ifndef PART_4_GUIUTILS_H
#define PART_4_GUIUTILS_H

#include <Python.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define string constants
#define RB1_LABEL "Drums"
#define RB2_LABEL "Piano"
#define RB3_LABEL "Mario"
#define RB1_TOOLTIP "Change instrument to: Drums"
#define RB2_TOOLTIP "Change instrument to: Piano"
#define RB3_TOOLTIP "Change instrument to: Mario SFX"
#define VC_TOOLTIP "Adjust the volume"
#define VOLUME_LABEL "Volume"
#define WIN_TITLE_RB1 "Instrument: Drums"
#define WIN_TITLE_RB2 "Instrument: Piano"
#define WIN_TITLE_RB3 "Instrument: Mario SFX"

// Define number constants
#define DEFAULT_PADDING 2
#define VOLUME_MIN 0
#define VOLUME_MAX 100
#define VOLUME_STEP 1
#define VOLUME_CONTROL_WIDTH 150
#define MAX_DIGITS_VOLUME_PERCENTAGE 3
#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 250
#define WINDOW_BORDER 15
#define WIDGET_SPACING 30
#define RADIO_BUTTON_SPACING 1
#define VOLUME_CONTROL_SPACING 1


// Enum for the type of Instrument currently selected
enum Instrument {
    DRUMS,
    PIANO,
    MARIO
} instrument;

// Declare widgets as global variables
GtkWidget *window;
GtkWidget *widgetContainer;
GtkWidget *vBoxRadioButtons;
GtkWidget *vBoxVolumeControl;
GtkWidget *volumeLabel;
GtkWidget *rb1;
GtkWidget *rb2;
GtkWidget *rb3;
GtkWidget *image;
GtkWidget *vc;

// Declare volume as variable
gdouble currentVolume;
PyObject *pyFunCall;

void create_radio_buttons(GtkBox *vBox);
void create_volume_control(GtkBox *vBox);
void toggle_sound_mode(GtkRadioButton *widget, gpointer window);
void adjust_volume(GtkScale *vc, gpointer window);

#endif //PART_4_GUIUTILS_H
