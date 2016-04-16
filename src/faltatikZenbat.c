#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"

	static GtkWidget *txtKopurua;
	static GtkWidget *lblIzena;
	static int Kopurua;

static void zenbakiaIdatzi(GtkWidget *botoia, gpointer datuak)
{
	gchar kodea[10];
	strcpy (kodea, gtk_entry_get_text (GTK_ENTRY(txtKopurua)));
	if (strcmp(datuak, "DEL")!=0)
	{
		if (strlen (kodea)!= 10)
		{
			strcat (kodea, datuak);
			gtk_entry_set_text (GTK_ENTRY(txtKopurua), kodea);
		}
	}
	else
	{
		if (strlen(kodea) != 0)
		{
			kodea[strlen(gtk_entry_get_text(GTK_ENTRY(txtKopurua)))-1] = '\0';
			gtk_entry_set_text (GTK_ENTRY(txtKopurua), kodea);
		}
	}
}

static void form_load(int zenb, char izen[20])
{
	char testua[100];
	sprintf(testua, "<span size='x-large'>%s</span>", izen);
	gtk_label_set_text(GTK_LABEL(lblIzena), testua);
	gtk_label_set_use_markup(GTK_LABEL(lblIzena), TRUE);
	char zenbakia[5];
	sprintf(zenbakia, "%d", zenb);
	gtk_entry_set_text(GTK_ENTRY(txtKopurua), zenbakia);
	Kopurua=zenb;
}

static void btmAdos()
{
	MYSQL_ROW row;
	char sql[500];

	/* Onartutako falten kopurua ez dela 0 edo negatiboa kontrolatu */
	if (atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)))<=0)
	{
		GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(frmFaltatikZenbat),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_ERROR,
						GTK_BUTTONS_OK,
						"Barkatu, onartutako falten kopurua ezin da 0 edo negatibo izan.");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy (dialog);
	}
	else
	{
		sprintf(sql, "Select GKodea,AKodea,Gprezioa from Gaiak where Gizenaeus='%s'", gtk_label_get_text(GTK_LABEL(lblIzena)));
		mysql_query(dbElkartea, sql);
		rstGaiak=mysql_store_result(dbElkartea);
		row=mysql_fetch_row(rstGaiak);
		int GKodea=atoi(row[0]);
		int AKodea=atoi(row[1]);
		double prezioa=atof(row[2]);
		mysql_free_result(rstGaiak);
		mysql_data_seek(rstDatuak, 0);
		do
		{
			row=mysql_fetch_row(rstDatuak);
		} while (GKodea!=atoi(row[1]));
		int FKodea = atoi(row[0]);
	
		/* Faltak eguneratu */
		if (atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)))<Kopurua)
		{
			sprintf(sql, "Update Faltak set GKopurua=GKopurua + %d where FKodea=%d", atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua))), FKodea);
			mysql_query(dbElkartea, sql);
		}
		else
		{
			sprintf(sql, "Delete from Faltak where FKodea=%d", FKodea);
			mysql_query(dbElkartea, sql);
		}
	
		/* Kontu berri bat sortu */
		mysql_query(dbElkartea, "select MAX(KKodea) from Kontuak");
		rstKontuak = mysql_use_result(dbElkartea);
		int kzenbakia;
		row=mysql_fetch_row(rstKontuak);
		if (row[0]==NULL) kzenbakia=0;
		else
		{
			kzenbakia=atoi(row[0])+1;
		}
		mysql_free_result(rstKontuak);
		sprintf(sql, "Insert into Kontuak(KKodea, BKodea, GKodea, AKodea, GKopurua, Data, KMota) values(%d, %d, %d, %d, %d, CURDATE(), 'FALTAO')", kzenbakia, unekoBazkidea, GKodea, AKodea, atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua))));
		mysql_query(dbElkartea, sql);
	
		//Faltaren datuak buffer batean gorde (Gairen kodea, zenbat unitate eta unitate bakoitzaren prezioa)
		faltenBufferra[faltaKop].kodea=GKodea;
		faltenBufferra[faltaKop].kopurua=atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)));
		faltenBufferra[faltaKop].prezioa=prezioa;
		faltaKop++;
	
		/* Egin beharreko eragiketak burututa daude, irten */
		gtk_main_quit();
		gtk_widget_destroy(frmFaltatikZenbat);
	}
}

