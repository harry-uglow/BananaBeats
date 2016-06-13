#define _POSIX_C_SOURCE 200809L
#include "guiUtils.h"
#include <pthread.h>
#include <signal.h>

#define MAX_DIGITS_NUMBER_OF_MODES 15

pthread_t threadPython;
pthread_t threadStartupSound;
pthread_t threadGui;

void *playStartupSound(void *pInstrument) {
    system("aplay sounds/startup.wav");
    return 0;
}

void *runPythonScript(void *pInstrument) {
    int newInstrument = *((int *) pInstrument);
    char *scriptAddress = "auxPython.py";
    char systemCall[strlen(scriptAddress) + MAX_DIGITS_NUMBER_OF_MODES];
    sprintf(systemCall, "python %s %d", scriptAddress, newInstrument);
    printf("%s\n", systemCall);
    system(systemCall);
    return 0;
}

// gtk_main has been put into a separate function so that it can 
// be called as a separate thread.
void *runGtkLoop(void *parameter) {
    gtk_main();
    system("aplay sounds/shutdown.wav");
    system("sudo ps aux | sudo grep python | sudo grep -v \"grep python\" | \
sudo awk '{print $2}' | sudo xargs kill -9");
    exit(0);
}

gboolean quitLoadingScreen(gpointer data) {
    gtk_widget_destroy((GtkWidget*)data);
    gtk_widget_show_all(window);
    return (FALSE);
}

int main(void) {
	GtkWidget *image;
    GtkWidget *layout;

	// Initialise GTK+
    gtk_init(0, NULL);
	 
    // Create loading window
    loadingWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (loadingWindow), "Loading...");
    gtk_container_set_border_width (GTK_CONTAINER (loadingWindow), 0);
    gtk_widget_set_size_request (loadingWindow, 400, 300);
    gtk_window_set_decorated(GTK_WINDOW (loadingWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(loadingWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(loadingWindow), FALSE);
    
    // Create new box to hold the loading widgets
    loadingContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    gtk_widget_set_halign(loadingContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loadingContainer, GTK_ALIGN_CENTER);

    // Create loading screen
    create_loading_screen(GTK_BOX(loadingContainer));

    gtk_container_add(GTK_CONTAINER(loadingWindow), loadingContainer);
    gtk_widget_show_all(loadingWindow);

    // Enter the main loop
    g_timeout_add(100, quitLoadingScreen, loadingWindow);

    // Set up the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1000);
    gtk_window_set_title(GTK_WINDOW(window), "Instrument: Drums");

	layout = gtk_layout_new(NULL, NULL);

    image = gtk_image_new_from_file("Images/background.png");
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);
    
    // Create the 12 lights and pack it into 
    hBoxLights = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
    gtk_widget_set_halign(hBoxLights, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(hBoxLights, GTK_ALIGN_CENTER);

    // Create new vertical box to hold the widgets
	widgetContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 195);
    gtk_widget_set_halign(widgetContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widgetContainer, GTK_ALIGN_CENTER);

    // Create new vertical box with 1 pixel between elements as default.
    vBoxRadioButtons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 45);
    gtk_widget_set_halign(vBoxRadioButtons, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxRadioButtons, GTK_ALIGN_CENTER);

    // Create new vertical box for volume control
    vBoxVolumeControl = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(vBoxVolumeControl, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxVolumeControl, GTK_ALIGN_CENTER);

    // Create new box to hold the control widgets (radio buttons and sound)
    controlContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1095);
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

    // Add the boxes to the window.
    gtk_container_add(GTK_CONTAINER(controlContainer), vBoxRadioButtons);
    gtk_container_add(GTK_CONTAINER(controlContainer), vBoxVolumeControl);
    gtk_container_add(GTK_CONTAINER(widgetContainer), hBoxLights);
    // Layout of widgets over background image aligned
	gtk_layout_put(GTK_LAYOUT(layout), controlContainer, 165, 320);
    gtk_layout_put(GTK_LAYOUT(layout), widgetContainer, 65, 690);
	gtk_container_add(GTK_CONTAINER(window), layout);

    // Windows starup sound
    pthread_create(&threadStartupSound, NULL, playStartupSound, NULL);
    
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
