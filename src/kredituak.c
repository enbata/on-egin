#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "modSarrera.h"

static void btmAdos()
{
	//gtk_main_quit();
	gtk_widget_destroy(frmKredituak);
}

kredituak()
{
	GtkWidget *frame;
	GtkWidget *alignment;
	GtkWidget *vBox;
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *vBoxNagusia;
	
	//frmKredituak = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	frmKredituak = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_widget_set_size_request (frmKredituak, 348, 200);
	gtk_window_set_title (GTK_WINDOW (frmKredituak), ("Kredituak"));
	gtk_window_set_position (GTK_WINDOW (frmKredituak), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmKredituak), TRUE);
	gtk_window_set_type_hint (GTK_WINDOW (frmKredituak), GDK_WINDOW_TYPE_HINT_DIALOG);
	
	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_container_add (GTK_CONTAINER (frmKredituak), frame);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_container_set_border_width (GTK_CONTAINER (alignment), 2);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 5, 5, 5, 5);
	
	vBoxNagusia = gtk_vbox_new (TRUE, 13);
	gtk_widget_show (vBoxNagusia);
	gtk_container_add (GTK_CONTAINER (alignment), vBoxNagusia);
	gtk_container_set_border_width (GTK_CONTAINER (vBoxNagusia), 5);
	
	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (vBoxNagusia), frame, TRUE, TRUE, 0);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 0, 0, 12, 0);
	
	vBox = gtk_vbox_new (TRUE, 0);
	gtk_widget_show (vBox);
	gtk_container_add (GTK_CONTAINER (alignment), vBox);
	
	labela = gtk_label_new ("<b>Manex Agirre Onandia</b>");
	gtk_widget_show (labela);
	gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	
	labela = gtk_label_new ("e-mail: jaimejasmi@gmail.com");
	gtk_widget_show (labela);
	gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	
	labela = gtk_label_new ("<b>Bertsio librearen egilea</b>");
	gtk_widget_show (labela);
	gtk_frame_set_label_widget (GTK_FRAME (frame), labela);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	
	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (vBoxNagusia), frame, TRUE, TRUE, 0);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 0, 0, 12, 0);
	
	vBox = gtk_vbox_new (TRUE, 0);
	gtk_widget_show (vBox);
	gtk_container_add (GTK_CONTAINER (alignment), vBox);
	
	labela = gtk_label_new ("<b>Aitor Sarriegi</b>");
	gtk_widget_show (labela);
	gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	
	labela = gtk_label_new ("e-mail: asarriegi@gmail");
	gtk_widget_show (labela);
	gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	
	labela = gtk_label_new ("<b>Jatorrizko bertsioaren egilea</b>");
	gtk_widget_show (labela);
	gtk_frame_set_label_widget (GTK_FRAME (frame), labela);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	
	botoia = gtk_button_new_from_stock ("gtk-ok");
	gtk_widget_show (botoia);
	gtk_box_pack_start (GTK_BOX (vBoxNagusia), botoia, FALSE, FALSE, 0);
	gtk_widget_set_size_request (botoia, -1, 30);

	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);

	/* Leihoa neurrira egokitu */
	/*GdkScreen *lehioa = gtk_window_get_screen(GTK_WINDOW(frmElkarteGastronomikoa));
	gint luzera = gdk_screen_get_height(lehioa);
	gint zabalera = gdk_screen_get_width(lehioa);
	gtk_window_resize(GTK_WINDOW(frmKredituak), zabalera*0.2,luzera*0.2);
	printf ("Zabalera: %d, Altuera: %d\n",zabalera*0.3,luzera*0.1);*/

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmKredituak);
	//gtk_main();
}
