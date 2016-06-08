#include <gtk/gtk.h>
#include <stdio.h>

// Declare widgets as global variables
GtkWidget *window;
GtkWidget *vBox;
GtkWidget *halign;
GtkWidget *rb1;
GtkWidget *rb2;
GtkWidget *rb3;
GtkWidget *image;

void toggle_title(GtkRadioButton *widget, gpointer window) {

	// Need this check as function is also called for the deselected button.
	if(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		return;
	}
	
	// Get the button's label and set the sound mode as appropriate.
	const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
	switch(*label) {
		case 'D' :
			gtk_window_set_title(GTK_WINDOW(window), "Sound mode: Drums");
			break;
		case 'P' :
			gtk_window_set_title(GTK_WINDOW(window), "Sound mode: Piano");
			break;
		case 'A' :
			gtk_window_set_title(GTK_WINDOW(window), "Sound mode: Airhorns");
			break;
		default:
			printf("Somethings gone wrong\n");
			break;	
	}
}

int main(int argc, char** argv) {
	

	// Initialise GTK+
  	gtk_init(&argc, &argv);

	// Set up the window
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
  	gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
  	gtk_window_set_title(GTK_WINDOW(window), "Sound mode: Drums");

	// Set up alignment box for radio buttons. Align to center top.
  	halign = gtk_alignment_new(0.5, 0, 0, 0);
  
	// Create radio buttons with their labels. The first one's group is 
	// unspecified and the others are placed into the same group as rb1.
  	rb1 = gtk_radio_button_new_with_label(NULL, "Drums");
  	rb2 = gtk_radio_button_new_with_label_from_widget
			(GTK_RADIO_BUTTON(rb1), "Piano");
  	rb3 = gtk_radio_button_new_with_label_from_widget
			(GTK_RADIO_BUTTON(rb2), "Airhorn");
	// Set tooltips for the radio buttons
	gtk_widget_set_tooltip_text(rb1, "Change to drum pad mode");
  	gtk_widget_set_tooltip_text(rb2, "Change to piano mode");
	gtk_widget_set_tooltip_text(rb3, "Change to airhorn mode");

	// Create new vertical box with 1 pixel between elements as default.
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	// Pack the radio buttons into vBox.
  	gtk_box_pack_start(GTK_BOX(vBox), rb1, TRUE, TRUE, 2);
  	gtk_box_pack_start(GTK_BOX(vBox), rb2, TRUE, TRUE, 2);
  	gtk_box_pack_start(GTK_BOX(vBox), rb3, TRUE, TRUE, 2);

	// When the buttons are clicked call toggle_title().
  	g_signal_connect(rb1, "clicked", 
      		G_CALLBACK(toggle_title), (gpointer) window);
  	g_signal_connect(rb2, "clicked", 
      		G_CALLBACK(toggle_title), (gpointer) window);
  	g_signal_connect(rb3, "clicked", 
      		G_CALLBACK(toggle_title), (gpointer) window);

	// When the window is closed exit the program.
  	g_signal_connect(window, "destroy",
      		G_CALLBACK(gtk_main_quit), NULL);

	// Add the box to the alignment container, and add that to the window.
  	gtk_container_add(GTK_CONTAINER(window), halign);
  	gtk_container_add(GTK_CONTAINER(halign), vBox);
	// Show the window
  	gtk_widget_show_all(window);
	
	// Enter the main loop
  	gtk_main();

  	return 0;
}
