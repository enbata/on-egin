#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include "modSarrera.h"

	static GtkWidget *txtIzena, *txtElkartekoPrezioa;
	static GtkWidget *cmbMenpekotasuna, *cmbAukerak;
	static GtkWidget *checkMateriala, *checkErabilgarri;
	static gchar *Gaia;
	static int Aukera, Ordena, Kodea;

static void btmUtzi()
{
	gtk_main_quit();
	gtk_widget_destroy(frmSartuGaia);
}

static void btmAdos()
{
	char sql[500];
	MYSQL_ROW row;
	MYSQL_RES *res;

	GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmSartuGaia),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_YES_NO,
					"Ziur aldaketak egin nahi dituzula?");
	int erantzuna;
	if ((erantzuna=gtk_dialog_run(GTK_DIALOG(mezua)))==GTK_RESPONSE_YES)
	{
		int Menpekotasuna=0;
		if (strcmp(gtk_combo_box_get_active_text (GTK_COMBO_BOX(cmbMenpekotasuna)),"Menpekotasunik gabea")==0) Menpekotasuna=0;
		if (strcmp(gtk_combo_box_get_active_text (GTK_COMBO_BOX(cmbMenpekotasuna)),"Guztiekiko menpekoa")==0) Menpekotasuna=1;
		if (strcmp(gtk_combo_box_get_active_text (GTK_COMBO_BOX(cmbMenpekotasuna)),"Ez bazkideekiko menpekoa")==0) Menpekotasuna=2;
		if (strcmp(gtk_combo_box_get_active_text (GTK_COMBO_BOX(cmbMenpekotasuna)),"Bazkideen menpekoa")==0) Menpekotasuna=3;
		if (strcmp(gtk_combo_box_get_active_text (GTK_COMBO_BOX(cmbMenpekotasuna)),"Menpeko aldagarria")==0) Menpekotasuna=4;
	
		sprintf(sql, "Select AKodea from Aukerak where Aizenaeus='%s'", gtk_combo_box_get_active_text(GTK_COMBO_BOX(cmbAukerak)));
		mysql_query(dbElkartea, sql);
		rstAukerak = mysql_store_result(dbElkartea);
		row = mysql_fetch_row(rstAukerak);

		// Gaia aukeraz aldatua izan bada, gaien Ordenak aktualizatu behar dira
		if (Aukera!=atoi(row[0]))
		{
			sprintf(sql, "Update Gaiak set GOrdena=GOrdena-1 where AKodea=%d and GOrdena>%d", Aukera, Ordena);
			mysql_query(dbElkartea, sql);
			Aukera = atoi(row[0]);
			sprintf(sql, "Select MAX(GOrdena) from Gaiak where AKodea=%d", Aukera);
			mysql_query(dbElkartea, sql);
			res=mysql_use_result(dbElkartea);
			row=mysql_fetch_row(res);
			if (row[0]!=NULL) Ordena=atoi(row[0])+1;
			else Ordena=0;
			mysql_free_result(res);
		}

		mysql_free_result(rstAukerak);

		// Materiala aukera desaktibatuta badago, elkartea taulan aldaketak egin behar
		if (! (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkMateriala))))
		{
			sprintf(sql, "Select * from Elkartea where gaikodea=%d", Kodea);
			mysql_query(dbElkartea, sql);
			res = mysql_use_result(dbElkartea);
			if ((row = mysql_fetch_row(res)) == NULL)
			{
				sprintf(sql, "Insert into Elkartea values (%d, 0)", Kodea);
				mysql_query(dbElkartea, sql);
			}
			mysql_free_result(res);
		}

		sprintf(sql, "update Gaiak set Gizenaeus='%s', Materiala=%d, Gprezioa='%s', Menpekotasuna=%d, AKodea=%d, GOrdena=%d, erabilgarri=%d where Gizenaeus='%s'",gtk_entry_get_text(GTK_ENTRY(txtIzena)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkMateriala)), gtk_entry_get_text(GTK_ENTRY(txtElkartekoPrezioa)), Menpekotasuna, Aukera, Ordena, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkErabilgarri)), Gaia);

		mysql_query(dbElkartea, sql);
 		gtk_widget_destroy(mezua); // Josebak gehitua
		gtk_main_quit();
		gtk_widget_destroy(frmSartuGaia); // Josebak deskomentatua
	}
	else gtk_widget_destroy(mezua); // Josebak gehitu du else (destroi bazegoen)
}

