#define _POSIX_C_SOURCE 200809L
#include "guiUtils.h"
#include <pthread.h>
#include <signal.h>

#define MAX_DIGITS_NUMBER_OF_MODES 15

pthread_t threadPython;
pthread_t threadGui;

void *runPythonScript(void *pInstrument) {
    int newInstrument = *((int *) pInstrument);
    char *scriptAddress = "auxPython.py";
    char systemCall[strlen(scriptAddress) + MAX_DIGITS_NUMBER_OF_MODES];
    sprintf(systemCall, "sudo python %s %d", scriptAddress, newInstrument);
    printf("%s\n", systemCall);
    system(systemCall);
    return 0;
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
printf("Started\n");
    // Initialise GTK+
    gtk_init(0, NULL);

    // Set up the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 250);
    gtk_window_set_title(GTK_WINDOW(window), "Instrument: Drums");
	
	// Set up and create menu 
	// TODO: extract this out to guiUtils.c later
	menuBox = gtk_box_new(FALSE, 0);

	menuBar = gtk_menu_bar_new();
	fileMenu = gtk_menu_new();

	file = gtk_menu_item_new_with_label("File");
	about = gtk_menu_item_new_with_label("About");
	quit = gtk_menu_item_new_with_label("Quit");


	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), about);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), file);
    gtk_box_pack_start(GTK_BOX(menuBox), menuBar, FALSE, FALSE, 0);

    // Banana icon
    GdkPixbuf *pIcon = gdk_pixbuf_new_from_file_at_size("icon.png", 256, 256,
                                                        NULL);
    gtk_window_set_icon(GTK_WINDOW(window), pIcon);

    // Create new box to hold the widgets
    widgetContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
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

	// Create new box to hold the control widgets (radio buttons and sound)
	controlContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 70);
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

  	// When 'Quit' is clicked, exit the program.
    g_signal_connect(G_OBJECT(quit), "activate",
                    G_CALLBACK(gtk_main_quit), NULL);

    // Add the boxs to the window.
    gtk_container_add(GTK_CONTAINER(controlContainer), vBoxRadioButtons);
    gtk_container_add(GTK_CONTAINER(controlContainer), vBoxVolumeControl);
    gtk_container_add(GTK_CONTAINER(widgetContainer), menuBox);
    gtk_container_add(GTK_CONTAINER(widgetContainer), hBoxLights);
    gtk_container_add(GTK_CONTAINER(widgetContainer), controlContainer);
    gtk_container_add(GTK_CONTAINER(window), widgetContainer);

    // Show the window
    gtk_widget_show_all(window);
    
    // Enter the main GUI loop
    pthread_create(&threadGui, NULL, runGtkLoop, NULL);
    
    int previous_instrument = (int) instrument;
    int current_instrument = (int) instrument;
    
    pthread_create(&threadPython, NULL, runPythonScript, &current_instrument);
    
    while (1) {
        current_instrument = (int) instrument;
        // If there is a change
        if (current_instrument != previous_instrument) {
            // Stop Python process
            system("sudo ps aux | sudo grep python | sudo grep -v \"grep python\" | \
sudo awk '{print $2}' | sudo xargs kill -9");
            pthread_kill(threadPython, SIGQUIT);
            // Create new Python process
            pthread_create(&threadPython, NULL, runPythonScript, &current_instrument);
            previous_instrument = current_instrument;
        }
    }
}
