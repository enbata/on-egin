#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "modSarrera.h"
#define false 0
#define true 1

	static GtkWidget *frameZenbat, *frameFalta, *lblAurrekoa, *lblAzkena, *txtFKodea, *txtKopurua, *txtGaia, *txtZenbat;
	int posizioa=0;
	int Ordaindua;
	
	MYSQL_ROW falta;

void datuakKargatu()
{
	char sql[200];
	MYSQL_ROW row;

	if (posizioa == mysql_num_rows(rstFaltak)) posizioa = mysql_num_rows(rstFaltak)-1;
	if (posizioa == -1) posizioa = 0;
	mysql_data_seek (rstFaltak, posizioa);
	if ((falta = mysql_fetch_row (rstFaltak)) == NULL)
	{
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmFaltenGestioa),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dago faltarik.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		
		mysql_free_result(rstFaltak);
		gtk_widget_destroy(frmFaltenGestioa);
	}
	else
	{
		gtk_label_set_text(GTK_LABEL(lblAurrekoa), falta[3]);
		gtk_label_set_text(GTK_LABEL(lblAzkena), falta[4]);
		gtk_entry_set_text(GTK_ENTRY(txtFKodea), falta[0]);
		gtk_entry_set_text(GTK_ENTRY(txtKopurua), falta[2]);
		sprintf(sql, "Select Gizenaeus from Gaiak where GKodea=%d", atoi(falta[1]));
		mysql_query(dbElkartea, sql);
		rstDatuak = mysql_use_result(dbElkartea);
		row=mysql_fetch_row(rstDatuak);
		gtk_entry_set_text(GTK_ENTRY(txtGaia), row[0]);
		mysql_free_result(rstDatuak);
	}
}

static void form_load()
{
	mysql_query(dbElkartea, "select * from Faltak");
	rstFaltak = mysql_store_result(dbElkartea);
	posizioa=0;
	datuakKargatu();
}

static void btmAdos()
{
	mysql_free_result(rstFaltak);
	gtk_widget_destroy(frmFaltenGestioa);
}

static void btmLehenengoa()
{
	posizioa = 0;
	datuakKargatu();
}

static void btmAurrekoa()
{
	posizioa--;
	datuakKargatu();
}

static void btmHurrengoa()
{
	posizioa++;
	datuakKargatu();
}

static void btmAzkenekoa()
{
	posizioa =  mysql_num_rows(rstFaltak)-1;
	datuakKargatu();
}

static void btmOrdaindua()
{
	Ordaindua = true;
	char balioa[5];
	sprintf(balioa, "%d", abs(atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)))));
	gtk_entry_set_text(GTK_ENTRY(txtZenbat), balioa);
	gtk_widget_show(frameZenbat);
	gtk_widget_set_sensitive(frameFalta, FALSE);
}

static void btmBeregain()
{
	Ordaindua = false;
	char balioa[5];
	sprintf(balioa, "%d", abs(atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)))));
	gtk_entry_set_text(GTK_ENTRY(txtZenbat), balioa);
	gtk_widget_show(frameZenbat);
	gtk_widget_set_sensitive(frameFalta, FALSE);
}

static void btmUtzi()
{
	gtk_widget_hide(frameZenbat);
	gtk_widget_set_sensitive(frameFalta, TRUE);
}