static void form_Load(gchar *gaia)
{
	char sql[300];
	MYSQL_ROW row;

	Gaia = gaia;
	mysql_query(dbElkartea, "Select * from Aukerak order by AOrdena");
	rstAukerak = mysql_store_result(dbElkartea);
	int i=0;
	while ((row = mysql_fetch_row(rstAukerak)) != NULL)
	{
		gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbAukerak), i, row[0]);
		i++;
	}
	mysql_free_result(rstAukerak);

	menpekotasunakSartu();

	gtk_entry_set_text(GTK_ENTRY(txtIzena), gaia);
	
	sprintf(sql, "SELECT * FROM Gaiak where Gizenaeus='%s'", gaia);
	mysql_query(dbElkartea, sql);
	rstGaiak = mysql_use_result(dbElkartea);
	row=mysql_fetch_row(rstGaiak);

	gtk_entry_set_text(GTK_ENTRY(txtElkartekoPrezioa), row[2]);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkMateriala), atoi(row[1]));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkErabilgarri), atoi(row[8]));
	gtk_combo_box_set_active (GTK_COMBO_BOX(cmbMenpekotasuna), atoi(row[3]));
	Aukera = atoi(row[5]);
	Ordena = atoi(row[7]);
	Kodea = atoi(row[4]);
	mysql_free_result(rstGaiak);

	sprintf(sql, "Select AOrdena from Aukerak where AKodea=%d", Aukera);
	mysql_query(dbElkartea, sql);
	rstGaiak = mysql_use_result(dbElkartea);
	row=mysql_fetch_row(rstGaiak);
	gtk_combo_box_set_active (GTK_COMBO_BOX(cmbAukerak), atoi(row[0])-1);
	mysql_free_result(rstGaiak);

}

menpekotasunakSartu()
{
	gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbMenpekotasuna), 0, "Menpekotasunik gabea");
	gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbMenpekotasuna), 1, "Guztiekiko menpekoa");
	gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbMenpekotasuna), 2, "Ez bazkideekiko menpekoa");
	gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbMenpekotasuna), 3, "Bazkideen menpekoa");
	gtk_combo_box_insert_text (GTK_COMBO_BOX(cmbMenpekotasuna), 4, "Menpeko aldagarria");
}

void sartuGaia(gchar *gaia)
{
	GtkWidget *vBox, *hBox;
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *frame;

	/* Lehioa sortu eta konfiguratu */
	frmSartuGaia = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmSartuGaia), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW(frmSartuGaia), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmSartuGaia), GTK_WINDOW(frmKonfigurazioOrokorra));
	gtk_window_set_position (GTK_WINDOW(frmSartuGaia), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW(frmSartuGaia), TRUE);

	/* Lehioko objektuak kokatzeko egitura sortu eta sartu */
	frame = gtk_frame_new("Gaia editatu");
	gtk_container_add(GTK_CONTAINER(frmSartuGaia), frame);
	
	/* Lehioaren obejtuak sortu eta sartu */
	vBox=gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(frame), vBox);
	/* Datuak sartzeko egiturak sortu eta sartu */
		/* Izena */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Izena:");
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
		/* Erabilgarritasuna */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Erabilgarri:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		checkErabilgarri = gtk_check_button_new();
		gtk_box_pack_start(GTK_BOX(hBox), checkErabilgarri, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Elkarteko prezioa */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Elkarteko prezioa:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtElkartekoPrezioa = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtElkartekoPrezioa, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Menpekotasuna */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Menpekotasuna:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		cmbMenpekotasuna = gtk_combo_box_new_text();
		gtk_box_pack_start(GTK_BOX(hBox), cmbMenpekotasuna, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Aukerak */
		hBox = gtk_hbox_new(TRUE, 20);
		labela = gtk_label_new("Aukerak:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		cmbAukerak = gtk_combo_box_new_text();
		gtk_box_pack_start(GTK_BOX(hBox), cmbAukerak, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
	/* Ados eta Utzi botoiak sortu eta sartu */
	hBox = gtk_hbox_new(TRUE, 10);
	botoia = gtk_button_new_with_label("Utzi");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
	botoia = gtk_button_new_with_label("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, TRUE, TRUE, 0);

	form_Load(gaia);

	/* Dena bistaratu */
	gtk_widget_show_all(frmSartuGaia);
	gtk_main();

}
