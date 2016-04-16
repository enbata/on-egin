#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"

	static GtkWidget *txtPassZaharra, *txtPassBerria, *txtPassBerriaBerriz;

static void btmUtzi()
{
	gtk_widget_destroy(frmAldatu);
}

static void btmAdos()
{
	MYSQL_RES *rstLag;
	MYSQL_ROW *row;

	mysql_query (dbElkartea, "Select Epasahitza from ElkartekoDatuak");
	rstLag = mysql_store_result (dbElkartea);
	if ((row= (MYSQL_ROW *) mysql_fetch_row(rstLag)) != NULL)
	{
		if ((row[0])!=NULL)
		{
			if (strcmp(gtk_entry_get_text(GTK_ENTRY(txtPassZaharra)), (gchar *) row[0])==0)
				if (strcmp(gtk_entry_get_text(GTK_ENTRY(txtPassBerria)), gtk_entry_get_text(GTK_ENTRY(txtPassBerriaBerriz)))==0)
				{
					char sql[100];
					sprintf (sql, "Update ElkartekoDatuak set Epasahitza='%s'", gtk_entry_get_text(GTK_ENTRY(txtPassBerria)));
					mysql_query(dbElkartea, sql);
					gtk_widget_destroy(frmAldatu);
				}
				else
				{
					GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmAldatu),
							GTK_DIALOG_DESTROY_WITH_PARENT,
							GTK_MESSAGE_INFO,
							GTK_BUTTONS_OK,
							"Pasahitz berria sar ezazu berriro");
					gtk_dialog_run(GTK_DIALOG(mezua));
					gtk_widget_destroy(mezua);
				}
			else
			{
				GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmAldatu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Pasahitz okerra");
				gtk_dialog_run(GTK_DIALOG(mezua));
				gtk_widget_destroy(mezua);
			}
		}
		else
		{
			if (strcmp(gtk_entry_get_text(GTK_ENTRY(txtPassBerria)), gtk_entry_get_text(GTK_ENTRY(txtPassBerriaBerriz)))==0)
			{
				char sql[100];
				sprintf (sql, "Update ElkartekoDatuak set Epasahitza='%s'", gtk_entry_get_text(GTK_ENTRY(txtPassBerria)));
				mysql_query(dbElkartea, sql);
				gtk_widget_destroy(frmAldatu);
			}
			else
			{
				GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmAldatu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Pasahitz berria sar ezazu berriro");
				gtk_dialog_run(GTK_DIALOG(mezua));
				gtk_widget_destroy(mezua);
			}
		}
	}
	else
	{
			if (strcmp(gtk_entry_get_text(GTK_ENTRY(txtPassBerria)), gtk_entry_get_text(GTK_ENTRY(txtPassBerriaBerriz)))==0)
			{
				char sql[100];
				sprintf (sql, "Insert into ElkartekoDatuak (Epasahitza) values ('%s')", gtk_entry_get_text(GTK_ENTRY(txtPassBerria)));
				mysql_query(dbElkartea, sql);
				gtk_widget_destroy(frmAldatu);
			}
			else
			{
				GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmAldatu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Pasahitz berria sar ezazu berriro");
				gtk_dialog_run(GTK_DIALOG(mezua));
				gtk_widget_destroy(mezua);
			}
	}
	mysql_free_result(rstLag);
}

static void txtPassBerria_KeyPress()
{
	printf("Funtzionatzen du!!!\n");
}

void aldatu()
{
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *vBox, *hBox;
	GtkWidget *frame;

	/* Lehioa sortu eta definitu */
	frmAldatu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmAldatu), FALSE);
	gtk_window_set_position (GTK_WINDOW(frmAldatu), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_type_hint (GTK_WINDOW(frmAldatu), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmAldatu), GTK_WINDOW(frmAdministraria));
	gtk_window_set_modal (GTK_WINDOW(frmAldatu), TRUE);

	/* Lehio barneko egitura osatu eta kokatu */
	frame = gtk_frame_new("Administraria");
	gtk_container_add(GTK_CONTAINER(frmAldatu), frame);
	vBox = gtk_vbox_new(FALSE, 5);
	gtk_container_add (GTK_CONTAINER(frame), vBox);

	/* Label eta testu areak sortu eta kokatu */
	labela = gtk_label_new("Pasahitza aldatu");
	gtk_box_pack_start (GTK_BOX(vBox), labela, FALSE, FALSE, 5);
	hBox = gtk_hbox_new(TRUE, 3);
	labela = gtk_label_new("Pasahitz zaharra");
	gtk_box_pack_start (GTK_BOX(hBox), labela, FALSE, FALSE, 0);
	txtPassZaharra = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(txtPassZaharra), 10);
	gtk_box_pack_start (GTK_BOX(hBox), txtPassZaharra, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
	hBox = gtk_hbox_new(TRUE, 3);
	labela = gtk_label_new("Pasahitz berria");
	gtk_box_pack_start (GTK_BOX(hBox), labela, FALSE, FALSE, 0);
	txtPassBerria = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(txtPassBerria), 7);
	gtk_entry_set_visibility (GTK_ENTRY(txtPassBerria), FALSE);
	g_signal_connect(G_OBJECT(txtPassBerria), "insert-at-cursor",
			G_CALLBACK(txtPassBerria_KeyPress), NULL);
	gtk_box_pack_start (GTK_BOX(hBox), txtPassBerria, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
	hBox = gtk_hbox_new(TRUE, 3);
	labela = gtk_label_new("Pasahitz berria berriro");
	gtk_box_pack_start (GTK_BOX(hBox), labela, FALSE, FALSE, 0);
	txtPassBerriaBerriz = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(txtPassBerriaBerriz), 7);
	gtk_entry_set_visibility (GTK_ENTRY(txtPassBerriaBerriz), FALSE);
	gtk_box_pack_start (GTK_BOX(hBox), txtPassBerriaBerriz, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	/* Botoiak sortu eta kokatu */
	hBox = gtk_hbox_new(TRUE, 10);
	botoia = gtk_button_new_with_label ("Utzi");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_widget_set_size_request(botoia, 100, 50);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, TRUE, 40);
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_widget_set_size_request(botoia, 100, 50);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, TRUE, 40);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 20);

	/* Dena bistaratu */
	gtk_widget_show_all(frmAldatu);
}
