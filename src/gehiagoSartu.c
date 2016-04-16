#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "modSarrera.h"

	GtkWidget *txtLehendikBodegan, *txtUnitateBerriak, *txtErosketaPrezioaUnitateko, *txtElkartekoPrezioa;
	GtkWidget *cmbHornitzaileak;

void horniBete()
{
	MYSQL_ROW row;

	mysql_query(dbElkartea, "select HIzena from Hornitzaileak order by HGakoa");
	rstHornitzaileak = mysql_use_result(dbElkartea);
	int i=0;
	while ((row=mysql_fetch_row(rstHornitzaileak))!=NULL)
	{
		gtk_combo_box_remove_text (GTK_COMBO_BOX(cmbHornitzaileak), i);
		gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbHornitzaileak), i, row[0]);
		i++;
	}
	mysql_free_result(rstHornitzaileak);
}

static void btmHornitzaileBerria()
{
	hornitzaileak(frmGehiagoSartu);
	horniBete();
}

static void datuakKargatu(gchar *izena, gchar *kop, gpointer frame)
{
	gtk_frame_set_label(frame, izena);
	gtk_entry_set_text (GTK_ENTRY(txtLehendikBodegan), kop);

	gchar sql[100];
	MYSQL_ROW row;
	sprintf(sql, "Select Gprezioa from Gaiak where Gizenaeus='%s'", izena);
	mysql_query(dbElkartea, sql);
	rstGaiak = mysql_use_result(dbElkartea);
	if ((row=mysql_fetch_row(rstGaiak))!=NULL)
		if (row[0]!=NULL)
			gtk_entry_set_text(GTK_ENTRY(txtElkartekoPrezioa), row[0]);
	mysql_free_result(rstGaiak);

	horniBete();
}

static void btmBodegaraUtzi()
{
	gtk_main_quit();
	gtk_widget_destroy(frmGehiagoSartu);
}

static void btmBodegaraAdos(GtkWidget *botoia, gpointer frame)
{
	MYSQL_ROW row;

	if (atoi(gtk_entry_get_text(GTK_ENTRY(txtUnitateBerriak))) < 0)
	{
		// Mezua, kopuru desegokia dela esanaz
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmGehiagoSartu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dituzu datu zuzenak sartu:\n unitate berriaren balioa ez da egokia!");
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy(mezua);
	}
	else
	{
		// Gaiaren kodea lortu
		char sql[300];
		sprintf (sql, "select GKodea from Gaiak where Gizenaeus='%s'", gtk_frame_get_label(frame));
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_use_result(dbElkartea);
		row = mysql_fetch_row(rstGaiak);
		int kodea=atoi(row[0]);
		mysql_free_result(rstGaiak);

		// Gaiaren unitate berriak elkartean sartu
		sprintf(sql, "select Kopurua from Elkartea where Gaikodea=%d", kodea);
		mysql_query(dbElkartea, sql);
		rstDatuak = mysql_store_result(dbElkartea);
		if ((row=mysql_fetch_row(rstDatuak)) != NULL)
		{
			sprintf(sql, "Update Elkartea set Kopurua=Kopurua + %d where Gaikodea=%d", atoi(gtk_entry_get_text(GTK_ENTRY(txtUnitateBerriak))), kodea);
			mysql_query(dbElkartea, sql);
		}
		else
		{
			sprintf(sql, "Insert into Elkartea values (%d, %d)", kodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtUnitateBerriak))));
			mysql_query(dbElkartea, sql);
		}
		mysql_free_result(rstDatuak);

		// Erosketa berria sartu datu basean
		int HKodea;
		if (gtk_combo_box_get_active(GTK_COMBO_BOX(cmbHornitzaileak)) == -1) HKodea=0;
		else
		{
			sprintf(sql, "Select HGakoa from Hornitzaileak where HIzena='%s'", gtk_combo_box_get_active_text(GTK_COMBO_BOX(cmbHornitzaileak)));
			mysql_query(dbElkartea, sql);
			rstHornitzaileak = mysql_use_result(dbElkartea);
			row=mysql_fetch_row(rstHornitzaileak);
			HKodea=atoi(row[0]);
			mysql_free_result(rstHornitzaileak);
		}
		sprintf(sql, "Insert into Erosketak(GaiKodea, GaiKopurua, data, HorniKodea, ErosketaPrezioa) values(%d, %d, CURDATE(), %d, '%s')", kodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtUnitateBerriak))), HKodea, gtk_entry_get_text(GTK_ENTRY(txtErosketaPrezioaUnitateko)));
		mysql_query(dbElkartea, sql);

		// Gaiaren elkarteko prezioa berritu
		sprintf(sql, "Update Gaiak set Gprezioa='%s' where GKodea=%d", gtk_entry_get_text(GTK_ENTRY(txtElkartekoPrezioa)), kodea);
		mysql_query(dbElkartea, sql);

		gtk_main_quit();
		gtk_widget_destroy(frmGehiagoSartu);
	}
}

void gehiagoSartu(gchar *izena, gchar *kop)
{
	GtkWidget *vBox, *hBox;
	GtkWidget *botoia;
	GtkWidget *labela;
	GtkWidget *frame;

	/* Lehio nagusia sortu eta konfiguratu */
	frmGehiagoSartu=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmGehiagoSartu), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW(frmGehiagoSartu), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_modal (GTK_WINDOW(frmGehiagoSartu), TRUE);
	gtk_window_set_transient_for(GTK_WINDOW(frmGehiagoSartu), GTK_WINDOW(frmBodegatikElkartera));
	gtk_window_set_position (GTK_WINDOW(frmGehiagoSartu), GTK_WIN_POS_CENTER_ALWAYS);

	frame = gtk_frame_new("");
	gtk_container_add(GTK_CONTAINER(frmGehiagoSartu), frame);
	/* Sortutako frameBodegara bete */
	vBox = gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(frame), vBox);
		/* Lehendik bodegan */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Lehendik bodegan:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtLehendikBodegan = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtLehendikBodegan, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Unitate berriak */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Unitate berriak:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtUnitateBerriak = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtUnitateBerriak, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Erosketa prezioa unitateko */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Erosketa prezioa unitateko:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtErosketaPrezioaUnitateko = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtErosketaPrezioaUnitateko, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Elkarteko prezioa */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Elkarteko prezioa:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtElkartekoPrezioa = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtElkartekoPrezioa, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Hornitzailea konboa */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Hornitzailea:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		cmbHornitzaileak = gtk_combo_box_new_text();
		gtk_box_pack_start(GTK_BOX(hBox), cmbHornitzaileak, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Hornitzaile berria sartzeko botoia */
		botoia = gtk_button_new_with_label("Hornitzaile berria sartu");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmHornitzaileBerria), NULL);
		gtk_box_pack_start(GTK_BOX(vBox), botoia, FALSE, FALSE, 0);
		/* Utzi eta Ados botoiak */
		hBox = gtk_hbox_new(TRUE, 20);
		botoia = gtk_button_new_with_label("Utzi");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBodegaraUtzi), NULL);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
		botoia = gtk_button_new_with_label("Ados");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBodegaraAdos), (gpointer) frame);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmGehiagoSartu);
	datuakKargatu(izena, kop, (gpointer) frame);
	gtk_main();
}
