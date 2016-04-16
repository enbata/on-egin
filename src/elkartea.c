#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"
#define true 1
#define false 0

	static GtkWidget *txtEIzena, *txtEHelbidea, *txtEPK, *txtEHerria, *txtETelefonoa, *txtEKontua;
	static int berria=false;

static void btmGorde()
{
	GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmElkartea),
				GTK_DIALOG_DESTROY_WITH_PARENT,
				GTK_MESSAGE_QUESTION,
				GTK_BUTTONS_YES_NO,
				"Ziur al zaude datuak gorde nahi dituzula?");
	int erantzuna;
	if ((erantzuna=gtk_dialog_run(GTK_DIALOG(mezua)))==GTK_RESPONSE_YES)
	{
		char sql[500];
		if (berria)
		{
			sprintf (sql, "Insert into ElkartekoDatuak(Eizena, Ehelbidea, EPK, Eherria, Etel, Kontua) values ('%s', '%s', '%s', '%s', '%s', '%s')", gtk_entry_get_text (GTK_ENTRY(txtEIzena)), gtk_entry_get_text(GTK_ENTRY(txtEHelbidea)), gtk_entry_get_text (GTK_ENTRY(txtEPK)), gtk_entry_get_text(GTK_ENTRY(txtEHerria)), gtk_entry_get_text(GTK_ENTRY(txtETelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtEKontua)));
			mysql_query(dbElkartea, sql);
			berria=false;
		}
		else
		{
			sprintf (sql, "Update ElkartekoDatuak set Eizena='%s', Ehelbidea='%s', EPK='%s', Eherria='%s', Etel='%s', Kontua='%s'", gtk_entry_get_text (GTK_ENTRY(txtEIzena)), gtk_entry_get_text(GTK_ENTRY(txtEHelbidea)), gtk_entry_get_text (GTK_ENTRY(txtEPK)), gtk_entry_get_text(GTK_ENTRY(txtEHerria)), gtk_entry_get_text(GTK_ENTRY(txtETelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtEKontua)));
			mysql_query(dbElkartea, sql);
		}
	}
	gtk_widget_destroy(mezua);
}

void elkarteaBete()
{
	MYSQL_ROW *row;
	
	mysql_query (dbElkartea, "select * from ElkartekoDatuak");
	rstDatuak = mysql_use_result (dbElkartea);
	if ((row= (MYSQL_ROW *) mysql_fetch_row(rstDatuak))!=NULL)
	{
		gtk_entry_set_text (GTK_ENTRY(txtEIzena), (gchar *) row[0]);
		gtk_entry_set_text (GTK_ENTRY(txtEHelbidea), (gchar *) row[1]);
		gtk_entry_set_text (GTK_ENTRY(txtEPK), (gchar *) row[2]);
		gtk_entry_set_text (GTK_ENTRY(txtEHerria), (gchar *) row[3]);
		gtk_entry_set_text (GTK_ENTRY(txtETelefonoa), (gchar *) row[4]);
		gtk_entry_set_text (GTK_ENTRY(txtEKontua), (gchar *) row[7]);
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY(txtEIzena), "");
		gtk_entry_set_text (GTK_ENTRY(txtEHelbidea), "");
		gtk_entry_set_text (GTK_ENTRY(txtEPK),"");
		gtk_entry_set_text (GTK_ENTRY(txtEHerria),"");
		gtk_entry_set_text (GTK_ENTRY(txtETelefonoa),"");
		gtk_entry_set_text (GTK_ENTRY(txtEKontua),"");
		berria=true;
	}
	mysql_free_result (rstDatuak);
}

static void btmDesegin()
{
	elkarteaBete();
}

