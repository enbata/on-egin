#include <gtk/gtk.h>
#include "irten.h"
#include "Pasahitza.h"
#include "modSarrera.h"

static void btmAdmin()
{

	gtk_widget_destroy (frmSarreraAukera);
	gtk_widget_hide(frmElkarteGastronomikoa);
	pasahitza();
}

static void btmIrten()
{
	gtk_widget_destroy(frmSarreraAukera);
	bukatu();
}

static void btmUtzi()
{
	

	gtk_widget_destroy(frmSarreraAukera);
	
}

void SarreraAukera()
{

	GtkWidget *Hbox, *Vbox;
	GtkWidget *botoia;
	GtkWidget *marra;
	GtkWidget *frame;
	GtkWidget *labela;
	
	/* Lehioa sortu eta definitu */
	frmSarreraAukera = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_decorated (GTK_WINDOW(frmSarreraAukera), FALSE);
// 	gtk_window_fullscreen (GTK_WINDOW(frmSarreraAukera));
	gtk_window_set_resizable (GTK_WINDOW(frmSarreraAukera), FALSE);
	gtk_window_set_position (GTK_WINDOW(frmSarreraAukera), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW(frmSarreraAukera), TRUE);


// 	gtk_window_set_transient_for (GTK_WINDOW(frmSarreraAukera),GTK_WINDOW(frmElkarteGastronomikoa));

	/* Lehioko elementuak sartu */
	frame = gtk_frame_new("");
	gtk_container_add (GTK_CONTAINER(frmSarreraAukera), frame);
	Vbox = gtk_vbox_new (FALSE, 20);
	gtk_container_add (GTK_CONTAINER(frame), Vbox);
	
		/* Lehen lerroko botoiak sortu eta jarri frmSarreraAukeran */
		Hbox = gtk_hbox_new (FALSE, 10);
		
		labela = gtk_label_new("<span size='xx-large'><b>Administrari bezala \nsartu</b></span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		gtk_label_set_justify (GTK_LABEL (labela), GTK_JUSTIFY_CENTER);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		gtk_widget_set_size_request (GTK_WIDGET(botoia), 300, 200);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmAdmin), NULL);
		gtk_box_pack_start(GTK_BOX(Hbox), botoia, FALSE, FALSE, 0);
		
		labela = gtk_label_new("<span size='xx-large'><b>Irten</b></span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		gtk_widget_set_size_request (GTK_WIDGET(botoia), 300, 200);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmIrten), NULL);
		gtk_box_pack_start(GTK_BOX(Hbox), botoia, FALSE, FALSE, 0);
		
		gtk_box_pack_start(GTK_BOX(Vbox), Hbox, FALSE, FALSE, 0);
	
		/* Marra bereizlea sartu */
		marra = gtk_hseparator_new();
		gtk_box_pack_start(GTK_BOX(Vbox), marra, FALSE, FALSE, 0);
	
		/* Utzi botoia jarri */
		labela = gtk_label_new("<span size='xx-large'><b>Utzi</b></span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		gtk_widget_set_size_request (GTK_WIDGET(botoia), 300, 150);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmUtzi), NULL);
		gtk_box_pack_start(GTK_BOX(Vbox), botoia, FALSE, FALSE, 0);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmSarreraAukera);
}
