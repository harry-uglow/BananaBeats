#define _POSIX_C_SOURCE 200809L
#include "guiUtils.h"
#include <pthread.h>
#include <signal.h>

#define MAX_DIGITS_NUMBER_OF_MODES 15

pthread_t threadPython;
pthread_t threadGui;
pthread_t threadInstrLoop;

int previous_instrument;
int current_instrument;

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
    system("aplay sounds/shutdown.wav");
    system("sudo ps aux | sudo grep python | sudo grep -v \"grep python\" | \
sudo awk '{print $2}' | sudo xargs kill -9");
    exit(0);
}

void *instrLoop(void *parameter) {
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
            sleep(2);
        }
    }
}

int main(void) {
	// Initialise GTK+
    gtk_init(0, NULL);

    // Initialise and run the loading screen
    run_loading_screen();
    
    // Initialise the main window
    initialise_main_window();
    
    // Set up main window widgets
    set_up_main_window();
    
    // Enter the main GUI loop
    pthread_create(&threadGui, NULL, runGtkLoop, NULL);
    
    previous_instrument = (int) instrument;
    current_instrument = (int) instrument;
    
    pthread_create(&threadPython, NULL, runPythonScript, &current_instrument);
    pthread_create(&threadInstrLoop, NULL, instrLoop, NULL);
    
    while (1) {
        char inputString[4];
        scanf("%s", inputString);
        printf("%s\n" ,inputString);
        char action = inputString[0]; // either 't' touched or 'r' released
        char *inputStringAfterFirstLetter = inputString + 1;
        int pin = atoi(inputStringAfterFirstLetter);
        printf("%d\n", pin);
        if (action == 't') {
            turn_light_on(pin);
        } else {
            // Else it must be released
            turn_light_off(pin);
        }
        usleep(300);
    }
}
