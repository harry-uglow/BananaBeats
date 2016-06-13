#include <stdlib.h>
#include "guiUtils.h"

int main(void) {
// Initialise GTK+
    gtk_init(0, NULL);

    // Set up the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1000);
    gtk_window_set_title(GTK_WINDOW(window), "Loading...");

    // Create new box to hold the loading widgets
    loadingContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    gtk_widget_set_halign(loadingContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loadingContainer, GTK_ALIGN_CENTER);
/*
    // Create loading screen
    create_loading_screen(GTK_BOX(loadingContainer));

    gtk_container_add(GTK_CONTAINER(window), loadingContainer);
    gtk_widget_show_all(window);

    gtk_main();

    // LOOP UNTIL LOADING FINISHED
    finishedLoading = 0;
    while(!finishedLoading) { finishedLoading = 0; }
    */
    gtk_window_set_title(GTK_WINDOW(window), "Sound mode: Drums");
    
    
    hBoxLights = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 80);
    gtk_widget_set_halign(hBoxLights, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(hBoxLights, GTK_ALIGN_CENTER);


	widgetContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 300);
    gtk_widget_set_halign(widgetContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widgetContainer, GTK_ALIGN_CENTER);

    // Create new vertical box with 1 pixel between elements as default.
    vBoxRadioButtons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 100);
    gtk_widget_set_halign(vBoxRadioButtons, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxRadioButtons, GTK_ALIGN_CENTER);

    // Create new vertical box for volume control
    vBoxVolumeControl = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    gtk_widget_set_halign(vBoxVolumeControl, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxVolumeControl, GTK_ALIGN_CENTER);


    controlContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 700);
    gtk_widget_set_halign(controlContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(controlContainer, GTK_ALIGN_CENTER);

     // Create the radio buttons and pack the into vBoxRadioButtons.
    create_radio_buttons(GTK_BOX(vBoxRadioButtons));

    // Create the volume control and pack it into vBoxVolumeControl
    create_volume_control(GTK_BOX(vBoxVolumeControl));

    // Create the 12 lights and pack it into hBoxLights
    create_twelve_lights(GTK_BOX(hBoxLights));

    // When the window is closed exit the program.
    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);


    // Add the boxs to the window.
    gtk_container_add(GTK_CONTAINER(controlContainer), vBoxRadioButtons);
    gtk_container_add(GTK_CONTAINER(controlContainer), vBoxVolumeControl);
    gtk_container_add(GTK_CONTAINER(widgetContainer), controlContainer);
    gtk_container_add(GTK_CONTAINER(widgetContainer), hBoxLights);
    gtk_container_add(GTK_CONTAINER(window), widgetContainer);

    // Show the window
    gtk_widget_show_all(window);

    // Enter the main loop
    gtk_main();
    return 0;
}
