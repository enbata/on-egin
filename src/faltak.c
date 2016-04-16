#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "modSarrera.h"
#include "faltatikZenbat.h"

	GtkWidget *fixed;
	GtkWidget *labelaNoiz;
	GtkWidget *labelaZer;
	GtkWidget *lblDatak3, *lblDatak2, *lblDatak4, *lblDatak5, *lblDatak6, *lblDatak7, *lblDatak8, *lblDatak9, *lblDatak1, *lblDatak0;
	GtkWidget *lblTestua0, *lblTestua9, *lblTestua8, *lblTestua5, *lblTestua3, *lblTestua6, *lblTestua4, *lblTestua2, *lblTestua1, *lblTestua7;
	GtkWidget *eventbox0, *eventbox1, *eventbox2, *eventbox3, *eventbox4, *eventbox5, *eventbox6, *eventbox7, *eventbox8, *eventbox9;
	GtkWidget *segiBotoia;
	GtkWidget *labelaTitulua;

void faltakKokatu()
{
	GdkScreen *lehioa = gtk_window_get_screen(GTK_WINDOW(frmFaltak));
	gint BenetakoLuzera = gdk_screen_get_height(lehioa);
	gint BenetakoZabalera = gdk_screen_get_width(lehioa);
	gint Luzera = BenetakoLuzera * 0.9;

	/* Tituluaren labela egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), labelaTitulua, BenetakoZabalera*0.15, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (labelaTitulua, BenetakoZabalera*0.7, BenetakoLuzera*0.1);

	/* Noiz eta Zer labelak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), labelaNoiz, BenetakoZabalera*0.05, BenetakoLuzera*0.2);
	gtk_widget_set_size_request (labelaNoiz, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), labelaZer, BenetakoZabalera*0.5, BenetakoLuzera*0.2);
	gtk_widget_set_size_request (labelaZer, BenetakoZabalera*0.45, BenetakoLuzera*0.05);

	/* Daten labelak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), lblDatak0, BenetakoZabalera*0.05, BenetakoLuzera*0.3);
	gtk_widget_set_size_request (lblDatak0, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak1, BenetakoZabalera*0.05, BenetakoLuzera*0.36);
	gtk_widget_set_size_request (lblDatak1, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak2, BenetakoZabalera*0.05, BenetakoLuzera*0.42);
	gtk_widget_set_size_request (lblDatak2, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak3, BenetakoZabalera*0.05, BenetakoLuzera*0.48);
	gtk_widget_set_size_request (lblDatak3, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak4, BenetakoZabalera*0.05, BenetakoLuzera*0.54);
	gtk_widget_set_size_request (lblDatak4, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak5, BenetakoZabalera*0.05, BenetakoLuzera*0.6);
	gtk_widget_set_size_request (lblDatak5, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak6, BenetakoZabalera*0.05, BenetakoLuzera*0.66);
	gtk_widget_set_size_request (lblDatak6, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak7, BenetakoZabalera*0.05, BenetakoLuzera*0.72);
	gtk_widget_set_size_request (lblDatak7, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak8, BenetakoZabalera*0.05, BenetakoLuzera*0.78);
	gtk_widget_set_size_request (lblDatak8, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblDatak9, BenetakoZabalera*0.05, BenetakoLuzera*0.84);
	gtk_widget_set_size_request (lblDatak9, BenetakoZabalera*0.3, BenetakoLuzera*0.05);

	/* Falten testuen labelak eta euren eventbox -ak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), eventbox0, BenetakoZabalera*0.35, BenetakoLuzera*0.3);
	gtk_widget_set_size_request (eventbox0, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua0, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox1, BenetakoZabalera*0.35, BenetakoLuzera*0.36);
	gtk_widget_set_size_request (eventbox1, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua1, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox2, BenetakoZabalera*0.35, BenetakoLuzera*0.42);
	gtk_widget_set_size_request (eventbox2, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua2, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox3, BenetakoZabalera*0.35, BenetakoLuzera*0.48);
	gtk_widget_set_size_request (eventbox3, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua3, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox4, BenetakoZabalera*0.35, BenetakoLuzera*0.54);
	gtk_widget_set_size_request (eventbox4, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua4, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox5, BenetakoZabalera*0.35, BenetakoLuzera*0.6);
	gtk_widget_set_size_request (eventbox5, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua5, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox6, BenetakoZabalera*0.35, BenetakoLuzera*0.66);
	gtk_widget_set_size_request (eventbox6, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua6, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox7, BenetakoZabalera*0.35, BenetakoLuzera*0.72);
	gtk_widget_set_size_request (eventbox7, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua7, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox8, BenetakoZabalera*0.35, BenetakoLuzera*0.78);
	gtk_widget_set_size_request (eventbox8, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua8, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox9, BenetakoZabalera*0.35, BenetakoLuzera*0.84);
	gtk_widget_set_size_request (eventbox9, BenetakoZabalera*0.6, BenetakoLuzera*0.05);
	gtk_widget_set_size_request (lblTestua9, BenetakoZabalera*0.6, BenetakoLuzera*0.05);

	/* "Segi" botoia egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), segiBotoia, BenetakoZabalera*0.4, BenetakoLuzera*0.92);
	gtk_widget_set_size_request (segiBotoia, BenetakoZabalera*0.2, BenetakoLuzera*0.07);
}

void DatakErakutsi(char i[1], char data1[10], char data2[10])
{
	char data[50];
	sprintf(data, "<span size='large'>%s -tik %s -ra</span>", data1, data2);
	gchar *text;
	PangoAttrList *attrs;
	pango_parse_markup (data, -1, 0, &attrs, &text, NULL, NULL);
	switch (i[0])
	{
		case '0': gtk_label_set_text(GTK_LABEL(lblDatak0), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak0), attrs);
			  gtk_widget_show(lblDatak0);
			  break;
		case '1': gtk_label_set_text(GTK_LABEL(lblDatak1), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak1), attrs);
			  gtk_widget_show(lblDatak1);
			  break;
		case '2': gtk_label_set_text(GTK_LABEL(lblDatak2), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak2), attrs);
			  gtk_widget_show(lblDatak2);
			  break;
		case '3': gtk_label_set_text(GTK_LABEL(lblDatak3), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak3), attrs);
			  gtk_widget_show(lblDatak3);
			  break;
		case '4': gtk_label_set_text(GTK_LABEL(lblDatak4), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak4), attrs);
			  gtk_widget_show(lblDatak4);
			  break;
		case '5': gtk_label_set_text(GTK_LABEL(lblDatak5), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak5), attrs);
			  gtk_widget_show(lblDatak5);
			  break;
		case '6': gtk_label_set_text(GTK_LABEL(lblDatak6), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak6), attrs);
			  gtk_widget_show(lblDatak6);
			  break;
		case '7': gtk_label_set_text(GTK_LABEL(lblDatak7), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak7), attrs);
			  gtk_widget_show(lblDatak7);
			  break;
		case '8': gtk_label_set_text(GTK_LABEL(lblDatak8), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak8), attrs);
			  gtk_widget_show(lblDatak8);
			  break;
		case '9': gtk_label_set_text(GTK_LABEL(lblDatak9), text);
			  gtk_label_set_attributes(GTK_LABEL(lblDatak9), attrs);
			  gtk_widget_show(lblDatak9);
			  break;
		default: break;
	}
}

void TestuakErakutsi(char i[1], char kopurua[5], char izena[20])
{
	char testua[50];
	sprintf(testua, "<span size='xx-large'>%d\t%s</span>", abs(atoi(kopurua)), izena);
	gchar *text;
	PangoAttrList *attrs;
	pango_parse_markup (testua, -1, 0, &attrs, &text, NULL, NULL);
	switch (i[0])
	{
		case '0': gtk_widget_show(eventbox0);
			  gtk_label_set_text(GTK_LABEL(lblTestua0), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua0), attrs);
			  gtk_widget_show(lblTestua0);
			  break;
		case '1': gtk_widget_show(eventbox1);
			  gtk_label_set_text(GTK_LABEL(lblTestua1), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua1), attrs);
			  gtk_widget_show(lblTestua1);
			  break;
		case '2': gtk_widget_show(eventbox2);
			  gtk_label_set_text(GTK_LABEL(lblTestua2), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua2), attrs);
			  gtk_widget_show(lblTestua2);
			  break;
		case '3': gtk_widget_show(eventbox3);
			  gtk_label_set_text(GTK_LABEL(lblTestua3), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua3), attrs);
			  gtk_widget_show(lblTestua3);
			  break;
		case '4': gtk_widget_show(eventbox4);
			  gtk_label_set_text(GTK_LABEL(lblTestua4), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua4), attrs);
			  gtk_widget_show(lblTestua4);
			  break;
		case '5': gtk_widget_show(eventbox5);
			  gtk_label_set_text(GTK_LABEL(lblTestua5), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua5), attrs);
			  gtk_widget_show(lblTestua5);
			  break;
		case '6': gtk_widget_show(eventbox6);
			  gtk_label_set_text(GTK_LABEL(lblTestua6), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua6), attrs);
			  gtk_widget_show(lblTestua6);
			  break;
		case '7': gtk_widget_show(eventbox7);
			  gtk_label_set_text(GTK_LABEL(lblTestua7), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua7), attrs);
			  gtk_widget_show(lblTestua7);
			  break;
		case '8': gtk_widget_show(eventbox8);
			  gtk_label_set_text(GTK_LABEL(lblTestua8), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua8), attrs);
			  gtk_widget_show(lblTestua8);
			  break;
		case '9': gtk_widget_show(eventbox9);
			  gtk_label_set_text(GTK_LABEL(lblTestua9), text);
			  gtk_label_set_attributes(GTK_LABEL(lblTestua9), attrs);
			  gtk_widget_show(lblTestua9);
			  break;
		default: break;
	}
}

void faltakErakutsi()
{
	int i=0;
	MYSQL_ROW row;
	mysql_data_seek (rstDatuak, 0);
	while (((row=mysql_fetch_row(rstDatuak))!=NULL) && i<10)
	{
		char pos[1];
		sprintf(pos, "%d", i);
		DatakErakutsi(pos, row[3], row[4]);
		TestuakErakutsi(pos, row[2], row[6]);
		i++;
	}
}

void form_load()
{
	/* Formularioaren itxura uneko resoluziora egokitu */
	faltakKokatu();
	/* Dauden faltak pantailan erakutsi */
	faltakErakutsi();
	faltaKop=0;
}

