#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "modSarrera.h"
#define true 1
#define false 0

	static GtkWidget *txtIzena, *txtHelbidea, *txtTelefonoa, *txtPK, *txtHerria;
	static GtkWidget *hBoxBilaketa;
	static GtkWidget *konboa;
	int Berria;
	static int pos=0;

	static MYSQL_ROW errenkada;
	static GtkWidget *mezua;

void HPantailaBete()
{
	if (pos == mysql_num_rows(rstHornitzaileak)) pos = mysql_num_rows(rstHornitzaileak)-1;
	if (pos == -1) pos = 0;
	mysql_data_seek (rstHornitzaileak, pos);
	if ((errenkada = mysql_fetch_row (rstHornitzaileak)) == NULL)
	{
		gtk_entry_set_text (GTK_ENTRY(txtIzena), "");
		gtk_entry_set_text (GTK_ENTRY(txtHelbidea), "");
		gtk_entry_set_text (GTK_ENTRY(txtTelefonoa), "");
		gtk_entry_set_text (GTK_ENTRY(txtPK), "");
		gtk_entry_set_text (GTK_ENTRY(txtHerria), "");
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY(txtIzena), errenkada[1]);
		gtk_entry_set_text (GTK_ENTRY(txtHelbidea), errenkada[2]);
		gtk_entry_set_text (GTK_ENTRY(txtTelefonoa), errenkada[3]);
		gtk_entry_set_text (GTK_ENTRY(txtPK), errenkada[4]);
		gtk_entry_set_text (GTK_ENTRY(txtHerria), errenkada[5]);
		Berria=false;
	}
}

static void form_load()
{
	mysql_query (dbElkartea, "select * from Hornitzaileak");
	rstHornitzaileak=mysql_store_result(dbElkartea);
	if ((errenkada = mysql_fetch_row(rstHornitzaileak)) != NULL)
	{
		Berria = false;
		HPantailaBete();
	}
	else
	{
		mezua = gtk_message_dialog_new(GTK_WINDOW(frmHornitzaileak),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dago Hornitzailearik!");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		Berria = true;
		HPantailaBete();
	}
}

static void btmLehenengoa()
{
	pos = 0;
	HPantailaBete();
}

static void btmHurrengoa()
{
	pos++;
	HPantailaBete();
}

static void btmAurrekoa()
{
	pos--;
	HPantailaBete();
}

static void btmAzkenekoa()
{
	pos = mysql_num_rows(rstHornitzaileak)-1;
	HPantailaBete();
}

void HBilaketaHasi()
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	mysql_query (dbElkartea, "SELECT HIzena FROM Hornitzaileak order by HIZena");
	res = mysql_store_result (dbElkartea);
	int i=0;
	while ((row = mysql_fetch_row (res)) != NULL)
	{
		gtk_combo_box_remove_text (GTK_COMBO_BOX(konboa), i);
		gtk_combo_box_insert_text (GTK_COMBO_BOX(konboa), i, row[0]);
		i++;
	}
	gtk_combo_box_remove_text (GTK_COMBO_BOX(konboa), i);
}

static void btmBilatu()
{
	gtk_widget_show (GTK_WIDGET(hBoxBilaketa));
	HBilaketaHasi();
}

static void btmEzabatu()
{
	if(!Berria)
	{
		mezua = gtk_message_dialog_new(GTK_WINDOW(frmHornitzaileak),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_YES_NO,
					"Zihur al zaude datuak ezabatu nahi dituzula?");
		gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		if (erantzuna == GTK_RESPONSE_YES)
		{
			gchar sql[300];
			sprintf (sql, "delete from Hornitzaileak where HGakoa=%d", atoi(errenkada[0]));
			mysql_query (dbElkartea, sql);
			mysql_free_result (rstHornitzaileak);
			form_load();
		}
	}
	/* Bilaketako konboa aktualizatu, erabiltzailea kendu */
	HBilaketaHasi();
}

