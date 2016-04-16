#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"

	GtkWidget *lblDiruaJarrita, *lblErreziboBidez, *lblTransferentziaBidez;
	GtkWidget *eventboxDiruaJarrita, *eventboxErreziboBidez, *eventboxTransferentziaBidez;

static void form_load()
{
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxDiruaJarrita, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblDiruaJarrita, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);

	sprintf(sOrdainModua, "%s", "Dirua jarrita");
}

static void lblDiruaJarrita_clicked()
{
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxDiruaJarrita, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblDiruaJarrita, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);

	sprintf(sOrdainModua, "%s", "Dirua jarrita");
}

static void lblErreziboBidez_clicked()
{
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_fg(lblDiruaJarrita, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxDiruaJarrita, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);

	sprintf(sOrdainModua, "%s", "Errezibo bidez");
}

static void lblTransferentziaBidez_clicked()
{
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_fg(lblDiruaJarrita, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblTransferentziaBidez, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxErreziboBidez, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxDiruaJarrita, GTK_STATE_NORMAL, &kolorea);

	sprintf(sOrdainModua, "%s", "Transferentzia bidez");
}

static void btmAdos()
{
	gtk_main_quit();
	gtk_widget_destroy(frmOrdainketa);
}

void ordainketa()
{
	GtkWidget *vBox;
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *frame;
	GtkWidget *alignment;

	/* Lehioa sortu eta definitu */
	frmOrdainketa = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_decorated(GTK_WINDOW(frmOrdainketa), FALSE);
// Joseba	gtk_window_set_type_hint (GTK_WINDOW(frmOrdainketa), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_modal(GTK_WINDOW(frmOrdainketa), TRUE);
	gtk_window_set_resizable (GTK_WINDOW(frmOrdainketa), FALSE);
	gtk_window_set_position (GTK_WINDOW(frmOrdainketa), GTK_WIN_POS_CENTER_ALWAYS);
// Joseba	gtk_window_set_transient_for (GTK_WINDOW(frmOrdainketa), GTK_WINDOW(frmKontua));

	/* Lehioaren egitura sortu eta egokitu */
	frame = gtk_frame_new("");
	gtk_container_add(GTK_CONTAINER(frmOrdainketa), frame);
	gdk_color_parse("#e4e1e3", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	vBox = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(alignment), vBox);

	/* Lehioko egiturak sortu eta kokatu */
	labela = gtk_label_new("<span size='xx-large'>Ordainketa - mota:</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	gtk_box_pack_start(GTK_BOX(vBox), labela, FALSE, FALSE, 5);

	lblDiruaJarrita = gtk_label_new("<span size='xx-large'> Dirua jarrita </span>");
	gtk_label_set_use_markup(GTK_LABEL(lblDiruaJarrita), TRUE);
	eventboxDiruaJarrita = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(eventboxDiruaJarrita), lblDiruaJarrita);
	gtk_box_pack_start(GTK_BOX(vBox), eventboxDiruaJarrita, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(eventboxDiruaJarrita), "button_press_event",
			G_CALLBACK(lblDiruaJarrita_clicked), NULL);
	gtk_widget_set_size_request(eventboxDiruaJarrita, 450, 50);

	lblErreziboBidez = gtk_label_new("<span size='xx-large'> Errezibo bidez </span>");
	gtk_label_set_use_markup(GTK_LABEL(lblErreziboBidez), TRUE);
	eventboxErreziboBidez = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(eventboxErreziboBidez), lblErreziboBidez);
	gtk_box_pack_start(GTK_BOX(vBox), eventboxErreziboBidez, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(eventboxErreziboBidez), "button_press_event",
			G_CALLBACK(lblErreziboBidez_clicked), NULL);
	gtk_widget_set_size_request(eventboxErreziboBidez, 450, 70);

	lblTransferentziaBidez = gtk_label_new("<span size='xx-large'> Transferentzia bidez </span>");
	gtk_label_set_use_markup(GTK_LABEL(lblTransferentziaBidez), TRUE);
	eventboxTransferentziaBidez = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(eventboxTransferentziaBidez), lblTransferentziaBidez);
	gtk_box_pack_start(GTK_BOX(vBox), eventboxTransferentziaBidez, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(eventboxTransferentziaBidez), "button_press_event",
			G_CALLBACK(lblTransferentziaBidez_clicked), NULL);
	gtk_widget_set_size_request(eventboxTransferentziaBidez, 450, 70);

	labela = gtk_label_new("<span size='xx-large'>Ados</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(vBox), botoia, FALSE, FALSE, 5);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_widget_set_size_request(eventboxDiruaJarrita, 150, 80);

	/* Dena bistaratu eta martxan jarri */
	form_load();
	gtk_widget_show_all(frmOrdainketa);

	gtk_main();
}
