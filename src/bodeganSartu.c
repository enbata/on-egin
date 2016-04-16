#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "modSarrera.h"
#include "hornitzaileak.h"

	static GtkWidget *txtIzena, *txtElkartekoPrezioa, *txtErosketaKop, *txtErosketaPrezioaUnitateko, *txtBLehendikBodegan, *txtBUnitateBerriak, *txtBErosketaPrezioaUnitateko, *txtBElkartekoPrezioa;
	static GtkWidget *checkMateriala;
	static GtkWidget *cmbAukerak, *cmbHornitzaileak, *cmbBHornitzaileak;
	static GtkWidget *frameGaiBerria, *frameBodegara, *frameBodega;
	static GtkWidget *egitura;
	static GtkWidget *lstGaiak;
	static GtkWidget *AdosBotoia;

void BodegaPantaila()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstGaiak));

	gtk_tree_store_clear(GTK_TREE_STORE(model));

	mysql_query(dbElkartea, "SELECT GIzenaeus,GaiKopurua from Bodega,Gaiak where Gaiak.GKodea = Bodega.Gaikodea ORDER BY GIzenaeus");
	res = mysql_use_result(dbElkartea);
	while ((row=mysql_fetch_row(res))!=NULL)
	{
		gtk_tree_store_append (GTK_TREE_STORE(model), &iter, NULL);
		gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
				0, row[0],
				1, atoi(row[1]),
				-1);
	}
	mysql_free_result (res);
}

static void form_load()
{
	BodegaPantaila();
}

void hornitzaileakBete(GtkWidget *konboa)
{
	MYSQL_ROW row;

	mysql_query(dbElkartea, "select HIzena from Hornitzaileak order by HGakoa");
	rstHornitzaileak = mysql_use_result(dbElkartea);
	int i=0;
	while ((row=mysql_fetch_row(rstHornitzaileak))!=NULL)
	{
		gtk_combo_box_remove_text (GTK_COMBO_BOX(konboa), i);
		gtk_combo_box_insert_text (GTK_COMBO_BOX(konboa), i, row[0]);
		i++;
	}
	mysql_free_result(rstHornitzaileak);
}

static void btmHornitzaileBerria()
{
	hornitzaileak(frmBodeganSartu);
	hornitzaileakBete(cmbHornitzaileak);
}

static void btmGaiBerriaUtzi()
{
	gtk_widget_destroy(frameGaiBerria);
	frameGaiBerria = gtk_frame_new("");
	gtk_widget_show(AdosBotoia);
	gtk_widget_set_sensitive(frameBodega, TRUE);
}

static void btmGaiBerriaAdos()
{
	gchar sql[300];
	MYSQL_ROW row;

	if ( (atoi(gtk_entry_get_text(GTK_ENTRY(txtErosketaKop))) < 1) && (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(checkMateriala)) == 1))
	{
		// Mezua, kopuru desegokia dela esanaz
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmBodeganSartu),
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
			sprintf(sql, "Insert into Bodega values(%d, %d)", GKodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtErosketaKop))));
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
			sprintf(sql, "Insert into Erosketak(GaiKodea, GaiKopurua, Data, HorniKodea, ErosketaPrezioa) values(%d, %d, CURDATE(), %d, '%s')", GKodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtErosketaKop))), HKodea, gtk_entry_get_text(GTK_ENTRY(txtErosketaPrezioaUnitateko)));
			mysql_query(dbElkartea, sql);

			gtk_widget_destroy(frameGaiBerria);
			frameGaiBerria = gtk_frame_new("");
			gtk_widget_show(AdosBotoia);
			gtk_widget_set_sensitive(frameBodega, TRUE);
		}
		else
		{
			//mezua!, datuak ez direla zuzenak esanaz
			GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmBodeganSartu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dituzu datu zuzenak sartu!");
			gtk_dialog_run(GTK_DIALOG(mezua));
			gtk_widget_destroy(mezua);
		}
	}
	BodegaPantaila();
}