static void btmUtzi()
{
	gtk_main_quit();
	gtk_widget_destroy(frmFaltatikZenbat);
}

void faltatikZenbat(int zenbakia, char *izena)
{
	GtkWidget *vBox, *hBox;
	GtkWidget *botoia;
	GtkWidget *taula;
	GtkWidget *labela;
	GtkWidget *frame;
	GtkWidget *lblTestua;
	GtkWidget *alignment;
	char *zenb;
	GdkColor kolorea;
	

	/* frmFaltatikZenbat sortu eta hasieratu */
	frmFaltatikZenbat = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmFaltatikZenbat), FALSE);
	gtk_window_set_position (GTK_WINDOW(frmFaltatikZenbat), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal(GTK_WINDOW(frmFaltatikZenbat), TRUE);
	gtk_window_set_transient_for(GTK_WINDOW(frmFaltatikZenbat), GTK_WINDOW(frmFaltak));
	gtk_window_set_type_hint (GTK_WINDOW(frmFaltatikZenbat), GDK_WINDOW_TYPE_HINT_DIALOG);

	frame = gtk_frame_new("");
	gtk_container_add (GTK_CONTAINER(frmFaltatikZenbat), frame);
	gdk_color_parse("#e3e0e0", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER(alignment), vBox);

	/* labela sortu eta sartu */
	lblTestua = gtk_label_new ("<span size='x-large'><b>Zenbat onartzen dituzu zure bezala?</b></span>");
	gtk_label_set_use_markup(GTK_LABEL(lblTestua), TRUE);
	gtk_box_pack_start (GTK_BOX(vBox), lblTestua, TRUE, FALSE, 20);

	hBox = gtk_hbox_new(FALSE, 35);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
	
	/* Ados eta Utzi botoiak sortu eta sartu */
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hBox), vBox, FALSE, FALSE, 0);
	lblIzena=gtk_label_new("");
	gtk_box_pack_start (GTK_BOX (vBox), lblIzena, FALSE, FALSE, 0);
	labela = gtk_label_new("<span size='x-large'>Ados</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_box_pack_start (GTK_BOX(vBox), botoia, FALSE, FALSE, 30);
	labela = gtk_label_new("<span size='x-large'>Utzi</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_box_pack_start (GTK_BOX(vBox), botoia, FALSE, FALSE, 30);
	
	/* Kodea idazteko panela sortu eta sartu */
	frame = gtk_frame_new("");
	gtk_box_pack_start (GTK_BOX(hBox), frame, FALSE, FALSE, 0);
	gdk_color_parse("#858484", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frame), vBox);
		
		/* Testua sortu eta sartu */
		txtKopurua = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(txtKopurua), "0");
		gtk_entry_set_editable(GTK_ENTRY(txtKopurua), FALSE);
		gtk_entry_set_max_length (GTK_ENTRY(txtKopurua), 10);
		gtk_widget_set_size_request(txtKopurua, 230, 40);
		gtk_box_pack_start (GTK_BOX(vBox), txtKopurua, FALSE, FALSE, 0);

		taula = gtk_table_new(4, 3, TRUE);
		gtk_box_pack_start (GTK_BOX(vBox), taula, TRUE, FALSE, 10);
		labela = gtk_label_new("<span size='x-large'>0</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="0";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 3, 4);
		labela = gtk_label_new("<span size='x-large'>DEL</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="DEL";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 3, 3, 4);
		labela = gtk_label_new("<span size='x-large'>1</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="1";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 2, 3);
		labela = gtk_label_new("<span size='x-large'>2</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="2";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 2, 3);
		labela = gtk_label_new("<span size='x-large'>3</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="3";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 2, 3);
		labela = gtk_label_new("<span size='x-large'>4</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="4";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 1, 2);
		labela = gtk_label_new("<span size='x-large'>5</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="5";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 1, 2);
		labela = gtk_label_new("<span size='x-large'>6</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="6";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 1, 2);
		labela = gtk_label_new("<span size='x-large'>7</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="7";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 0, 1);
		labela = gtk_label_new("<span size='x-large'>8</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="8";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 0, 1);
		labela = gtk_label_new("<span size='x-large'>9</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		botoia = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(botoia), labela);
		zenb="9";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 0, 1);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmFaltatikZenbat);

	form_load(zenbakia, izena);

	gtk_main();
}
