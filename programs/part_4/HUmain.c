#define _POSIX_C_SOURCE 200809L
#include "guiUtils.h"
#include <pthread.h>
#include <signal.h>

#define MAX_DIGITS_NUMBER_OF_MODES 15

pthread_t threadGui;

void runPythonScript() {
    char *scriptAddress = "HUauxPython.py";
    char systemCall[strlen(scriptAddress) + MAX_DIGITS_NUMBER_OF_MODES];
    sprintf(systemCall, "sudo python %s %d", scriptAddress, 0);
    printf("%s\n", systemCall);
    system(systemCall);
}

// gtk_main has been put into a separate function so that it can 
// be called as a separate thread.
void *runGtkLoop(void *parameter) {
    gtk_main();
    system("sudo ps aux | sudo grep python | sudo grep -v \"grep python\" | \
sudo awk '{print $2}' | sudo xargs kill -9");
    exit(0);
}

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

    // Add the boxs to the windowg.
    gtk_container_add(GTK_CONTAINER(widgetContainer), vBoxRadioButtons);
    gtk_container_add(GTK_CONTAINER(widgetContainer), vBoxVolumeControl);
    gtk_container_add(GTK_CONTAINER(window), widgetContainer);

    // Show the window
    gtk_widget_show_all(window);
    
    // Enter the main GUI loop
    pthread_create(&threadGui, NULL, runGtkLoop, NULL);
    // Send this thread to the Python script
    runPythonScript();
}