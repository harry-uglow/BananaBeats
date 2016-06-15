#include "guiUtils.h"

void create_twelve_lights(GtkBox *hBox) {
    // All lights turned off at first
    for(int i = 0; i < 12; i++) {
        turn_light_off(i);
    }
    
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
}

void turn_light_on(int pin) {
    switch (pin) {
        case 0:
            light0 = gtk_image_new_from_file("Images/on.png");
            break;
        case 1:
            light1 = gtk_image_new_from_file("Images/on.png");
            break;
        case 2:
            light2 = gtk_image_new_from_file("Images/on.png");
            break;
        case 3:
            light3 = gtk_image_new_from_file("Images/on.png");
            break;
        case 4:
            light4 = gtk_image_new_from_file("Images/on.png");
            break;
        case 5:
            light5 = gtk_image_new_from_file("Images/on.png");
            break;
        case 6:
            light6 = gtk_image_new_from_file("Images/on.png");
            break;
        case 7:
            light7 = gtk_image_new_from_file("Images/on.png");
            break;
        case 8:
            light8 = gtk_image_new_from_file("Images/on.png");
            break;
        case 9:
            light9 = gtk_image_new_from_file("Images/on.png");
            break;
        case 10:
            light10 = gtk_image_new_from_file("Images/on.png");
            break;
        case 11:
            light11 = gtk_image_new_from_file("Images/on.png");
            break;
        default: 
            // Should not reach this stage if correct pin is selected
            break;
    }
    gtk_widget_show_all(window);
}

void turn_light_off(int pin) {
    switch (pin) {
        case 0:
            light0 = gtk_image_new_from_file("Images/off.png");
            break;
        case 1:
            light1 = gtk_image_new_from_file("Images/off.png");
            break;
        case 2:
            light2 = gtk_image_new_from_file("Images/off.png");
            break;
        case 3:
            light3 = gtk_image_new_from_file("Images/off.png");
            break;
        case 4:
            light4 = gtk_image_new_from_file("Images/off.png");
            break;
        case 5:
            light5 = gtk_image_new_from_file("Images/off.png");
            break;
        case 6:
            light6 = gtk_image_new_from_file("Images/off.png");
            break;
        case 7:
            light7 = gtk_image_new_from_file("Images/off.png");
            break;
        case 8:
            light8 = gtk_image_new_from_file("Images/off.png");
            break;
        case 9:
            light9 = gtk_image_new_from_file("Images/off.png");
            break;
        case 10:
            light10 = gtk_image_new_from_file("Images/off.png");
            break;
        case 11:
            light11 = gtk_image_new_from_file("Images/off.png");
            break;
        default: 
            // Should not reach this stage if correct pin is selected
            break;
    }
    gtk_widget_show_all(window);
}

void create_loading_screen(GtkBox *vBox) {
    // Set up the loading gif
    animation = gdk_pixbuf_animation_new_from_file("Images/hexLoader.gif", NULL);
    loadingGif = gtk_image_new_from_animation(animation);

    // Set up tooltips
    gtk_widget_set_tooltip_text(loadingGif, LOADING_TOOLTIP);

    // Pack the loading screen into vBox.
    gtk_box_pack_start(vBox, loadingGif, TRUE, TRUE, DEFAULT_PADDING);
}

void create_radio_buttons(GtkBox *vBox) {
    // Create radio buttons with their labels (No labels). The first one's 
    // group is unspecified and the others are placed into the same group as rb1.
    rb1 = gtk_radio_button_new_with_label(NULL, RB1_LABEL);
    rb2 = gtk_radio_button_new_with_label_from_widget
            (GTK_RADIO_BUTTON(rb1), RB2_LABEL);
    rb3 = gtk_radio_button_new_with_label_from_widget
            (GTK_RADIO_BUTTON(rb1), RB3_LABEL);

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

    g_object_set(vc, "width-request", VOLUME_CONTROL_WIDTH, NULL);

    // Create label for loading screen
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
            gtk_window_set_title(GTK_WINDOW(window), WIN_TITLE_RB1);
            break;
        case 'P' :
            instrument = PIANO;
            gtk_window_set_title(GTK_WINDOW(window), WIN_TITLE_RB2);
            break;
        case 'M' :
            instrument = MARIO;
            gtk_window_set_title(GTK_WINDOW(window), WIN_TITLE_RB3);
            break;
        default:
            printf("Somethings gone wrong\n");
            break;
    }
}

void adjust_volume(GtkScale *vc, gpointer window) {
    currentVolume = gtk_range_get_value(GTK_RANGE(vc));
    char *volumeCmdPre = "amixer set PCM -- ";
    int sizeVolumeCmdPre = strlen(volumeCmdPre);
    char volumeCmd[sizeVolumeCmdPre + MAX_DIGITS_VOLUME_PERCENTAGE + 2];
    sprintf(volumeCmd, "%s%d%%", volumeCmdPre, (int) currentVolume);
    system(volumeCmd);
}
