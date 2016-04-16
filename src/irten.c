#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"

	static GtkWidget *txtPasahitza;

static void zenbakiaIdatzi(GtkWidget *botoia, gpointer zenbakia)
{
	gchar kodea[10];
	strcpy (kodea, gtk_entry_get_text (GTK_ENTRY(txtPasahitza)));
	if (strcmp(zenbakia, "DEL")!=0)
	{
		if (strlen (kodea)!= 10)
		{
			strcat (kodea, zenbakia);
			gtk_entry_set_text (GTK_ENTRY(GTK_ENTRY(txtPasahitza)), kodea);
		}
	}
	else
	{
		if (strlen(kodea) != 0)
		{
			kodea[strlen(gtk_entry_get_text(GTK_ENTRY(txtPasahitza)))-1] = '\0';
			gtk_entry_set_text (GTK_ENTRY(GTK_ENTRY(txtPasahitza)), kodea);
		}
	}
}

static void btmAdos()
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	mysql_query (dbElkartea, "Select Epasahitza from ElkartekoDatuak");
	res = mysql_store_result (dbElkartea);
	if ((row=mysql_fetch_row(res)) != NULL)
	{
		if (strcmp(gtk_entry_get_text(GTK_ENTRY(txtPasahitza)), row[0])==0)
		{
			gtk_main_quit();
		}
		else
		{
			gtk_entry_set_text(GTK_ENTRY(txtPasahitza), "");
		}
	}
	else gtk_main_quit();
	mysql_free_result (res);
}

static void btmUtzi()
{
	gtk_widget_destroy (frmIrten);
}

void bukatu()
{
	GtkWidget *vBox, *hBox;
	GtkWidget *botoia;
	GtkWidget *taula;
	GtkWidget *labela;
	GtkWidget *frame;
	GtkWidget *alignment;
	GdkColor kolorea;
	char *zenb;
	

	/* frmIrten sortu eta hasieratu */
	frmIrten = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_decorated (GTK_WINDOW(frmIrten), FALSE);
	gtk_window_set_position (GTK_WINDOW(frmIrten), GTK_WIN_POS_CENTER_ALWAYS);

	frame = gtk_frame_new("IRTEN");
	gdk_color_parse("#e3e0e0", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	gtk_container_add (GTK_CONTAINER(frmIrten), frame);
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER(alignment), vBox);

	/* labela sortu eta sartu */
	labela = gtk_label_new ("<span size='x-large'><b>Sar ezazu administrariaren kodea</b></span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	gtk_box_pack_start (GTK_BOX(vBox), labela, TRUE, FALSE, 20);

	hBox = gtk_hbox_new(FALSE, 20);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
	
	/* Ados eta Utzi botoiak sortu eta sartu */
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hBox), vBox, FALSE, FALSE, 0);
	labela=gtk_label_new("<span size='x-large'>Ados</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_box_pack_start (GTK_BOX(vBox), botoia, FALSE, FALSE, 30);
	labela=gtk_label_new("<span size='x-large'>Utzi</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_box_pack_start (GTK_BOX(vBox), botoia, FALSE, FALSE, 30);
	
	/* Kodea idazteko panela sortu eta sartu */
	frame = gtk_frame_new("");
	gdk_color_parse("#858484", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	gtk_box_pack_start (GTK_BOX(hBox), frame, FALSE, FALSE, 0);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frame), vBox);
		
		/* Testua sortu eta sartu */
		txtPasahitza = gtk_entry_new();
		gtk_entry_set_visibility (GTK_ENTRY(txtPasahitza), FALSE);
		gtk_entry_set_max_length (GTK_ENTRY(txtPasahitza), 10);
		gtk_widget_set_size_request(txtPasahitza, 220, 40);
		gtk_box_pack_start (GTK_BOX(vBox), txtPasahitza, FALSE, FALSE, 0);

		/* Zenbakiak sartzeko botoiak sortu eta sartu */
		taula = gtk_table_new(4, 3, TRUE);
		gtk_box_pack_start (GTK_BOX(vBox), taula, TRUE, FALSE, 10);
		labela=gtk_label_new("<span size='x-large'>0</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "0";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 3, 4);
		labela=gtk_label_new("<span size='x-large'>DEL</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "DEL";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 3, 3, 4);
		labela=gtk_label_new("<span size='x-large'>1</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "1";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 2, 3);
		labela=gtk_label_new("<span size='x-large'>2</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "2";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 2, 3);
		labela=gtk_label_new("<span size='x-large'>3</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "3";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 2, 3);
		labela=gtk_label_new("<span size='x-large'>4</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "4";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 1, 2);
		labela=gtk_label_new("<span size='x-large'>5</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "5";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 1, 2);
		labela=gtk_label_new("<span size='x-large'>6</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "6";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 1, 2);
		labela=gtk_label_new("<span size='x-large'>7</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "7";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 0, 1);
		labela=gtk_label_new("<span size='x-large'>8</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "8";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 0, 1);
		labela=gtk_label_new("<span size='x-large'>9</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb = "9";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 0, 1);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmIrten);
	
}
