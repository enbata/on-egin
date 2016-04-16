#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "modSarrera.h"

	GtkWidget *txtIzena, *txtElkartekoPrezioa, *txtErosketaKop, *txtErosketaPrezioaUnitateko;
	GtkWidget *cmbHornitzaileak, *cmbAukerak;
	GtkWidget *checkMateriala;

void horniakBete()
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
	hornitzaileak(frmGaiBerriaSartu);
	horniakBete();
}

static void datuakKargatu()
{
	MYSQL_ROW row;

	mysql_query(dbElkartea, "SELECT Aizenaeus FROM Aukerak ORDER BY AOrdena");
	rstAukerak = mysql_use_result(dbElkartea);
	int i=0;
	while ((row=mysql_fetch_row(rstAukerak))!=NULL)
	{
		gtk_combo_box_remove_text (GTK_COMBO_BOX(cmbAukerak), i);
		gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbAukerak), i, row[0]);
		i++;
	}
	mysql_free_result(rstAukerak);

	horniakBete();
}

static void btmGaiBerriaUtzi()
{
	gtk_main_quit();
	gtk_widget_destroy(frmGaiBerriaSartu);
}

static void btmGaiBerriaAdos()
{
	gchar sql[300];
	MYSQL_ROW row;

	if ( (atoi(gtk_entry_get_text(GTK_ENTRY(txtErosketaKop))) < 1) && (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(checkMateriala)) == 1))
	{
		// Mezua, kopuru desegokia dela esanaz
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmGaiBerriaSartu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dituzu datu zuzenak sartu!");
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy(mezua);
	}
	else
	{
		if (	(strcmp(gtk_entry_get_text(GTK_ENTRY(txtIzena)), "") != 0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtElkartekoPrezioa)), "") != 0) &&
			(gtk_combo_box_get_active(GTK_COMBO_BOX(cmbAukerak)) != -1) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtErosketaKop)), "") != 0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtErosketaPrezioaUnitateko)), "") != 0) )
		{
			// Gai Berria sartu
			sprintf(sql, "Select AKodea from Aukerak where Aizenaeus='%s'", gtk_combo_box_get_active_text(GTK_COMBO_BOX(cmbAukerak)));
			mysql_query(dbElkartea, sql);
			rstAukerak = mysql_use_result(dbElkartea);
			row = mysql_fetch_row(rstAukerak);
			int AKodea = atoi(row[0]);
			mysql_free_result(rstAukerak);
			int GKodea=1;
			int GOrdena=1;
			mysql_query(dbElkartea, "Select MAX(GKodea) from Gaiak");
			rstGaiak = mysql_use_result(dbElkartea);
			row = mysql_fetch_row(rstGaiak);
			if (row[0]!=NULL)
			{
				GKodea=atoi(row[0])+1;
			}
			mysql_free_result(rstGaiak);
			sprintf(sql, "Select MAX(GOrdena) from Gaiak where AKodea=%d", AKodea);
			mysql_query(dbElkartea, sql);
			rstGaiak = mysql_use_result(dbElkartea);
			row = mysql_fetch_row(rstGaiak);
			if (row[0]!=NULL)
			{
				GOrdena=atoi(row[0])+1;
			}
			mysql_free_result(rstGaiak);
			sprintf(sql, "Insert into Gaiak values('%s', %d, '%s', 0, %d, %d, '', %d, 1)", gtk_entry_get_text(GTK_ENTRY(txtIzena)), gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(checkMateriala)), gtk_entry_get_text(GTK_ENTRY(txtElkartekoPrezioa)), GKodea, AKodea, GOrdena);
			mysql_query(dbElkartea, sql);

			//Bodega aktualizatu
			sprintf(sql, "Insert into Elkartea values(%d, %d)", GKodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtErosketaKop))));
			mysql_query(dbElkartea, sql);
			//Erosketak aktualizatu
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
			sprintf(sql, "Insert into Erosketak(GaiKodea, GaiKopurua, data, HorniKodea, ErosketaPrezioa) values(%d, %d, CURDATE(), %d, '%s')", GKodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtErosketaKop))), HKodea, gtk_entry_get_text(GTK_ENTRY(txtErosketaPrezioaUnitateko)));
			mysql_query(dbElkartea, sql);

			gtk_main_quit();
			gtk_widget_destroy(frmGaiBerriaSartu);
		}
		else
		{
			//mezua!, datuak ez direla zuzenak esanaz
			GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmGaiBerriaSartu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dituzu datu zuzenak sartu!");
			gtk_dialog_run(GTK_DIALOG(mezua));
			gtk_widget_destroy(mezua);
		}
	}
}

void gaiBerriaSartu()
{
	GtkWidget *hBox, *vBox;
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *frame;

	/* Lehioa sortu eta konfiguratu */
	frmGaiBerriaSartu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmGaiBerriaSartu), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmGaiBerriaSartu), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmGaiBerriaSartu), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmGaiBerriaSartu), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmGaiBerriaSartu), GTK_WINDOW(frmBodegatikElkartera));

	frame = gtk_frame_new("Gai berria sartu");
	gtk_container_add(GTK_CONTAINER(frmGaiBerriaSartu), frame);
	/* Sortutako frameGaiBerria bete */
	vBox = gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(frame), vBox);
		/* Titulua */
		labela = gtk_label_new("GAI BERRIAREN DATUAK");
		gtk_box_pack_start(GTK_BOX(vBox), labela, TRUE, TRUE, 0);
		/* Gaiaren izena */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Gaiaren izena:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtIzena = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtIzena, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Materiala */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Materiala:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		checkMateriala = gtk_check_button_new();
		gtk_box_pack_start(GTK_BOX(hBox), checkMateriala, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Elkarteko prezioa */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Elkarteko prezioa:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtElkartekoPrezioa = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtElkartekoPrezioa, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Dagokion aukera */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Dagokion aukera:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		cmbAukerak = gtk_combo_box_new_text();
		gtk_box_pack_start(GTK_BOX(hBox), cmbAukerak, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Erosketaren kopurua */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Erosketa kopurua:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtErosketaKop = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtErosketaKop, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Eroskea prezioa unitateko */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Erosketa prezioa unitateko:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtErosketaPrezioaUnitateko = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtErosketaPrezioaUnitateko, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Hornitzailea */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Hornitzailea:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		cmbHornitzaileak = gtk_combo_box_new_text();
		gtk_box_pack_start(GTK_BOX(hBox), cmbHornitzaileak, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Hornitzaile berria botoia */
		botoia = gtk_button_new_with_label("Hornitzaile berria sartu");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmHornitzaileBerria), NULL);
		gtk_box_pack_start(GTK_BOX(vBox), botoia, FALSE, FALSE, 0);
		/* Utzi eta Ados botoiak */
		hBox = gtk_hbox_new(TRUE, 20);
		botoia = gtk_button_new_with_label("Utzi");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmGaiBerriaUtzi), NULL);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
		botoia = gtk_button_new_with_label("Ados");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmGaiBerriaAdos), NULL);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmGaiBerriaSartu);
	datuakKargatu();
	
	gtk_main();
}