static void btmSegi()
{
	// Bufferrean inprimatzeko datuak badaude hauek inprimatu (FaltenKontuaInprimatu)
	if (faltenBufferra[0].kopurua!=0)
		faltenKontuaInprimatu();
	gtk_widget_destroy(frmFaltak);
	gtk_main_quit();
}

void DatuakIzkutatu()
{
	gtk_widget_hide(lblDatak0);
	gtk_widget_hide(eventbox0);
	gtk_widget_hide(lblDatak1);
	gtk_widget_hide(eventbox1);
	gtk_widget_hide(lblDatak2);
	gtk_widget_hide(eventbox2);
	gtk_widget_hide(lblDatak3);
	gtk_widget_hide(eventbox3);
	gtk_widget_hide(lblDatak4);
	gtk_widget_hide(eventbox4);
	gtk_widget_hide(lblDatak5);
	gtk_widget_hide(eventbox5);
	gtk_widget_hide(lblDatak6);
	gtk_widget_hide(eventbox6);
	gtk_widget_hide(lblDatak7);
	gtk_widget_hide(eventbox7);
	gtk_widget_hide(lblDatak8);
	gtk_widget_hide(eventbox8);
	gtk_widget_hide(lblDatak9);
	gtk_widget_hide(eventbox9);
}

