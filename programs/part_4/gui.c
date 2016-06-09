#include "gui.h

void gui_init() {
	

	// Initialise GTK+
  	gtk_init(0, NULL);

	// Set up the window
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
  	gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
  	gtk_window_set_title(GTK_WINDOW(window), "Sound mode: Drums");

	// Set up alignment box for radio buttons. Align to center top.
  	halign = gtk_alignment_new(0.5, 0, 0, 0);

    // Create new vertical box with 1 pixel between elements as default.
    vBoxRadioButtons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    // Create the radio buttons and pack the into vBoxRadioButtons.
    create_radio_buttons(GTK_BOX(vBoxRadioButtons));

	// When the window is closed exit the program.
  	g_signal_connect(window, "destroy",
      		G_CALLBACK(gtk_main_quit), NULL);

	// Add the box to the alignment container, and add that to the window.
  	gtk_container_add(GTK_CONTAINER(window), halign);
  	gtk_container_add(GTK_CONTAINER(halign), vBoxRadioButtons);
	// Show the window
  	gtk_widget_show_all(window);
	
	// Enter the main loop
  	gtk_main();
}