static void btmZenbatAdos()
{
	MYSQL_ROW row;
	char sql[500];

	if (abs(atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbat)))) < abs(atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)))))
		if (atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)))>0)
		{
			sprintf(sql, "Update Faltak set GKopurua=%d-%d where FKodea=%d", atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua))), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbat))), atoi(gtk_entry_get_text(GTK_ENTRY(txtFKodea))));
			mysql_query(dbElkartea, sql);
		}
		else
		{
			sprintf(sql, "Update Faltak set GKopurua=%d+%d where FKodea=%d", atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua))), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbat))), atoi(gtk_entry_get_text(GTK_ENTRY(txtFKodea))));
			mysql_query(dbElkartea, sql);
		}
	else
	{
		sprintf(sql, "Delete from Faltak where FKodea=%d", atoi(gtk_entry_get_text(GTK_ENTRY(txtFKodea))));
		mysql_query(dbElkartea, sql);
		posizioa=0;
	}

	/* Kontua taulan erregistro berria sartu */
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
	sprintf(sql, "select * from Gaiak where Gizenaeus='%s'", gtk_entry_get_text(GTK_ENTRY(txtGaia)));
	mysql_query(dbElkartea, sql);
	rstGaiak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstGaiak);
	char *falta;
	if (Ordaindua) falta="FALTAO";
	else falta="FALTAA";
	sprintf(sql, "Insert into Kontuak(KKodea, BKodea, GKodea, AKodea, GKopurua, Data, KMota)  values(%d,0,%d,%d,%d,CURDATE(),'%s')", kzenbakia, atoi(row[4]), atoi(row[5]), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbat))), falta);
	mysql_query(dbElkartea, sql);
	mysql_free_result(rstGaiak);

	gtk_widget_hide(frameZenbat);
	gtk_widget_set_sensitive(frameFalta, TRUE);

	mysql_free_result(rstFaltak);
	mysql_query(dbElkartea, "select * from Faltak");
	rstFaltak = mysql_store_result(dbElkartea);
	datuakKargatu();
}