static void btmEventBox(GtkWidget *widget, GdkEventButton *event,
				    gpointer data)
{
	char testua[50];
	char zenbakia[5];
	char izena[20];
	sprintf(testua, "%s", gtk_label_get_text(data));
	testua[strlen(testua)+1]='\n';
	int i=0;
	sprintf(zenbakia, "abcd");
	while (testua[i]!='\t')
	{
		zenbakia[i]=testua[i];
		i++;
	}
	i++;
	int k=0;
	while(testua[i]!='\n')
	{
		izena[k]=testua[i];
		i++;
		k++;
	}

	faltatikZenbat(atoi(zenbakia), izena);

	/* Lehioa freskatu, datuak berriz egoki ikusteko */
	DatuakIzkutatu();

	/* Oraindik beste faltarik ba al dago? */
	mysql_free_result(rstDatuak);
	char sql[500];
	MYSQL_ROW row;

	//Faltak kargatu, ea bazkide hori egon den egunetan faltarik dagoen ikusteko
	sprintf(sql, "SELECT DISTINCT Faltak.FKodea,Faltak.gkodea,Faltak.GKopurua,Faltak.DAurrekoa,Faltak.DAzkena,Gaiak.GPrezioa,Gaiak.Gizenaeus FROM Faltak,Gaiak,Kontuak WHERE Kontuak.BKodea = %d AND Faltak.GKopurua < 0 AND Faltak.DAurrekoa <= Kontuak.Data AND Kontuak.Data <= Faltak.DAzkena AND Faltak.Gkodea = Gaiak.Gkodea AND Kontuak.KMota = 'KONTUA' ORDER BY Faltak.Daurrekoa,Gaiak.Gizenaeus", unekoBazkidea);
	mysql_query(dbElkartea, sql);
	rstDatuak = mysql_store_result(dbElkartea);
	if ((row=mysql_fetch_row(rstDatuak))!=NULL)
	{
		faltakErakutsi();
	}
	else
	{
		// Bufferrean gordetzen joan garen falten datuak inprimatu (FaltenKontuaInprimatu)
		faltenKontuaInprimatu();
		gtk_main_quit();
		gtk_widget_destroy(frmFaltak);
	}
}