static void btmAdos()
{
	MYSQL_ROW *row;

	mysql_query (dbElkartea, "Select * from ElkartekoDatuak");
	rstDatuak = mysql_store_result(dbElkartea);
	if ((row= (MYSQL_ROW *) mysql_fetch_row(rstDatuak))!=NULL)
	if (!(	(strcmp(gtk_entry_get_text(GTK_ENTRY(txtEIzena)), (gchar *) row[0])==0) &&
		(strcmp(gtk_entry_get_text(GTK_ENTRY(txtEHelbidea)), (gchar *) row[1])==0) &&
		(strcmp(gtk_entry_get_text(GTK_ENTRY(txtEPK)), (gchar *) row[2])==0) &&
		(strcmp(gtk_entry_get_text(GTK_ENTRY(txtEHerria)), (gchar *) row[3])==0) &&
		(strcmp(gtk_entry_get_text(GTK_ENTRY(txtETelefonoa)), (gchar *) row[4])==0) &&
		(strcmp(gtk_entry_get_text(GTK_ENTRY(txtEKontua)), (gchar *) row[7])==0) ))
		
	{
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmElkartea),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_YES_NO,
					"Aldaketak gorde nahi al dituzu?");
		int erantzuna;
		if ((erantzuna=gtk_dialog_run(GTK_DIALOG(mezua)))==GTK_RESPONSE_YES)
		{
			char sql[500];
			if (berria)
			{
				sprintf (sql, "Insert into ElkartekoDatuak(Eizena, Ehelbidea, EPK, Eherria, Etel, Kontua) values ('%s', '%s', '%s', '%s', '%s', '%s')", gtk_entry_get_text (GTK_ENTRY(txtEIzena)), gtk_entry_get_text(GTK_ENTRY(txtEHelbidea)), gtk_entry_get_text (GTK_ENTRY(txtEPK)), gtk_entry_get_text(GTK_ENTRY(txtEHerria)), gtk_entry_get_text(GTK_ENTRY(txtETelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtEKontua)));
				mysql_query(dbElkartea, sql);
				berria=false;
			}
			else
			{
				sprintf (sql, "Update ElkartekoDatuak set Eizena='%s', Ehelbidea='%s', EPK='%s', Eherria='%s', Etel='%s', Kontua='%s'", gtk_entry_get_text (GTK_ENTRY(txtEIzena)), gtk_entry_get_text(GTK_ENTRY(txtEHelbidea)), gtk_entry_get_text (GTK_ENTRY(txtEPK)), gtk_entry_get_text(GTK_ENTRY(txtEHerria)), gtk_entry_get_text(GTK_ENTRY(txtETelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtEKontua)));
				mysql_query(dbElkartea, sql);
			}
		}
	}
	mysql_free_result (rstDatuak);
	gtk_widget_destroy (frmElkartea);
}

void elkartea()
{
	GtkWidget *frame;
	GtkWidget *hBox;
	GtkWidget *barra;
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *taula;
	GtkWidget *irudia;

	/* lehioa sortu eta definitu */
	frmElkartea=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmElkartea), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW(frmElkartea), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_modal (GTK_WINDOW(frmElkartea), TRUE);
	gtk_window_set_transient_for(GTK_WINDOW(frmElkartea), GTK_WINDOW(frmAdministraria));
	gtk_window_set_position (GTK_WINDOW(frmElkartea), GTK_WIN_POS_CENTER_ALWAYS);

	frame = gtk_frame_new("ELKARTEA");
	gtk_container_add (GTK_CONTAINER(frmElkartea), frame);
	
	/* taula egitura bat erabiliko dugu formularioko elementuak kokatzeko */
	taula = gtk_table_new (3, 7, FALSE);
	gtk_container_add (GTK_CONTAINER(frame), taula);

	/* ekintza botoiak sortu eta kokatu */
	hBox =gtk_hbox_new(TRUE, 5);
	gtk_table_attach_defaults (GTK_TABLE(taula), hBox, 5, 7, 0, 1);
	botoia = gtk_button_new();
	irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/gorde2.png");
	gtk_container_add (GTK_CONTAINER(botoia), irudia);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmGorde), NULL);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
	botoia = gtk_button_new();
	irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/desegin4.png");
	gtk_container_add (GTK_CONTAINER(botoia), irudia);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmDesegin), NULL);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);

	/* ados botoia sortu eta sartu */
	botoia = gtk_button_new_with_label("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 5, 2, 3);

	/* Elkartearen datuak sartzeko testu areak sortu eta kokatu */
	frame = gtk_frame_new("");
	gtk_table_attach_defaults (GTK_TABLE(taula), frame, 0, 7, 1, 2);
	taula = gtk_table_new(6, 4, FALSE);
	gtk_container_add (GTK_CONTAINER(frame), taula);
		/* sortutako taula egituran elementuak kokatu */
		barra = gtk_hseparator_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), barra, 0, 4, 0, 1);
		labela = gtk_label_new("Elkartearen izena");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 2, 1, 2);
		txtEIzena = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtEIzena, 2, 4, 1, 2);
		labela = gtk_label_new("Helbidea");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 2, 3);
		txtEHelbidea = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtEHelbidea, 1, 2, 2, 3);
		labela = gtk_label_new("P.K");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 2, 3, 2, 3);
		txtEPK = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtEPK, 3, 4, 2, 3);
		labela = gtk_label_new("Herria");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 3, 4);
		txtEHerria = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtEHerria, 1, 2, 3, 4);
		labela = gtk_label_new("Telefonoa");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 2, 3, 3, 4);
		txtETelefonoa = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtETelefonoa, 3, 4, 3, 4);
		labela = gtk_label_new("Kontu zenbakia");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 2, 4, 5);
		txtEKontua = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtEKontua, 2, 4, 4, 5);
		barra = gtk_hseparator_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), barra, 0, 4, 5, 6);

	/* Dena bistaratu */
	gtk_widget_show_all(frmElkartea);

	elkarteaBete();

}
