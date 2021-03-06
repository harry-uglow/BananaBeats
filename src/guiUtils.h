#ifndef PART_4_GUIUTILS_H
#define PART_4_GUIUTILS_H

#include <Python.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

// Define string constants
#define LOADING_LABEL "Loading..."
#define LOADING_TOOLTIP "Patience is a virtue"
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
#define VOLUME_CONTROL_WIDTH 580
#define MAX_DIGITS_VOLUME_PERCENTAGE 3
#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 250
#define WINDOW_BORDER 15
#define WIDGET_SPACING 30
#define RADIO_BUTTON_SPACING 1
#define VOLUME_CONTROL_SPACING 1
#define DEFAULT_START_VOLUME 70
#define MAX_DIGITS_NUMBER_OF_MODES 15



// Enum for the type of Instrument currently selected
enum Instrument {
    DRUMS,
    PIANO,
    MARIO
} instrument;

// Declare widgets as global variables
GtkWidget *loadingWindow;
GtkWidget *window;
GtkWidget *layout;
GtkWidget *background;
GtkWidget *controlContainer;
GtkWidget *widgetContainer;
GtkWidget *loadingContainer;
GtkWidget *loadingGif;
GtkWidget *loadingLabel;
GtkWidget *hBoxLights;
GtkWidget *vBoxRadioButtons;
GtkWidget *vBoxVolumeControl;
GtkWidget *volumeLabel;
GtkWidget *rb1;
GtkWidget *rb2;
GtkWidget *rb3;
GtkWidget *image;
GtkWidget *vc;
GtkWidget *light0;
GtkWidget *light1;
GtkWidget *light2;
GtkWidget *light3;
GtkWidget *light4;
GtkWidget *light5;
GtkWidget *light6;
GtkWidget *light7;
GtkWidget *light8;
GtkWidget *light9;
GtkWidget *light10;
GtkWidget *light11;
GtkWidget *drumsIcon;
GtkWidget *pianoIcon;
GtkWidget *marioIcon;
GtkWidget *currentSoundMode;
GtkWidget *iconContainer;

// Declare animation for the loading gif
GdkPixbufAnimation *animation;

// Declare volume as variable
gdouble currentVolume;
PyObject *pyFunCall;

// Declare pthread as global variable
pthread_t threadStartupSound;

pthread_t threadPython;
pthread_t threadGui;
pthread_t threadInstrLoop;

FILE *pyPipe;

int isChangingIns;


void run_loading_screen(void);
gboolean quitLoadingScreen(gpointer data);
void initialise_main_window(void);
void set_up_main_window(void);
void *playStartupSound(void *pInstrument);
void create_background(void);
void create_sound_mode(GtkBox *hBox);
void create_twelve_lights(GtkBox *hBox);
void turn_light_on(int pin);
void turn_light_off(int pin);
void create_loading_screen(GtkBox *vBox);
void create_radio_buttons(GtkBox *vBox);
void create_volume_control(GtkBox *vBox);
void toggle_sound_mode(GtkRadioButton *widget, gpointer window);
void adjust_volume(GtkScale *vc, gpointer window);
gboolean toggle_light(GtkWidget *widget, GdkEventExpose *event);
void changePyProgram(void);
void runPythonScript(void);

// DEBUGGING VARIABLES
int number_of_ons;
int number_of_offs;

#endif //PART_4_GUIUTILS_H