void frameGaiBerriaSortu()
{
	GtkWidget *hBox, *vBox;
	GtkWidget *labela;
	GtkWidget *botoia;

	frameGaiBerria = gtk_frame_new("Gai berria sartu");
	gtk_box_pack_end(GTK_BOX(egitura), frameGaiBerria, FALSE, FALSE, 0);
	/* Sortutako frameGaiBerria bete */
	vBox = gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(frameGaiBerria), vBox);
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

	gtk_widget_show_all(frameGaiBerria);
}

static void btmGaiBerria()
{
	if (frameBodegara != NULL) gtk_widget_destroy(frameBodegara);
	if (frameGaiBerria != NULL) gtk_widget_destroy(frameGaiBerria);
	frameGaiBerriaSortu();
	frameBodegara = gtk_frame_new("");
	gtk_widget_hide(AdosBotoia);
	gtk_widget_set_sensitive(frameBodega, FALSE);

	MYSQL_ROW row;

	// Ados botoia desabilitatu behar
	gtk_entry_set_text(GTK_ENTRY(txtIzena), "");
	gtk_entry_set_text(GTK_ENTRY(txtElkartekoPrezioa), "");
	gtk_entry_set_text(GTK_ENTRY(txtErosketaKop), "");
	gtk_entry_set_text(GTK_ENTRY(txtErosketaPrezioaUnitateko), "");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkMateriala), 1);

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

	hornitzaileakBete(cmbHornitzaileak);
}

static void btmAdos()
{
	gtk_widget_destroy(frmBodeganSartu);
}

static void btmBodegaraUtzi()
{
	gtk_widget_destroy(frameBodegara);
	frameBodegara = gtk_frame_new("");
	gtk_widget_show(AdosBotoia);
	gtk_widget_set_sensitive(frameBodega, TRUE);
}

static void btmBHornitzaileBerria()
{
	hornitzaileak(frmBodeganSartu);
	hornitzaileakBete(cmbBHornitzaileak);
}

static void btmBodegaraAdos()
{
	MYSQL_ROW row;

	if (atoi(gtk_entry_get_text(GTK_ENTRY(txtBUnitateBerriak))) < 0)
	{
		// Mezua, kopuru desegokia dela esanaz
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmBodeganSartu),
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
		sprintf (sql, "select GKodea from Gaiak where Gizenaeus='%s'", gtk_frame_get_label(GTK_FRAME(frameBodegara)));
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_use_result(dbElkartea);
		row = mysql_fetch_row(rstGaiak);
		int kodea=atoi(row[0]);
		mysql_free_result(rstGaiak);

		// Gaiaren unitate berriak bodegan sartu
		sprintf(sql, "select Gaikopurua from Bodega where Gaikodea=%d", kodea);
		mysql_query(dbElkartea, sql);
		rstDatuak = mysql_store_result(dbElkartea);
		if ((row = (MYSQL_ROW) mysql_fetch_row(rstDatuak)) != NULL)
		{
			sprintf(sql, "Update Bodega set Gaikopurua=Gaikopurua + %d where Gaikodea=%d", atoi(gtk_entry_get_text(GTK_ENTRY(txtBUnitateBerriak))), kodea);
			mysql_query(dbElkartea, sql);
		}
		else
		{
			sprintf(sql, "Insert into Bodega values (%d, %d)", kodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtBUnitateBerriak))));
			mysql_query(dbElkartea, sql);
		}
		mysql_free_result(rstDatuak);

		// Erosketa berria sartu datu basean
		int HKodea;
		if (gtk_combo_box_get_active(GTK_COMBO_BOX(cmbBHornitzaileak)) == -1) HKodea=0;
		else
		{
			sprintf(sql, "Select HGakoa from Hornitzaileak where HIzena='%s'", gtk_combo_box_get_active_text(GTK_COMBO_BOX(cmbBHornitzaileak)));
			mysql_query(dbElkartea, sql);
			rstHornitzaileak = mysql_use_result(dbElkartea);
			row=mysql_fetch_row(rstHornitzaileak);
			HKodea=atoi(row[0]);
			mysql_free_result(rstHornitzaileak);
		}
		sprintf(sql, "Insert into Erosketak(GaiKodea, GaiKopurua, data, HorniKodea, ErosketaPrezioa) values(%d, %d, CURDATE(), %d, '%s')", kodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtBUnitateBerriak))), HKodea, gtk_entry_get_text(GTK_ENTRY(txtBErosketaPrezioaUnitateko)));
		mysql_query(dbElkartea, sql);

		// Gaiaren elkarteko prezioa berritu
		sprintf(sql, "Update Gaiak set Gprezioa='%s' where GKodea=%d", gtk_entry_get_text(GTK_ENTRY(txtBElkartekoPrezioa)), kodea);
		mysql_query(dbElkartea, sql);

		BodegaPantaila();
		gtk_widget_destroy(frameBodegara);
		frameBodegara = gtk_frame_new("");
		gtk_widget_show(AdosBotoia);
		gtk_widget_set_sensitive(frameBodega, TRUE);
	}
}