static void btmGorde()
{
	mezua = gtk_message_dialog_new(GTK_WINDOW(frmHornitzaileak),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_YES_NO,
					"Zihur al zaude datuak gorde nahi dituzula?");
	gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
	gtk_widget_destroy (mezua);
	if (erantzuna == GTK_RESPONSE_YES)
	{
		gchar sql[500];
		if (Berria)
		{
			sprintf (sql, "insert into Hornitzaileak (HIzena, HHelbidea, HTel, HPK, HHerria) values ('%s', '%s', '%s', '%s', '%s')", gtk_entry_get_text(GTK_ENTRY(txtIzena)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)));
			int erantzuna;
			if ((erantzuna = mysql_query(dbElkartea, sql)) != 0)
			{
				mezua = gtk_message_dialog_new(GTK_WINDOW(frmHornitzaileak),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_OK,
					"Daturen bat ez dago ondo sartuta!");
				gtk_dialog_run(GTK_DIALOG(mezua));
				gtk_widget_destroy(mezua);
			}
			else
			{
				Berria=false;
				mysql_free_result(rstHornitzaileak);
				pos=0;
				HBilaketaHasi();
				form_load();
			}
		}
		else
		{
			sprintf(sql, "update Hornitzaileak set HIzena='%s', HHelbidea='%s', HTel=%d, HPK=%d, HHerria='%s' where HGakoa=%d", gtk_entry_get_text(GTK_ENTRY(txtIzena)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)), atoi(errenkada[0]));
			if ((erantzuna = mysql_query(dbElkartea, sql)) != 0)
			{
				mezua = gtk_message_dialog_new(GTK_WINDOW(frmHornitzaileak),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_OK,
					"Daturen bat ez dago ondo sartuta!");
				gtk_dialog_run(GTK_DIALOG(mezua));
				gtk_widget_destroy(mezua);
			}
			else
			{
				mysql_free_result(rstHornitzaileak);
				HBilaketaHasi();
				form_load();
			}
		}
	}
}

static void btmDesegin()
{
	HPantailaBete();
}

static void btmBerria()
{
	gtk_entry_set_text (GTK_ENTRY(txtIzena), "");
	gtk_entry_set_text (GTK_ENTRY(txtHelbidea), "");
	gtk_entry_set_text (GTK_ENTRY(txtTelefonoa), "");
	gtk_entry_set_text (GTK_ENTRY(txtPK), "");
	gtk_entry_set_text (GTK_ENTRY(txtHerria), "");
	Berria=true;
}

static void cmbBilaketa()
{
	gchar *hornitzailea;
	hornitzailea = gtk_combo_box_get_active_text (GTK_COMBO_BOX(konboa));
	mysql_data_seek (rstHornitzaileak, 0);
	pos=-1;
	while ((errenkada=mysql_fetch_row(rstHornitzaileak)) != NULL)
	{
		pos++;
		if (strcmp(errenkada[1], hornitzailea)==0) break;
	}
	HPantailaBete();
}

static void btmBilaketaItxi()
{
	gtk_widget_hide (GTK_WIDGET(hBoxBilaketa));
}

static void btmAdos()
{
	MYSQL_ROW row;

	mysql_data_seek (rstHornitzaileak, 0);
	if ((row=mysql_fetch_row(rstHornitzaileak))!=NULL)
	{
		if (!(  (strcmp(gtk_entry_get_text(GTK_ENTRY(txtIzena)), errenkada[1])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), errenkada[2])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtTelefonoa)), errenkada[3])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtPK)), errenkada[4])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtHerria)), errenkada[5])==0)) )
		{
			mezua = gtk_message_dialog_new(GTK_WINDOW(frmHornitzaileak),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_YES_NO,
					"Aldaketak gorde nahi al dituzu?");
			int erantzuna;
			if ((erantzuna=gtk_dialog_run(GTK_DIALOG(mezua)))==GTK_RESPONSE_YES)
			{
				gtk_widget_destroy (mezua);
				gchar sql[500];
				if (Berria)
				{
					sprintf (sql, "insert into Hornitzaileak (HIzena, HHelbidea, HTel, HPK, HHerria) values ('%s', '%s', '%s', '%s', '%s')", gtk_entry_get_text(GTK_ENTRY(txtIzena)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)));
					int erantzuna;
				}
				else
				{
					sprintf(sql, "update Hornitzaileak set HIzena='%s', HHelbidea='%s', HTel=%d, HPK=%d, HHerria='%s' where HGakoa=%d", gtk_entry_get_text(GTK_ENTRY(txtIzena)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)), atoi(errenkada[0]));
				}
				if ((erantzuna = mysql_query(dbElkartea, sql)) != 0)
				{
					mezua = gtk_message_dialog_new(GTK_WINDOW(frmHornitzaileak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Daturen bat ez dago ondo sartuta!");
					gtk_dialog_run(GTK_DIALOG(mezua));
					gtk_widget_destroy(mezua);
				}
				else
				{
					mysql_free_result(rstHornitzaileak);
					gtk_widget_destroy(frmHornitzaileak);
					gtk_main_quit();
				}
			}
			else
			{
				gtk_widget_destroy (mezua);
				mysql_free_result(rstHornitzaileak);
				gtk_widget_destroy(frmHornitzaileak);
				gtk_main_quit();
			}
		}
		else
		{
			mysql_free_result(rstHornitzaileak);
			gtk_widget_destroy(frmHornitzaileak);
			gtk_main_quit();
		}
	}
	else
	{
		mysql_free_result(rstHornitzaileak);
		gtk_widget_destroy(frmHornitzaileak);
		gtk_main_quit();
	}
}

