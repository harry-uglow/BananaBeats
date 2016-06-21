#include "guiUtils.h"

void run_loading_screen(void) {
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
 
    // Display loading screen
    gtk_container_add(GTK_CONTAINER(loadingWindow), loadingContainer);
    gtk_widget_show_all(loadingWindow);

    // Timing for loading screen
    g_timeout_add(6000, quitLoadingScreen, loadingWindow);
}

gboolean quitLoadingScreen(gpointer data) {
    // Destroy loading screen and display main gui window
    gtk_widget_destroy((GtkWidget *) data);
    gtk_widget_show_all(window);
    return (FALSE);
}

void initialise_main_window(void) {
    // Set up the main gui window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1000);
    gtk_window_set_title(GTK_WINDOW(window), "BananaBeats");
}

void set_up_main_window(void) {    
    // Create background image 
    create_background();

    // Create banana icon 
    GdkPixbuf *pIcon = gdk_pixbuf_new_from_file_at_size("images/icon.png", 256, 256,NULL);
    gtk_window_set_icon(GTK_WINDOW(window), pIcon);
 
    // Create horizontal box for current sound mode icon 
    iconContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(iconContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(iconContainer, GTK_ALIGN_CENTER);

    // Create horizontal box for the 12 lights 
    hBoxLights = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 45);
    gtk_widget_set_halign(hBoxLights, GTK_ALIGN_END);
    gtk_widget_set_valign(hBoxLights, GTK_ALIGN_CENTER);
    gtk_box_set_homogeneous(GTK_BOX(hBoxLights), TRUE);

    // Create new vertical box to hold the widgets
	widgetContainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 200);
    gtk_widget_set_halign(widgetContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widgetContainer, GTK_ALIGN_CENTER);

    // Create new vertical box for the radio buttons
    vBoxRadioButtons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    gtk_widget_set_halign(vBoxRadioButtons, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxRadioButtons, GTK_ALIGN_CENTER);

    // Create new vertical box for volume control
    vBoxVolumeControl = gtk_box_new(GTK_ORIENTATION_VERTICAL, 80);
    gtk_widget_set_halign(vBoxVolumeControl, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vBoxVolumeControl, GTK_ALIGN_CENTER);

    // Create new box to hold the control widgets (radio buttons and sound)
    controlContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 915);
    gtk_widget_set_halign(controlContainer, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(controlContainer, GTK_ALIGN_CENTER);

     // Create the radio buttons and pack them into vBoxRadioButtons.
    create_radio_buttons(GTK_BOX(vBoxRadioButtons));
    
    // Set up current sound mode icon and pack it into iconContainer
    create_sound_mode(GTK_BOX(iconContainer));

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
	gtk_layout_put(GTK_LAYOUT(layout), controlContainer, 215, 320);
    gtk_layout_put(GTK_LAYOUT(layout), iconContainer, 665, 150);
    gtk_layout_put(GTK_LAYOUT(layout), widgetContainer, 80, 690);
	gtk_container_add(GTK_CONTAINER(window), layout);

    // Play windows startup sound when gui is opened
    pthread_create(&threadStartupSound, NULL, playStartupSound, NULL);
}

void create_background(void) {
    layout = gtk_layout_new(NULL, NULL);
    background = gtk_image_new_from_file("images/background.png");
    gtk_layout_put(GTK_LAYOUT(layout), background, 0, 0);
}

void *playStartupSound(void *pInstrument) {
    system("aplay sounds/startup.wav");
    return 0;
}

void create_sound_mode(GtkBox *hBox) {
    // Set up image icon for default current sound mode
    drumsIcon = gtk_image_new_from_file("images/drums.png");

    // Set default icon to drums
    currentSoundMode = drumsIcon;   

    // Pack the current sound mode image into hBox
    gtk_box_pack_start(hBox, currentSoundMode, TRUE, TRUE, DEFAULT_PADDING);
}

