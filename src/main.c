#define _POSIX_C_SOURCE 200809L
#include "guiUtils.h"
#include <pthread.h>
#include <signal.h>
// gtk_main has been put into a separate function so that it can 
// be called as a separate thread.
void *runGtkLoop(void *parameter) {
    gtk_main();
    system("aplay sounds/shutdown.wav");
    system("sudo ps aux | sudo grep python | sudo grep -v \"grep python\" | \
sudo awk '{print $2}' | sudo xargs kill -9");
    exit(0);
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
    // pthread_create(&threadPython, NULL, runPythonScript, &instrument);
    runPythonScript();
    isChangingIns = 0;

    while (1) {
//	char test;
//	if(fscanf(pyPipe, "%d", &test) != 1) {
//            continue;
//        }
        char inputString[9];
        fgets(inputString, 100, pyPipe);
        //fflush(pyPipe);
        if(isChangingIns || !*inputString || !*(inputString + 5)) {
            continue;
        }

        printf("%s\n", inputString);
        if(strncmp(inputString, "input", 5)) {
            continue;
        }

        char action = inputString[5];// either 't' touched or 'r' released
        // If this is some other junk console output, skip this iteration
        //if((action != 't' && action != 'r') || !isdigit(inputString[6])) {
        //    continue;
        //}
        char *inputStringAfterFirstLetter = inputString + 6;
        int pin = atoi(inputStringAfterFirstLetter);
        printf("%d\n", pin);
        if (action == 't') {
            turn_light_on(pin);
        } else {
            // Else it must be released
            turn_light_off(pin);
        }
    }
}
