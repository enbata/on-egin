#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"
#define true 1
#define false 0

	static int Berria; char *aukera;

enum
{
	Balio_Zutabea,
	Zutabe_Kop
};

static void form_load(gpointer lista, gpointer testua)
{
	if (Berria)
		gtk_entry_set_text(GTK_ENTRY(testua), "");
	else
	{	
		GtkTreeSelection *selection;
		GtkTreeModel *model;
		GtkTreeIter iter;

		model = gtk_tree_view_get_model(lista);
		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lista));
		gtk_tree_selection_get_selected(selection, &model, &iter);
		gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
		gtk_entry_set_text(GTK_ENTRY(testua), aukera);
	}
}

static void btmUtzi()
{
	gtk_widget_destroy(frmAukeraSartu);
}

static void btmAdos(GtkWidget *botoia, gpointer testua)
{
	// Lehenik ea testu area hutsa dagoan konprobatu behar!!!!!!!!!!!!!!!
	char sql[300];
	if (Berria)
	{
		MYSQL_ROW row;
		mysql_query (dbElkartea, "Select MAX(AKodea), MAX(AOrdena) from Aukerak");
		rstAukerak = mysql_store_result(dbElkartea);
		row=mysql_fetch_row(rstAukerak);
		if ((row[0])!=NULL)
		{
			sprintf(sql, "Insert into Aukerak values('%s','',%d,%d)", gtk_entry_get_text(testua), atoi(row[0])+1,atoi(row[1])+1);
			mysql_query(dbElkartea, sql);
		}
		else
		{
			sprintf(sql, "Insert into Aukerak values('%s','',1,1)", gtk_entry_get_text(testua));
			mysql_query(dbElkartea, sql);
		}
		mysql_free_result(rstAukerak);
	}
	else
	{
		sprintf (sql, "Update Aukerak set Aizenaeus='%s' where Aizenaeus='%s'", gtk_entry_get_text(testua), aukera);
		mysql_query(dbElkartea, sql);
	}
	gtk_main_quit();
	gtk_widget_destroy(frmAukeraSartu);
}

void aukeraSartu(gpointer lista, int berria)
{
	GtkWidget *vBox, *hBox;
	GtkWidget *labela;
	GtkWidget *txtIzena;
	GtkWidget *botoia;
	GtkWidget *frame;

	/* Lehioa sortu */
	frmAukeraSartu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(frmAukeraSartu), FALSE);
	gtk_window_set_type_hint(GTK_WINDOW(frmAukeraSartu), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_position (GTK_WINDOW(frmAukeraSartu), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW(frmAukeraSartu), TRUE);
	gtk_window_set_transient_for (GTK_WINDOW(frmAukeraSartu), GTK_WINDOW(frmKonfigurazioOrokorra));

	/* Barneko egitura sortu eta sartu */
	frame = gtk_frame_new ("Aukera sartu");
	gtk_container_add(GTK_CONTAINER(frmAukeraSartu), frame);
	vBox = gtk_vbox_new(TRUE, 5);
	gtk_container_add (GTK_CONTAINER(frame), vBox);
	hBox = gtk_hbox_new(FALSE, 5);
		/* Labela eta testu area sortu eta sartu */
		labela = gtk_label_new("Aukeraren izena:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtIzena = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtIzena, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
	hBox = gtk_hbox_new (TRUE, 5);
		/* Botoiak sortu eta sartu */
		botoia = gtk_button_new_with_label("Utzi");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmUtzi), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, TRUE, 5);
		botoia = gtk_button_new_with_label("Ados");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmAdos), (gpointer) txtIzena);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, TRUE, 5);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	/* Dena bistaratu */
	gtk_widget_show_all(frmAukeraSartu);

	Berria = berria;
	form_load((gpointer) lista, (gpointer) txtIzena);

	gtk_main();
}
