#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <string.h>
#include "modSarrera.h"
#include "aukerak.h"
#define true 1
#define false 0

	static GtkWidget *txtKodea;
	static GtkWidget *lblTestua;
	static int ident=false;

static void zenbakiaIdatzi(GtkWidget *botoia, gpointer datuak)
{
	gchar kodea[10];
	strcpy (kodea, gtk_entry_get_text (GTK_ENTRY(txtKodea)));
	if (strcmp(datuak, "DEL")!=0)
	{
		if (strlen (kodea)!= 10)
		{
			strcat (kodea, datuak);
			gtk_entry_set_text (GTK_ENTRY(txtKodea), kodea);
		}
	}
	else
	{
		if (strlen(kodea) != 0)
		{
			kodea[strlen(gtk_entry_get_text(txtKodea))-1] = '\0';
			gtk_entry_set_text (GTK_ENTRY(txtKodea), kodea);
		}
	}
}

static void btmAdos()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char sql[300];
	int a;

	if (ident==false)
	{
		mysql_query(dbElkartea, "Select * from Bazkideak");
		rstBazkideak = mysql_use_result(dbElkartea);
		if ((row=mysql_fetch_row(rstBazkideak))!=NULL)
		{
			mysql_free_result(rstBazkideak);
			sprintf(sql, "Select * from Bazkideak where Zenbakia1=%d", atoi(gtk_entry_get_text(txtKodea)));
			mysql_query (dbElkartea, sql);
			res = mysql_store_result (dbElkartea);
			if ((row=mysql_fetch_row(res)) != NULL)
			{
				sprintf(sql, "<span size='x-large'><b>Kaixo %s %s %s,\n sakatu Ados</b></span>", row[0], row[3], row[4]);
				gtk_label_set_text(lblTestua, sql);
				gtk_label_set_use_markup(lblTestua, TRUE);
				a=true;
				// Uneko bazkidearen kodea eta izen abizenak gorde
				unekoBazkidea = atoi(gtk_entry_get_text(txtKodea));
				sprintf(unekoIzena, "%s %s %s", row[0], row[3], row[4]);
			}
			else
			{
				gtk_label_set_text(lblTestua, "<span size='x-large'><b>Zenbaki okerra. Saiatu berriro</b></span>");
				gtk_label_set_use_markup(lblTestua, TRUE);
				gtk_entry_set_text(GTK_ENTRY(txtKodea), "0");
				a=false;
			}
			mysql_free_result (res);
		}
		else
		{
			mysql_free_result(rstBazkideak);
			GtkWidget *dialog = gtk_message_dialog_new(frmKodea,
							GTK_DIALOG_MODAL,
							GTK_MESSAGE_INFO,
							GTK_BUTTONS_OK,
							"Bazkide-zerrenda hutsa. Ezin duzu jarraitu.");
			gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy (dialog);
		}
	}

	if (ident==true)
	{
		// frmKodea itxi.
		gtk_widget_destroy(frmKodea);

		mysql_query(dbElkartea, "Select Faltak from ElkartekoDatuak");
		rstFaltak = mysql_store_result(dbElkartea);
		if ((row=mysql_fetch_row(rstFaltak))!=NULL)
			if (atoi(row[0])==true)
				TratatuFaltak();
		mysql_free_result(rstFaltak);

// 		BalioakKargatuEusk();

		aukerak();
	}


	ident = a;
}

static void btmUtzi()
{
	ident=false;
	gtk_widget_destroy (frmKodea);
}

void kodea()
{
	GtkWidget *vBox, *hBox;
	GtkWidget *botoia;
	GtkWidget *taula;
	GtkWidget *labela;
	GtkWidget *frame;
	GtkWidget *alignment;
	char *zenb;
	GdkColor kolorea;
	

	/* frmKodea sortu eta hasieratu */
	frmKodea = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_decorated (GTK_WINDOW(frmKodea), FALSE);
	gtk_window_set_position (GTK_WINDOW(frmKodea), GTK_WIN_POS_CENTER_ALWAYS);

	frame = gtk_frame_new("");
	gtk_container_add (GTK_CONTAINER(frmKodea), frame);
	gdk_color_parse("#e3e0e0", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER(alignment), vBox);

	/* labela sortu eta sartu */
	lblTestua = gtk_label_new ("<span size='x-large'><b>Sar ezazu Bazkide-Zenbakia</b></span>");
	gtk_label_set_use_markup(lblTestua, TRUE);
	gtk_label_set_justify(lblTestua, GTK_JUSTIFY_CENTER);
	gtk_box_pack_start (GTK_BOX(vBox), lblTestua, TRUE, FALSE, 20);

	hBox = gtk_hbox_new(FALSE, 20);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);
	
	/* Ados eta Utzi botoiak sortu eta sartu */
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX (hBox), vBox, FALSE, FALSE, 0);
	labela = gtk_label_new("<span size='x-large'>Ados</span>");
	gtk_label_set_use_markup(labela, TRUE);
	botoia = gtk_button_new();
	gtk_container_add(botoia, labela);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_box_pack_start (GTK_BOX(vBox), botoia, FALSE, FALSE, 30);
	labela = gtk_label_new("<span size='x-large'>Utzi</span>");
	gtk_label_set_use_markup(labela, TRUE);
	botoia = gtk_button_new();
	gtk_container_add(botoia, labela);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_box_pack_start (GTK_BOX(vBox), botoia, FALSE, FALSE, 30);
	
	/* Kodea idazteko panela sortu eta sartu */
	frame = gtk_frame_new("");
	gtk_box_pack_start (GTK_WIDGET(hBox), frame, FALSE, FALSE, 0);
	gdk_color_parse("#858484", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frame), vBox);
		
		/* Testua sortu eta sartu */
		txtKodea = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(txtKodea), "");
		gtk_entry_set_max_length (GTK_ENTRY(txtKodea), 10);
		gtk_widget_set_size_request(txtKodea, 220, 40);
		gtk_box_pack_start (GTK_BOX(vBox), txtKodea, FALSE, FALSE, 0);

		/* Zenbakiak sartzeko botoiak sortu eta sartu */
		taula = gtk_table_new(4, 3, TRUE);
		gtk_box_pack_start (GTK_BOX(vBox), taula, TRUE, FALSE, 10);
		labela = gtk_label_new("<span size='x-large'>0</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="0";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 3, 4);
		labela = gtk_label_new("<span size='x-large'>DEL</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="DEL";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 3, 3, 4);
		labela = gtk_label_new("<span size='x-large'>1</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="1";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 2, 3);
		labela = gtk_label_new("<span size='x-large'>2</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="2";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 2, 3);
		labela = gtk_label_new("<span size='x-large'>3</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="3";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 2, 3);
		labela = gtk_label_new("<span size='x-large'>4</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="4";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 1, 2);
		labela = gtk_label_new("<span size='x-large'>5</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="5";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 1, 2);
		labela = gtk_label_new("<span size='x-large'>6</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="6";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 1, 2);
		labela = gtk_label_new("<span size='x-large'>7</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="7";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 0, 1, 0, 1);
		labela = gtk_label_new("<span size='x-large'>8</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="8";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 1, 2, 0, 1);
		labela = gtk_label_new("<span size='x-large'>9</span>");
		gtk_label_set_use_markup(labela, TRUE);
		botoia = gtk_button_new();
		gtk_container_add(botoia, labela);
		zenb="9";
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(zenbakiaIdatzi), (gpointer) zenb);
		gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 2, 3, 0, 1);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmKodea);
	ident = false;
}