void faltenGestioa()
{
	GtkWidget *frame;
	GtkWidget *alignment;
	GtkWidget *fixedNagusia;
	GtkWidget *fixed;
	GtkWidget *botoia;
	GtkWidget *irudia;
	GtkWidget *labela;
	
	/* Lehioa sortu eta definitu */
	frmFaltenGestioa = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmFaltenGestioa), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmFaltenGestioa), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmFaltenGestioa), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmFaltenGestioa), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for(GTK_WINDOW(frmFaltenGestioa), GTK_WINDOW(frmAdministraria));

	/* Lehioaren egitura sortu */
	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (frmFaltenGestioa), frame);

	labela = gtk_label_new ("<b>Falten gestioa</b>");
	gtk_frame_set_label_widget (GTK_FRAME (frame), labela);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	
	fixedNagusia = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (alignment), fixedNagusia);

	/* Falten frame-a sortu eta sartu */
	frameFalta = gtk_frame_new ("Faltak");
	gtk_fixed_put (GTK_FIXED (fixedNagusia), frameFalta, 16, 16);
	gtk_widget_set_size_request (frameFalta, 464, 368);
	
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frameFalta), fixed);
	
		/* Faltaren kodea agertzeko testu area sortu eta sartu */
		txtFKodea = gtk_entry_new ();
		gtk_entry_set_editable(GTK_ENTRY(txtFKodea), FALSE);
		gtk_fixed_put (GTK_FIXED (fixed), txtFKodea, 344, 32);
		gtk_widget_set_size_request (txtFKodea, 32, 32);
		
		/* Mugimendu botoiak sortu eta sartu */
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmLehenengoa), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 56, 32);
		gtk_widget_set_size_request (botoia, 32, 32);
		irudia = gtk_image_new_from_stock ("gtk-goto-first", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (botoia), irudia);
		
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmAurrekoa), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 96, 32);
		gtk_widget_set_size_request (botoia, 32, 32);
		irudia = gtk_image_new_from_stock ("gtk-go-back", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (botoia), irudia);
		
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmHurrengoa), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 136, 32);
		gtk_widget_set_size_request (botoia, 32, 32);
		irudia = gtk_image_new_from_stock ("gtk-go-forward", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (botoia), irudia);
		
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmAzkenekoa), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 176, 32);
		gtk_widget_set_size_request (botoia, 32, 32);
		irudia = gtk_image_new_from_stock ("gtk-goto-last", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (botoia), irudia);
		
		/* Faltaren datuak azaltzen diren zatia sortu eta sartu */
		frame = gtk_frame_new (NULL);
		gtk_fixed_put (GTK_FIXED (fixed), frame, 24, 72);
		gtk_widget_set_size_request (frame, 400, 256);
		
		fixed = gtk_fixed_new ();
		gtk_container_add (GTK_CONTAINER (frame), fixed);
		
		lblAurrekoa = gtk_label_new ("Aurrekoa");
		gtk_fixed_put (GTK_FIXED (fixed), lblAurrekoa, 40, 16);
		gtk_widget_set_size_request (lblAurrekoa, 88, 24);
		
		labela = gtk_label_new ("-tik");
		gtk_fixed_put (GTK_FIXED (fixed), labela, 120, 16);
		gtk_widget_set_size_request (labela, 54, 28);
		
		lblAzkena = gtk_label_new ("Azkena");
		gtk_fixed_put (GTK_FIXED (fixed), lblAzkena, 176, 16);
		gtk_widget_set_size_request (lblAzkena, 88, 24);
		
		labela = gtk_label_new ("-ra");
		gtk_fixed_put (GTK_FIXED (fixed), labela, 264, 16);
		gtk_widget_set_size_request (labela, 46, 28);
		
		labela = gtk_label_new ("Gaia:");
		gtk_fixed_put (GTK_FIXED (fixed), labela, 32, 64);
		gtk_widget_set_size_request (labela, 48, 28);
		
		labela = gtk_label_new ("Kopurua:");
		gtk_fixed_put (GTK_FIXED (fixed), labela, 32, 120);
		gtk_widget_set_size_request (labela, 72, 24);
		
		txtGaia = gtk_entry_new ();
		gtk_entry_set_editable(GTK_ENTRY(txtGaia), FALSE);
		gtk_fixed_put (GTK_FIXED (fixed), txtGaia, 104, 64);
		gtk_widget_set_size_request (txtGaia, 216, 24);
		gtk_entry_set_invisible_char (GTK_ENTRY (txtGaia), 9679);
		
		txtKopurua = gtk_entry_new ();
		gtk_entry_set_editable(GTK_ENTRY(txtKopurua), FALSE);
		gtk_fixed_put (GTK_FIXED (fixed), txtKopurua, 104, 120);
		gtk_widget_set_size_request (txtKopurua, 216, 24);
		gtk_entry_set_invisible_char (GTK_ENTRY (txtKopurua), 9679);
		
		botoia = gtk_button_new_with_label ("Eskudirutan");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmOrdaindua), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 40, 176);
		gtk_widget_set_size_request (botoia, 136, 40);
		
		botoia = gtk_button_new_with_label ("Elkartearen gain");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBeregain), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 192, 176);
		gtk_widget_set_size_request (botoia, 136, 40);

	/* Faltak kentzeko frame-a sortu eta sartu */
	frameZenbat = gtk_frame_new (NULL);
	gtk_fixed_put (GTK_FIXED (fixedNagusia), frameZenbat, 504, 80);
	gtk_widget_set_size_request (frameZenbat, 256, 248);
	
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frameZenbat), fixed);
	
	labela = gtk_label_new ("Zenbat unitate kendu nahi dituzu?");
	gtk_fixed_put (GTK_FIXED (fixed), labela, 0, 24);
	gtk_widget_set_size_request (labela, 248, 16);
	
	txtZenbat = gtk_entry_new ();
	gtk_fixed_put (GTK_FIXED (fixed), txtZenbat, 80, 64);
	gtk_widget_set_size_request (txtZenbat, 88, 24);
	gtk_entry_set_invisible_char (GTK_ENTRY (txtZenbat), 9679);
	
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbatAdos), NULL);
	gtk_fixed_put (GTK_FIXED (fixed), botoia, 80, 112);
	gtk_widget_set_size_request (botoia, 88, 40);
	
	botoia = gtk_button_new_with_label ("Utzi");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_fixed_put (GTK_FIXED (fixed), botoia, 80, 168);
	gtk_widget_set_size_request (botoia, 88, 40);

	/* Ados botoia sortu eta sartu */
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_fixed_put (GTK_FIXED (fixedNagusia), botoia, 352, 408);
	gtk_widget_set_size_request (botoia, 118, 38);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmFaltenGestioa);

	gtk_widget_hide(frameZenbat);

	form_load();
}
