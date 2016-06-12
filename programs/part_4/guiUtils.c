#include "guiUtils.h"

void create_loading_screen(GtkBox *vBox) {
    // Set up the loading gif
    animation = gdk_pixbuf_animation_new_from_file("hexLoader.gif", NULL);
    loadingGif = gtk_image_new_from_animation(animation);

    // Create label for loading screen
    loadingLabel = gtk_label_new(LOADING_LABEL);

    // Set up tooltips
    gtk_widget_set_tooltip_text(loadingGif, LOADING_TOOLTIP);
    gtk_widget_set_tooltip_text(loadingLabel, LOADING_LABEL);

    // Pack the loading screen into vBox.
    gtk_box_pack_start(vBox, loadingGif, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(vBox, loadingLabel, TRUE, TRUE, DEFAULT_PADDING);
}


void create_radio_buttons(GtkBox *vBox) {
    // Create radio buttons with their labels. The first one's group is
    // unspecified and the others are placed into the same group as rb1.
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

    // Set tooltip for the volume control
    gtk_widget_set_tooltip_text(vc, VC_TOOLTIP);

    // Create label
    volumeLabel = gtk_label_new(VOLUME_LABEL);

    // When volume is changed vall adjust_volume
    g_signal_connect(vc, "value-changed",
                     G_CALLBACK(adjust_volume), (gpointer) window);

    // Pack the volume control into vBox.
    gtk_box_pack_start(vBox, vc, TRUE, TRUE, DEFAULT_PADDING);
    gtk_box_pack_start(vBox, volumeLabel, TRUE, TRUE, DEFAULT_PADDING);
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
