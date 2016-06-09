#include "guiUtils.h"
#include <stdlib.h>

int main(void) {
    // Initialise GTK+
    gtk_init(0, NULL);

    // Set up the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 250);
    gtk_window_set_title(GTK_WINDOW(window), "Instrument: Drums");

    // Create new box to hold the widgets
    widgetContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
    gtk_widget_set_halign(widgetContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widgetContainer, GTK_ALIGN_CENTER);
    
    // Create new vertical box with 1 pixel between elements as default.
    vBoxRadioButtons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_halign(vBoxRadioButtons, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxRadioButtons, GTK_ALIGN_CENTER);

    // Create new vertical box for volume control
    vBoxVolumeControl = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
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

    enum Instrument previous_instrument = DRUMS; // Default instrument
    int current_instrument = (int) instrument;

    while (1) {
        if (current_instrument != previous_instrument) {
           // TODO: Stop current python process

           // Run new process with new sound mode
           switch (current_instrument) {
               // DRUMS
               case 0; 
                   system("auxPython.py 0");
                   break;
               case 1: 
                   system("auxPython.py 1");
                   break;
               case 2: 
                   system("auxPython.py 2");
                   break;
               default:
                   printf("Invalid sound mode.");
                   break; 
           }
        }
    }

    return EXIT_SUCCESS;
}