void faltak()
{
	GtkWidget *labela;
	GdkColor kolorea;
	gchar *text;
	gchar *testua;
	PangoAttrList *attrs;
	
	/* Lehio definitu eta konfiguratu */
	frmFaltak = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW (frmFaltak), FALSE);
	gtk_window_fullscreen(GTK_WINDOW(frmFaltak));
	gdk_color_parse("#000051", &kolorea);
	gtk_widget_modify_bg(frmFaltak, GTK_STATE_NORMAL, &kolorea);
	
	/* Lehioko elementuak ezartzeko egitura sortu */
	fixed = gtk_fixed_new ();
	gtk_widget_show (fixed);
	gtk_container_add (GTK_CONTAINER (frmFaltak), fixed);
	
	/* Lehioko elementuak sortu eta sartu */
	gdk_color_parse("#4c66ee", &kolorea);
	testua = "<span size='xx-large'> NOIZ </span>";
	pango_parse_markup (testua, -1, 0, &attrs, &text, NULL, NULL);
	labelaNoiz = gtk_label_new (text);
	gtk_label_set_attributes(GTK_LABEL(labelaNoiz), attrs);
	gtk_widget_show (labelaNoiz);
	gtk_fixed_put (GTK_FIXED (fixed), labelaNoiz, 64, 128);
	gtk_widget_set_size_request (labelaNoiz, 112, 40);
	gtk_widget_modify_fg(labelaNoiz, GTK_STATE_NORMAL, &kolorea);
	
		gdk_color_parse("#ffffff", &kolorea);
		/* Datak ipintzeko 10 labelak sartu */
		lblDatak2 = gtk_label_new ("Datak3");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak2, 80, 312);
		gtk_widget_set_size_request (lblDatak2, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak2), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak2, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak1 = gtk_label_new ("Datak2");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak1, 80, 248);
		gtk_widget_set_size_request (lblDatak1, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak1), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak1, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak3 = gtk_label_new ("Datak4");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak3, 80, 376);
		gtk_widget_set_size_request (lblDatak3, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak3), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak3, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak4 = gtk_label_new ("Datak5");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak4, 80, 440);
		gtk_widget_set_size_request (lblDatak4, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak4), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak4, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak5 = gtk_label_new ("Datak6");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak5, 80, 504);
		gtk_widget_set_size_request (lblDatak5, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak5), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak5, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak6 = gtk_label_new ("Datak7");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak6, 80, 568);
		gtk_widget_set_size_request (lblDatak6, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak6), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak6, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak7 = gtk_label_new ("Datak8");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak7, 80, 640);
		gtk_widget_set_size_request (lblDatak7, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak7), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak7, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak8 = gtk_label_new ("Datak9");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak8, 80, 720);
		gtk_widget_set_size_request (lblDatak8, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak8), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak8, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak0 = gtk_label_new ("Datak1");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak0, 80, 184);
		gtk_widget_set_size_request (lblDatak0, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak0), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak0, GTK_STATE_NORMAL, &kolorea);
		
		lblDatak9 = gtk_label_new ("Datak10");
		gtk_fixed_put (GTK_FIXED (fixed), lblDatak9, 80, 792);
		gtk_widget_set_size_request (lblDatak9, 280, 56);
		gtk_label_set_ellipsize(GTK_LABEL(lblDatak9), PANGO_ELLIPSIZE_START);
		gtk_widget_modify_fg(lblDatak9, GTK_STATE_NORMAL, &kolorea);

	gdk_color_parse("#4c66ee", &kolorea);
	testua = "<span size='xx-large'> ZER </span>";
	pango_parse_markup (testua, -1, 0, &attrs, &text, NULL, NULL);
	labelaZer = gtk_label_new (text);
	gtk_label_set_attributes(GTK_LABEL(labelaZer), attrs);
	gtk_widget_show (labelaZer);
	gtk_fixed_put (GTK_FIXED (fixed), labelaZer, 440, 128);
	gtk_widget_set_size_request (labelaZer, 128, 32);
	gtk_widget_modify_fg(labelaZer, GTK_STATE_NORMAL, &kolorea);

		gdk_color_parse("#a9bbdb", &kolorea);
		/* Faltaren azalpena idazteko labelak sartu */
		eventbox0 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox0, 400, 184);
		gtk_widget_set_size_request (eventbox0, 720, 48);
		gtk_widget_modify_bg(eventbox0, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua0 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox0), lblTestua0);
		gtk_widget_set_size_request (lblTestua0, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua0), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox0), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua0);
		
		eventbox9 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox9, 400, 760);
		gtk_widget_set_size_request (eventbox9, 720, 48);
		gtk_widget_modify_bg(eventbox9, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua9 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox9), lblTestua9);
		gtk_widget_set_size_request (lblTestua9, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua9), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox9), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua9);
		
		eventbox8 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox8, 400, 696);
		gtk_widget_set_size_request (eventbox8, 720, 48);
		gtk_widget_modify_bg(eventbox8, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua8 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox8), lblTestua8);
		gtk_widget_set_size_request (lblTestua8, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua8), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox8), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua8);
		
		eventbox5 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox5, 400, 504);
		gtk_widget_set_size_request (eventbox5, 720, 48);
		gtk_widget_modify_bg(eventbox5, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua5 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox5), lblTestua5);
		gtk_widget_set_size_request (lblTestua5, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua5), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox5), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua5);
		
		eventbox3 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox3, 400, 376);
		gtk_widget_set_size_request (eventbox3, 720, 48);
		gtk_widget_modify_bg(eventbox3, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua3 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox3), lblTestua3);
		gtk_widget_set_size_request (lblTestua3, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua3), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox3), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua3);
		
		eventbox6 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox6, 400, 568);
		gtk_widget_set_size_request (eventbox6, 720, 48);
		gtk_widget_modify_bg(eventbox6, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua6 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox6), lblTestua6);
		gtk_widget_set_size_request (lblTestua6, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua6), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox6), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua6);
		
		eventbox4 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox4, 400, 440);
		gtk_widget_set_size_request (eventbox4, 720, 48);
		gtk_widget_modify_bg(eventbox4, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua4 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox4), lblTestua4);
		gtk_widget_set_size_request (lblTestua4, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua4), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox4), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua4);
		
		eventbox2 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox2, 400, 312);
		gtk_widget_set_size_request (eventbox2, 720, 48);
		gtk_widget_modify_bg(eventbox2, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua2 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox2), lblTestua2);
		gtk_widget_set_size_request (lblTestua2, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua2), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox2), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua2);
		
		eventbox1 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox1, 400, 248);
		gtk_widget_set_size_request (eventbox1, 720, 48);
		gtk_widget_modify_bg(eventbox1, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua1 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox1), lblTestua1);
		gtk_widget_set_size_request (lblTestua1, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua1), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox1), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua1);
		
		eventbox7 = gtk_event_box_new ();
		gtk_fixed_put (GTK_FIXED (fixed), eventbox7, 400, 632);
		gtk_widget_set_size_request (eventbox7, 720, 48);
		gtk_widget_modify_bg(eventbox7, GTK_STATE_NORMAL, &kolorea);
		
		lblTestua7 = gtk_label_new ("Testua");
		gtk_container_add (GTK_CONTAINER (eventbox7), lblTestua7);
		gtk_widget_set_size_request (lblTestua7, 720, 48);
		gtk_label_set_ellipsize(GTK_LABEL(lblTestua7), PANGO_ELLIPSIZE_START);
		g_signal_connect(G_OBJECT(eventbox7), "button_press_event",
				G_CALLBACK(btmEventBox), (gpointer) lblTestua7);
	
	/* Formularioa uzteko botoia sortu eta sartu */
	testua = "<span size='xx-large'> Segi </span>";
	pango_parse_markup (testua, -1, 0, &attrs, &text, NULL, NULL);
	labela = gtk_label_new (text);
	gtk_label_set_attributes(GTK_LABEL(labela), attrs);
	segiBotoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(segiBotoia), labela);
	g_signal_connect(G_OBJECT(segiBotoia), "clicked",
			G_CALLBACK(btmSegi), NULL);
	gtk_widget_show (segiBotoia);
	gtk_widget_show (labela);
	gtk_fixed_put (GTK_FIXED (fixed), segiBotoia, 1200, 712);
	gtk_widget_set_size_request (segiBotoia, 136, 104);
	
	gdk_color_parse("#ffff00", &kolorea);
	testua = "<span size='xx-large'>Elkartean izan zaren egunetan falta hauek aurkitu dira: \nOnartzeko, sakatu gainean.</span>";
	pango_parse_markup (testua, -1, 0, &attrs, &text, NULL, NULL);
	labelaTitulua = gtk_label_new (text);
	gtk_label_set_attributes(GTK_LABEL(labelaTitulua), attrs);
	gtk_widget_modify_fg(labelaTitulua, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_show (labelaTitulua);
	gtk_fixed_put (GTK_FIXED (fixed), labelaTitulua, 136, 24);
	gtk_widget_set_size_request (labelaTitulua, 1120, 72);
	gtk_label_set_justify (GTK_LABEL (labelaTitulua), GTK_JUSTIFY_CENTER);
	gtk_misc_set_alignment (GTK_MISC (labelaTitulua), 0.51, 0.52);
	
	form_load();

	/* lehioa bistaratu eta martxan jarri */
	gtk_widget_show(frmFaltak);

	gtk_main();

}
