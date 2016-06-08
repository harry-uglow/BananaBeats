#ifndef PART_4_GUIUTILS_H
#define PART_4_GUIUTILS_H

#include <gtk/gtk.h>

// Define string constants
#define RB1_LABEL "Drums"
#define RB2_LABEL "Piano"
#define RB3_LABEL "Airhorns"
#define RB1_TOOLTIP "Change instrument to: Drums"
#define RB2_TOOLTIP "Change instrument to: Piano"
#define RB3_TOOLTIP "Change instrument to: Airhorns"
#define WIN_TITLE_RB1 "Instrument: Drums"
#define WIN_TITLE_RB2 "Instrument: Piano"
#define WIN_TITLE_RB3 "Instrument: Airhorns"

// Declare widgets as global variables
GtkWidget *window;
GtkWidget *vBoxRadioButtons;
GtkWidget *halign;
GtkWidget *rb1;
GtkWidget *rb2;
GtkWidget *rb3;
GtkWidget *image;

void create_radio_buttons(GtkBox *vBox);
void toggle_sound_mode(GtkRadioButton *widget, gpointer window);

#endif //PART_4_GUIUTILS_H