void frameBodegaraSortu()
{
	GtkWidget *hBox, *vBox;
	GtkWidget *labela;
	GtkWidget *botoia;

	frameBodegara = gtk_frame_new("");
	gtk_box_pack_start(GTK_BOX(egitura), frameBodegara, FALSE, FALSE, 0);
	/* Sortutako frameBodegara bete */
	vBox = gtk_vbox_new(TRUE, 5);
	gtk_container_add(GTK_CONTAINER(frameBodegara), vBox);
		/* Lehendik bodegan */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Lehendik bodegan:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtBLehendikBodegan = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtBLehendikBodegan, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Unitate berriak */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Unitate berriak:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtBUnitateBerriak = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtBUnitateBerriak, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Erosketa prezioa unitateko */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Erosketa prezioa unitateko:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtBErosketaPrezioaUnitateko = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtBErosketaPrezioaUnitateko, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Elkarteko prezioa */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Elkarteko prezioa:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		txtBElkartekoPrezioa = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hBox), txtBElkartekoPrezioa, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Hornitzailea konboa */
		hBox = gtk_hbox_new(TRUE, 3);
		labela = gtk_label_new("Hornitzailea:");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		cmbBHornitzaileak = gtk_combo_box_new_text();
		gtk_box_pack_start(GTK_BOX(hBox), cmbBHornitzaileak, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
		/* Hornitzaile berria sartzeko botoia */
		botoia = gtk_button_new_with_label("Hornitzaile berria sartu");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBHornitzaileBerria), NULL);
		gtk_box_pack_start(GTK_BOX(vBox), botoia, FALSE, FALSE, 0);
		/* Utzi eta Ados botoiak */
		hBox = gtk_hbox_new(TRUE, 20);
		botoia = gtk_button_new_with_label("Utzi");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBodegaraUtzi), NULL);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
		botoia = gtk_button_new_with_label("Ados");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBodegaraAdos), NULL);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 10);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	gtk_widget_show_all(frameBodegara);
}

static void lstGaiak_click(GtkWidget *lista)
{
	if (GTK_WIDGET(frameBodegara) != NULL) gtk_widget_destroy(frameBodegara);
	if (GTK_WIDGET(frameGaiBerria) != NULL) gtk_widget_destroy(frameGaiBerria);
	frameBodegaraSortu();
	frameGaiBerria = gtk_frame_new("");
	gtk_widget_hide(AdosBotoia);
	gtk_widget_set_sensitive(frameBodega, FALSE);

	gtk_entry_set_text(GTK_ENTRY(txtBUnitateBerriak), "");
	gtk_entry_set_text(GTK_ENTRY(txtBErosketaPrezioaUnitateko), "");

	// Lista aukeratutako datuak lortu eta frameBodegan datuak sartu berauen arabera
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lista));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lista));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *izena;
		gchar kop[5];
		int kopurua;
		gtk_tree_model_get (model, &iter, 0, &izena, -1);
		gtk_tree_model_get (model, &iter, 1, &kopurua, -1);
		gtk_frame_set_label(GTK_FRAME(frameBodegara), izena);
		sprintf(kop, "%d" , kopurua);
		gtk_entry_set_text (GTK_ENTRY(txtBLehendikBodegan), kop);

		gchar sql[100];
		MYSQL_ROW row;
		sprintf(sql, "Select Gprezioa from Gaiak where Gizenaeus='%s'", izena);
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_use_result(dbElkartea);
		if ((row=mysql_fetch_row(rstGaiak))!=NULL)
			if (row[0]!=NULL)
				gtk_entry_set_text(GTK_ENTRY(txtBElkartekoPrezioa), row[0]);
		mysql_free_result(rstGaiak);
	}
	hornitzaileakBete(cmbBHornitzaileak);
}

