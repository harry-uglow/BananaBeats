#ifndef PART_4_GUIUTILS_H
#define PART_4_GUIUTILS_H

// Define string constants
#define RB1_LABEL "Drums"
#define RB2_LABEL "Piano"
#define RB3_LABEL "Airhorns"
#define RB_TOOLTIP_PREFIX "Change instrument to: "
#define WINDOW_TITLE_PREFIX "Instrument: "

// Declare widgets as global variables
GtkWidget *window;
GtkWidget *vBoxRadioButtons;
GtkWidget *halign;
GtkWidget *rb1;
GtkWidget *rb2;
GtkWidget *rb3;
GtkWidget *image;

void create_radio_buttons(void);
void toggle_sound_mode(GtkRadioButton *widget, gpointer window);

#endif //PART_4_GUIUTILS_H