void hornitzaileak(GtkWidget *aita)
{
	GtkWidget *frame;
	GtkWidget *botoia;
	GtkWidget *marra;
	GtkWidget *irudia;
	GtkWidget *hBox;
	GtkWidget *taula;
	GtkWidget *labela;

	/* Lehio sortu eta definitu */
	frmHornitzaileak = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmHornitzaileak), FALSE);
	gtk_window_set_position (GTK_WINDOW(frmHornitzaileak), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_type_hint (GTK_WINDOW(frmHornitzaileak), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmHornitzaileak), GTK_WINDOW(aita));
	gtk_window_set_modal (GTK_WINDOW(frmHornitzaileak), TRUE);

	/* Lehioaren egitura osatu */
	frame = gtk_frame_new("HORNITZAILEAK");
	gtk_container_add (GTK_CONTAINER(frmHornitzaileak), frame);

	/* Taula egitura bat erabiliko dugu formularioko elementuak kokatzeko */
	taula = gtk_table_new (4, 10, FALSE);
	gtk_container_add (GTK_CONTAINER(frame), taula);
	
	/* goiko botoiak sortu eta ezarri */
	hBox = gtk_hbox_new (TRUE, 5);
	gtk_table_attach_defaults (GTK_TABLE(taula), hBox, 0, 4, 0, 1);
		/* Mugimendu botoiak sartu */
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/lenengoa2.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmLehenengoa), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/aurrekoa2.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmAurrekoa), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/hurrengoa2.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmHurrengoa), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/azkenekoa2.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmAzkenekoa), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
	hBox = gtk_hbox_new (TRUE, 5);
	gtk_table_attach_defaults (GTK_TABLE(taula), hBox, 5, 10, 0, 1);
		/* Ekintza botoiak sartu */
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/bilatu2.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBilatu), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/gorde2.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmGorde), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/berria.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBerria), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/ezabatu2.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmEzabatu), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		botoia = gtk_button_new();
		irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/desegin4.png");
		gtk_container_add (GTK_CONTAINER(botoia), irudia);
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmDesegin), NULL);
		gtk_box_pack_start (GTK_BOX(hBox), botoia, FALSE, FALSE, 0);

	/* Bilatzeko konboaa eta botoia sortu eta sartu */
	hBoxBilaketa = gtk_hbox_new(FALSE, 1);
	konboa = gtk_combo_box_new_text();
	g_signal_connect(G_OBJECT(konboa), "changed",
			G_CALLBACK(cmbBilaketa), NULL);
	gtk_box_pack_start (GTK_BOX(hBoxBilaketa), konboa, TRUE, TRUE, 0);
	botoia = gtk_button_new_with_label ("X");
	gtk_box_pack_start (GTK_BOX(hBoxBilaketa), botoia, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmBilaketaItxi), NULL);
	gtk_table_attach_defaults (GTK_TABLE(taula), hBoxBilaketa, 0, 4, 1, 2);

	/* Ados botoia sortu eta sartu */
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	gtk_table_attach_defaults (GTK_TABLE(taula), botoia, 3, 7, 3, 4);

	/* Hornitzailearen datuak azaltzeko testu areak sortu eta sartu */
	frame = gtk_frame_new ("");
	gtk_table_attach_defaults (GTK_TABLE(taula), frame, 0, 10, 2, 3);
	taula = gtk_table_new (5, 6, FALSE);
	gtk_container_add (GTK_CONTAINER(frame), taula);
		/* Sortutako taula egituran elementuak sartu */
		marra = gtk_hseparator_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), marra, 0, 6, 0, 1);
		labela = gtk_label_new("Hornitzaile izena");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 2, 1, 2);
		txtIzena = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtIzena, 2, 5, 1, 2);
		labela = gtk_label_new("Helbidea");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 2, 3);
		txtHelbidea = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtHelbidea, 1, 3, 2, 3);
		labela = gtk_label_new("Telefonoa");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 2, 3);
		txtTelefonoa = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtTelefonoa, 4, 6, 2, 3);
		labela = gtk_label_new("Posta kodea");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 3, 4);
		txtPK = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtPK, 1, 3, 3, 4);
		labela = gtk_label_new("Herria");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 3, 4);
		txtHerria = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtHerria, 4, 6, 3, 4);
		marra = gtk_hseparator_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), marra, 0, 6, 4, 5);

	/* Dena bistaratu, bilaketa konboa izan ezik */
	gtk_widget_show_all(frmHornitzaileak);
	gtk_widget_hide (GTK_WIDGET(hBoxBilaketa));

	form_load();

	gtk_main();
}