void create_twelve_lights(GtkBox *hBox) {
    //Set images
    light0 = gtk_image_new_from_file("images/off.png");
    light1 = gtk_image_new_from_file("images/off.png");
    light2 = gtk_image_new_from_file("images/off.png");
    light3 = gtk_image_new_from_file("images/off.png");
    light4 = gtk_image_new_from_file("images/off.png");
    light5 = gtk_image_new_from_file("images/off.png");
    light6 = gtk_image_new_from_file("images/off.png");
    light7 = gtk_image_new_from_file("images/off.png");
    light8 = gtk_image_new_from_file("images/off.png");
    light9 = gtk_image_new_from_file("images/off.png");
    light10 = gtk_image_new_from_file("images/off.png");
    light11 = gtk_image_new_from_file("images/off.png");

    // Set tooltips
    gtk_widget_set_tooltip_text(light0, "Pin 0");
    gtk_widget_set_tooltip_text(light1, "Pin 1");
    gtk_widget_set_tooltip_text(light2, "Pin 2");
    gtk_widget_set_tooltip_text(light3, "Pin 3");
    gtk_widget_set_tooltip_text(light4, "Pin 4");
    gtk_widget_set_tooltip_text(light5, "Pin 5");
    gtk_widget_set_tooltip_text(light6, "Pin 6");
    gtk_widget_set_tooltip_text(light7, "Pin 7");
    gtk_widget_set_tooltip_text(light8, "Pin 8");
    gtk_widget_set_tooltip_text(light9, "Pin 9");
    gtk_widget_set_tooltip_text(light10, "Pin 10");
    gtk_widget_set_tooltip_text(light11, "Pin 11");

    // Pack the lights into hBox
    gtk_box_pack_start(hBox, light0, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light1, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light2, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light3, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light4, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light5, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light6, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light7, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light8, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light9, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light10, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(hBox, light11, TRUE, TRUE, DEFAULT_PADDING);

    printf("Lights created\n");
}

void turn_light_on(int pin) {
    printf("Function on called with the %d pin.\n", pin);
    switch (pin) {
        case 0:
            gtk_image_set_from_file(GTK_IMAGE(light0), "images/on.png");
            break;
        case 1:
            gtk_image_set_from_file(GTK_IMAGE(light1), "images/on.png");
            break;
        case 2:
            gtk_image_set_from_file(GTK_IMAGE(light2), "images/on.png");
            break;
        case 3:
            gtk_image_set_from_file(GTK_IMAGE(light3), "images/on.png");
            break;
        case 4:
            gtk_image_set_from_file(GTK_IMAGE(light4), "images/on.png");
            break;
        case 5:
            gtk_image_set_from_file(GTK_IMAGE(light5), "images/on.png");
            break;
        case 6:
            gtk_image_set_from_file(GTK_IMAGE(light6), "images/on.png");
            break;
        case 7:
            gtk_image_set_from_file(GTK_IMAGE(light7), "images/on.png");
            break;
        case 8:
            gtk_image_set_from_file(GTK_IMAGE(light8), "images/on.png");
            break;
        case 9:
            gtk_image_set_from_file(GTK_IMAGE(light9), "images/on.png");
            break;
        case 10:
            gtk_image_set_from_file(GTK_IMAGE(light10), "images/on.png");
            break;
        case 11:
            gtk_image_set_from_file(GTK_IMAGE(light11), "images/on.png");
            break;
        default:
            // Should not reach this stage if correct pin is selected
            break;
    }
}

void turn_light_off(int pin) {
    printf("Function off called with the %d pin.\n", pin);
    switch (pin) {
        case 0:
            gtk_image_set_from_file(GTK_IMAGE(light0), "images/off.png");
            break;
        case 1:
            gtk_image_set_from_file(GTK_IMAGE(light1), "images/off.png");
            break;
        case 2:
            gtk_image_set_from_file(GTK_IMAGE(light2), "images/off.png");
            break;
        case 3:
            gtk_image_set_from_file(GTK_IMAGE(light3), "images/off.png");
            break;
        case 4:
            gtk_image_set_from_file(GTK_IMAGE(light4), "images/off.png");
            break;
        case 5:
            gtk_image_set_from_file(GTK_IMAGE(light5), "images/off.png");
            break;
        case 6:
            gtk_image_set_from_file(GTK_IMAGE(light6), "images/off.png");
            break;
        case 7:
            gtk_image_set_from_file(GTK_IMAGE(light7), "images/off.png");
            break;
        case 8:
            gtk_image_set_from_file(GTK_IMAGE(light8), "images/off.png");
            break;
        case 9:
            gtk_image_set_from_file(GTK_IMAGE(light9), "images/off.png");
            break;
        case 10:
            gtk_image_set_from_file(GTK_IMAGE(light10), "images/off.png");
            break;
        case 11:
            gtk_image_set_from_file(GTK_IMAGE(light11), "images/off.png");
            break;
        default:
            // Should not reach this stage if correct pin is selected
            break;
    }
}

void create_loading_screen(GtkBox *vBox) {
    // Set up the loading gif
    animation = gdk_pixbuf_animation_new_from_file("images/hexLoader.gif", NULL);
    loadingGif = gtk_image_new_from_animation(animation);

    // Set up tooltips
    gtk_widget_set_tooltip_text(loadingGif, LOADING_TOOLTIP);

    // Pack the loading screen into vBox.
    gtk_box_pack_start(vBox, loadingGif, TRUE, TRUE, DEFAULT_PADDING);
}

void create_radio_buttons(GtkBox *vBox) {
    // Create radio buttons with their labels (No labels). The first one's
    // group is unspecified and the others are placed into the same group as rb1
    rb1 = gtk_radio_button_new_with_label(NULL, RB1_LABEL);
    rb2 = gtk_radio_button_new_with_label_from_widget
            (GTK_RADIO_BUTTON(rb1), RB2_LABEL);
    rb3 = gtk_radio_button_new_with_label_from_widget
            (GTK_RADIO_BUTTON(rb1), RB3_LABEL);

    PangoFontDescription *font;
    GdkRGBA defaultColor = {1, 1, 1, 1};
    GdkRGBA selectedColor = {1, 1, 0, 1};
    GdkRGBA *white = &defaultColor;
    GdkRGBA *yellow = &selectedColor;
    font = pango_font_description_from_string("Montserrat 30");
    gtk_widget_override_font(rb1, font);
    gtk_widget_override_font(rb2, font);
    gtk_widget_override_font(rb3, font);
    gtk_widget_override_color(rb1, GTK_STATE_FLAG_NORMAL, white);
    gtk_widget_override_color(rb2, GTK_STATE_FLAG_NORMAL , white);
    gtk_widget_override_color(rb3, GTK_STATE_FLAG_NORMAL, white);
    gtk_widget_override_color(rb1, GTK_STATE_FLAG_ACTIVE, yellow);
    gtk_widget_override_color(rb2, GTK_STATE_FLAG_ACTIVE , yellow);
    gtk_widget_override_color(rb3, GTK_STATE_FLAG_ACTIVE, yellow);

    // Set tooltips for the radio buttons
    gtk_widget_set_tooltip_text(rb1, RB1_TOOLTIP);
    gtk_widget_set_tooltip_text(rb2, RB2_TOOLTIP);
    gtk_widget_set_tooltip_text(rb3, RB3_TOOLTIP);

    // When the buttons are clicked call toggle_title().
    g_signal_connect(rb1, "clicked",
                     G_CALLBACK(toggle_sound_mode), (gpointer) window);
    g_signal_connect(rb2, "clicked",
                     G_CALLBACK(toggle_sound_mode), (gpointer) window);
    g_signal_connect(rb3, "clicked",
                     G_CALLBACK(toggle_sound_mode), (gpointer) window);

    // Pack the radio buttons into vBox.
    gtk_box_pack_start(vBox, rb1, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(vBox, rb2, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(vBox, rb3, TRUE, TRUE, DEFAULT_PADDING);

    // Default instrument is the drums.
    instrument = DRUMS;
}

void create_volume_control(GtkBox *vBox) {
    // Create volume control with its label
    vc = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, VOLUME_MIN,
                                  VOLUME_MAX, VOLUME_STEP);

    // Set default start volume to 70
    gtk_range_set_value(GTK_RANGE(vc), DEFAULT_START_VOLUME);

    g_object_set(vc, "width-request", VOLUME_CONTROL_WIDTH, NULL);

    // Create empty label for alignment purposes
    loadingLabel = gtk_label_new(NULL);

    // Set tooltip for the volume control
    gtk_widget_set_tooltip_text(vc, VC_TOOLTIP);

    // When volume is changed vall adjust_volume
    g_signal_connect(vc, "value-changed",
                     G_CALLBACK(adjust_volume), (gpointer) window);

    // Pack the volume control into vBox.
    gtk_box_pack_start(vBox, vc, TRUE, TRUE, 20);
    gtk_box_pack_start(vBox, loadingLabel, TRUE, TRUE, 20);
}

void toggle_sound_mode(GtkRadioButton *widget, gpointer window) {
    // Need this check as function is also called for the deselected button.
    if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        return;
    }

    // Get the button's label and set the sound mode as appropriate.
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    switch(*label) {
        case 'D' :
            instrument = DRUMS;
            // Change current sound mode image to drums
            gtk_image_set_from_file(GTK_IMAGE(currentSoundMode), "images/drums.png");
            break;
        case 'P' :
            instrument = PIANO;
            // Change current sound mode image to piano
            gtk_image_set_from_file(GTK_IMAGE(currentSoundMode), "images/piano.png");
            break;
        case 'M' :
            instrument = MARIO;
            // Change current sound mode image to mario
            gtk_image_set_from_file(GTK_IMAGE(currentSoundMode), "images/mario.png");
            break;
        default:
            printf("Somethings gone wrong\n");
            break;
    }
    printf("Sound changed.\n");
    changePyProgram();
}

void adjust_volume(GtkScale *vc, gpointer window) {
    currentVolume = gtk_range_get_value(GTK_RANGE(vc));
    //char *volumeCmdPre = "amixer set PCM -- ";
    //int sizeVolumeCmdPre = strlen(volumeCmdPre);
    //char volumeCmd[sizeVolumeCmdPre + MAX_DIGITS_VOLUME_PERCENTAGE + 2];
    //sprintf(volumeCmd, "%s%d%%", volumeCmdPre, (int) currentVolume);
    //system(volumeCmd);
}

void changePyProgram(void) {
    // Stop Python process
    system("sudo ps aux | sudo grep python | sudo grep -v \"grep python\" | \
sudo awk '{print $2}' | sudo xargs kill -9");
    pclose(pyPipe);
    // Create new Python process
    runPythonScript();
}

void runPythonScript(void) {
    char *scriptAddress = "auxPython.py";
    char systemCall[strlen(scriptAddress) + MAX_DIGITS_NUMBER_OF_MODES];
    sprintf(systemCall, "sudo python %s %d", scriptAddress, instrument);
    // printf("%s\n", systemCall);
    char *r = "r";
    pyPipe = popen(systemCall, r);
    printf("Pipe set up\n");
}