void bodeganSartu()
{
	GtkWidget *frame;
	GtkWidget *hBox, *vBox;
	GtkWidget *botoia;
	GtkWidget *labela;
	GtkWidget *scrolla;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;

	/* Lehioa sortu eta konfiguratu */
	frmBodeganSartu=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmBodeganSartu), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW(frmBodeganSartu), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_modal (GTK_WINDOW(frmBodeganSartu), TRUE);
	gtk_window_set_transient_for(GTK_WINDOW(frmBodeganSartu), GTK_WINDOW(frmAdministraria));
	gtk_window_set_position (GTK_WINDOW(frmBodeganSartu), GTK_WIN_POS_CENTER_ALWAYS);

	/* Lehioaren egitura sortu */
	frame = gtk_frame_new("Bodegan Sartu");
	gtk_container_add(GTK_CONTAINER(frmBodeganSartu), frame);
	hBox = gtk_hbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(frame), hBox);

	/* Bodegaren aldea egituratu */
	frameBodega = gtk_frame_new("Bodega");
	gtk_box_pack_start(GTK_BOX(hBox), frameBodega, FALSE, FALSE, 0);
	vBox = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(frameBodega), vBox);
		/* Gaien lista sortu eta sartu */
		scrolla = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolla), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_widget_set_size_request (scrolla, 296, 376);
		gtk_box_pack_start(GTK_BOX(vBox), scrolla, FALSE, FALSE, 0);
		model = GTK_TREE_MODEL (gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT));
		lstGaiak = gtk_tree_view_new_with_model(model);
		g_signal_connect(G_OBJECT(lstGaiak), "cursor-changed",
				G_CALLBACK(lstGaiak_click), NULL);
		renderer = gtk_cell_renderer_text_new ();
        	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstGaiak),
						-1, "Zer", renderer,
						"text", 0,
						NULL);
		renderer = gtk_cell_renderer_text_new ();
        	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstGaiak),
						-1, "Zenbat", renderer,
						"text", 1,
						NULL);
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolla), lstGaiak);
		
		/* Gai berria sartzeko botoia sortu eta sartu */
		botoia = gtk_button_new_with_label("Gai berria sartu");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmGaiBerria), NULL);
		gtk_box_pack_start(GTK_BOX(vBox), botoia, FALSE, FALSE, 0);

	/* Frame -ak jartzeko egitura eta Ados botoia sortu eta sartu */
	egitura = gtk_vbox_new(FALSE, 10);
	gtk_box_pack_start(GTK_BOX(hBox), egitura, FALSE, FALSE, 0);
	
	
		/* Ados botoia sortu eta sartu */
		AdosBotoia = gtk_button_new_with_label("Ados");
		g_signal_connect(G_OBJECT(AdosBotoia), "clicked",
				G_CALLBACK(btmAdos), NULL);
		gtk_widget_set_size_request (GTK_WIDGET(AdosBotoia), 100, 50);
		gtk_box_pack_start(GTK_BOX(egitura), AdosBotoia, TRUE, FALSE, 0);
		
		

	/* Dena bistaratu eta martxa jarri */
	gtk_widget_show_all(frmBodeganSartu);

	form_load();
}
