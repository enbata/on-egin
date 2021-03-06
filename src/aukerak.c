#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "modSarrera.h"
#include "kontua.h"
#include "galdera.h"
#define true 1
#define false 0

	GtkWidget *fixed;
	GtkWidget *eventboxA0, *eventboxA1, *eventboxA2, *eventboxA3, *eventboxA4, *eventboxA5, *eventboxA6, *eventboxA7, *eventboxA8, *eventboxA9;
	GtkWidget *lblAukerak0, *lblAukerak6, *lblAukerak5, *lblAukerak4, *lblAukerak3, *lblAukerak2, *lblAukerak1, *lblAukerak7, *lblAukerak8, *lblAukerak9;
	GtkWidget *eventbox0, *eventbox1, *eventbox2, *eventbox3, *eventbox4, *eventbox5, *eventbox6, *eventbox7, *eventbox8, *eventbox9, *eventbox10, *eventbox11, *eventbox12, *eventbox13, *eventbox14, *eventbox15, *eventbox16, *eventbox17, *eventbox18, *eventbox19;
	GtkWidget *lblGaiak9, *lblGaiak16, *lblGaiak11, *lblGaiak7, *lblGaiak3, *lblGaiak1, *lblGaiak5, *lblGaiak8, *lblGaiak13, *lblGaiak17, *lblGaiak18, *lblGaiak14, *lblGaiak12, *lblGaiak10, *lblGaiak6, *lblGaiak0, *lblGaiak4, *lblGaiak2, *lblGaiak19, *lblGaiak15;
	GtkWidget *eventboxP0, *eventboxP1, *eventboxP2, *eventboxP3, *eventboxP4, *eventboxP5, *eventboxP6, *eventboxP7, *eventboxP8, *eventboxP9, *eventboxP10, *eventboxP11, *eventboxP12, *eventboxP13, *eventboxP14, *eventboxP15, *eventboxP16, *eventboxP17, *eventboxP18, *eventboxP19;
	GtkWidget *lblPrezioa16, *lblPrezioa17, *lblPrezioa12, *lblPrezioa13, *lblPrezioa8, *lblPrezioa4, *lblPrezioa5, *lblPrezioa1, *lblPrezioa0, *lblPrezioa2, *lblPrezioa3, *lblPrezioa6, *lblPrezioa7, *lblPrezioa9, *lblPrezioa10, *lblPrezioa11, *lblPrezioa14, *lblPrezioa15, *lblPrezioa18, *lblPrezioa19;
	GtkWidget *eventboxK0, *eventboxK1, *eventboxK2, *eventboxK3, *eventboxK4, *eventboxK5, *eventboxK6, *eventboxK7, *eventboxK8, *eventboxK9, *eventboxK10, *eventboxK11, *eventboxK12, *eventboxK13, *eventboxK14, *eventboxK15, *eventboxK16, *eventboxK17, *eventboxK18, *eventboxK19;
	GtkWidget *lblKopuruak16, *lblKopuruak17, *lblKopuruak12, *lblKopuruak13, *lblKopuruak8, *lblKopuruak4, *lblKopuruak5, *lblKopuruak0, *lblKopuruak1, *lblKopuruak2, *lblKopuruak3, *lblKopuruak6, *lblKopuruak7, *lblKopuruak10, *lblKopuruak11, *lblKopuruak14, *lblKopuruak15, *lblKopuruak18, *lblKopuruak19, *lblKopuruak9;
	GtkWidget *vseparator1, *hseparator1;
	GtkWidget *eventboxAukerakoak, *eventboxAKopuruak, *eventboxAGuztira, *eventboxGuztira, *eventboxKGuztira;
	GtkWidget *lblAukerakoak, *lblAKopuruak, *lblAGuztira, *lblGuztira, *lblKGuztira;
	GtkWidget *frameKalkulagailua;
	GtkWidget *txtKopurua;
	GtkWidget *cmdZenbakia0, *cmdZenbakia1, *cmdZenbakia2, *cmdZenbakia3, *cmdZenbakia4, *cmdZenbakia5, *cmdZenbakia6, *cmdZenbakia7, *cmdZenbakia8, *cmdZenbakia9, *cmdZenbakia10, *cmdZenbakia11, *cmdZenbakia12;
	GtkWidget *eventboxKontuaEgin, *eventboxKontuaUtzi, *lblIzena;
	GtkWidget *eventboxGAtalean, *eventboxLabel1;
	GtkWidget *lblGAtalean, *label1;
	GtkWidget *lblKontuaEgin;

int unekoAukera;
int unekoGaia;
int aukeraKop;
int gaikop;
int bazkideKop=0;
int ezBazkideKop=0;

void aukerakErakutsi(char i[5], char d[100])
{
	char datua[100];
	sprintf(datua, "<span size='xx-large'><b>%s</b></span>", d);
	switch(i[0])
	{
		case '0': gtk_label_set_text(GTK_LABEL(lblAukerak0), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak0), TRUE);
			  gtk_widget_show_all(eventboxA0);
			  break;
		case '1': gtk_label_set_text(GTK_LABEL(lblAukerak1), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak1), TRUE);
			  gtk_widget_show_all(eventboxA1);
			  break;
		case '2': gtk_label_set_text(GTK_LABEL(lblAukerak2), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak2), TRUE);
			  gtk_widget_show_all(eventboxA2);
			  break;
		case '3': gtk_label_set_text(GTK_LABEL(lblAukerak3), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak3), TRUE);
			  gtk_widget_show_all(eventboxA3);
			  break;
		case '4': gtk_label_set_text(GTK_LABEL(lblAukerak4), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak4), TRUE);
			  gtk_widget_show_all(eventboxA4);
			  break;
		case '5': gtk_label_set_text(GTK_LABEL(lblAukerak5), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak5), TRUE);
			  gtk_widget_show_all(eventboxA5);
			  break;
		case '6': gtk_label_set_text(GTK_LABEL(lblAukerak6), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak6), TRUE);
			  gtk_widget_show_all(eventboxA6);
			  break;
		case '7': gtk_label_set_text(GTK_LABEL(lblAukerak7), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak7), TRUE);
			  gtk_widget_show_all(eventboxA7);
			  break;
		case '8': gtk_label_set_text(GTK_LABEL(lblAukerak8), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak8), TRUE);
			  gtk_widget_show_all(eventboxA8);
			  break;
		case '9': gtk_label_set_text(GTK_LABEL(lblAukerak9), datua);
			  gtk_label_set_use_markup(GTK_LABEL(lblAukerak9), TRUE);
			  gtk_widget_show_all(eventboxA9);
			  break;
		default:  break;
	}
}

void gaiaKokatu(int i)
{
	char a[5];
	char p[50];
	char k[50];
	char izena[150];
	sprintf(a, "%d", i);

	gaia *lag;
	lag=arrGaiak[unekoAukera];

	sprintf(p, "<span size='x-large'>%.2f</span>", lag[i].Prezioa);
	sprintf(k, "<span size='x-large'>%d</span>", lag[i].Zenbat);
	sprintf(izena, "<span size='x-large'>%s</span>", lag[i].Izena);

	switch (a[0])
	{
		case '0': gtk_label_set_text(GTK_LABEL(lblGaiak0), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa0), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak0), k);
			  gtk_widget_show_all(eventbox0);
			  gtk_widget_show_all(eventboxP0);
			  gtk_widget_show_all(eventboxK0);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak0), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa0), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak0), TRUE);
			  break;
		case '1': gtk_label_set_text(GTK_LABEL(lblGaiak1), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa1), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak1), k);
			  gtk_widget_show_all(eventbox1);
			  gtk_widget_show_all(eventboxP1);
			  gtk_widget_show_all(eventboxK1);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak1), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa1), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak1), TRUE);
			  break;
		case '2': gtk_label_set_text(GTK_LABEL(lblGaiak2), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa2), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak2), k);
			  gtk_widget_show_all(eventbox2);
			  gtk_widget_show_all(eventboxP2);
			  gtk_widget_show_all(eventboxK2);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak2), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa2), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak2), TRUE);
			  break;
		case '3': gtk_label_set_text(GTK_LABEL(lblGaiak3), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa3), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak3), k);
			  gtk_widget_show_all(eventbox3);
			  gtk_widget_show_all(eventboxP3);
			  gtk_widget_show_all(eventboxK3);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak3), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa3), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak3), TRUE);
			  break;
		case '4': gtk_label_set_text(GTK_LABEL(lblGaiak4), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa4), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak4), k);
			  gtk_widget_show_all(eventbox4);
			  gtk_widget_show_all(eventboxP4);
			  gtk_widget_show_all(eventboxK4);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak4), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa4), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak4), TRUE);
			  break;
		case '5': gtk_label_set_text(GTK_LABEL(lblGaiak5), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa5), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak5), k);
			  gtk_widget_show_all(eventbox5);
			  gtk_widget_show_all(eventboxP5);
			  gtk_widget_show_all(eventboxK5);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak5), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa5), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak5), TRUE);
			  break;
		case '6': gtk_label_set_text(GTK_LABEL(lblGaiak6), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa6), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak6), k);
			  gtk_widget_show_all(eventbox6);
			  gtk_widget_show_all(eventboxP6);
			  gtk_widget_show_all(eventboxK6);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak6), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa6), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak6), TRUE);
			  break;
		case '7': gtk_label_set_text(GTK_LABEL(lblGaiak7), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa7), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak7), k);
			  gtk_widget_show_all(eventbox7);
			  gtk_widget_show_all(eventboxP7);
			  gtk_widget_show_all(eventboxK7);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak7), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa7), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak7), TRUE);
			  break;
		case '8': gtk_label_set_text(GTK_LABEL(lblGaiak8), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa8), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak8), k);
			  gtk_widget_show_all(eventbox8);
			  gtk_widget_show_all(eventboxP8);
			  gtk_widget_show_all(eventboxK8);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak8), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa8), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak8), TRUE);
			  break;
		case '9': gtk_label_set_text(GTK_LABEL(lblGaiak9), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa9), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak9), k);
			  gtk_widget_show_all(eventbox9);
			  gtk_widget_show_all(eventboxP9);
			  gtk_widget_show_all(eventboxK9);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak9), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa9), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak9), TRUE);
			  break;
	}
}

void gaiaKokatu2(int i)
{
	char a[5];
	char p[50];
	char k[50];
	char izena[150];
	sprintf(a, "%d", i-10);

	gaia *lag;
	lag=arrGaiak[unekoAukera];

	sprintf(p, "<span size='x-large'>%.2f</span>", lag[i].Prezioa);
	sprintf(k, "<span size='x-large'>%d</span>", lag[i].Zenbat);
	sprintf(izena, "<span size='x-large'>%s</span>", lag[i].Izena);

	switch (a[0])
	{
		case '0': gtk_label_set_text(GTK_LABEL(lblGaiak10), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa10), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak10), k);
			  gtk_widget_show_all(eventbox10);
			  gtk_widget_show_all(eventboxP10);
			  gtk_widget_show_all(eventboxK10);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak10), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa10), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak10), TRUE);
			  break;
		case '1': gtk_label_set_text(GTK_LABEL(lblGaiak11), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa11), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak11), k);
			  gtk_widget_show_all(eventbox11);
			  gtk_widget_show_all(eventboxP11);
			  gtk_widget_show_all(eventboxK11);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak11), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa11), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak11), TRUE);
			  break;
		case '2': gtk_label_set_text(GTK_LABEL(lblGaiak12), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa12), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak12), k);
			  gtk_widget_show_all(eventbox12);
			  gtk_widget_show_all(eventboxP12);
			  gtk_widget_show_all(eventboxK12);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak12), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa12), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak12), TRUE);
			  break;
		case '3': gtk_label_set_text(GTK_LABEL(lblGaiak13), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa13), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak13), k);
			  gtk_widget_show_all(eventbox13);
			  gtk_widget_show_all(eventboxP13);
			  gtk_widget_show_all(eventboxK13);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak13), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa13), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak13), TRUE);
			  break;
		case '4': gtk_label_set_text(GTK_LABEL(lblGaiak14), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa14), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak14), k);
			  gtk_widget_show_all(eventbox14);
			  gtk_widget_show_all(eventboxP14);
			  gtk_widget_show_all(eventboxK14);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak14), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa14), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak14), TRUE);
			  break;
		case '5': gtk_label_set_text(GTK_LABEL(lblGaiak15), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa15), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak15), k);
			  gtk_widget_show_all(eventbox15);
			  gtk_widget_show_all(eventboxP15);
			  gtk_widget_show_all(eventboxK15);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak15), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa15), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak15), TRUE);
			  break;
		case '6': gtk_label_set_text(GTK_LABEL(lblGaiak16), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa16), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak16), k);
			  gtk_widget_show_all(eventbox16);
			  gtk_widget_show_all(eventboxP16);
			  gtk_widget_show_all(eventboxK16);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak16), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa16), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak16), TRUE);
			  break;
		case '7': gtk_label_set_text(GTK_LABEL(lblGaiak17), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa17), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak17), k);
			  gtk_widget_show_all(eventbox17);
			  gtk_widget_show_all(eventboxP17);
			  gtk_widget_show_all(eventboxK17);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak17), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa17), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak17), TRUE);
			  break;
		case '8': gtk_label_set_text(GTK_LABEL(lblGaiak18), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa18), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak18), k);
			  gtk_widget_show_all(eventbox18);
			  gtk_widget_show_all(eventboxP18);
			  gtk_widget_show_all(eventboxK18);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak18), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa18), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak18), TRUE);
			  break;
		case '9': gtk_label_set_text(GTK_LABEL(lblGaiak19), izena);
			  gtk_label_set_text(GTK_LABEL(lblPrezioa19), p);
			  gtk_label_set_text(GTK_LABEL(lblKopuruak19), k);
			  gtk_widget_show_all(eventbox19);
			  gtk_widget_show_all(eventboxP19);
			  gtk_widget_show_all(eventboxK19);
			  gtk_label_set_use_markup(GTK_LABEL(lblGaiak19), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblPrezioa19), TRUE);
			  gtk_label_set_use_markup(GTK_LABEL(lblKopuruak19), TRUE);
			  break;
	}
}

void gaiakErakutsi()
{
	char sql[200];
	MYSQL_ROW row;

	/* Uneko aukeraren gai kopurua lortu */
	mysql_data_seek(rstAukerak, unekoAukera);
	row=mysql_fetch_row(rstAukerak);
	sprintf(sql, "SELECT count(*) from Gaiak, Elkartea where Elkartea.Gaikodea = Gaiak.GKodea AND AKodea =%d and Gaiak.erabilgarri", atoi(row[2]));
	mysql_query(dbElkartea, sql);
	rstGaiak = mysql_store_result(dbElkartea);
	if (row=mysql_fetch_row(rstGaiak))
		gaikop=atoi(row[0]);
	else
		gaikop=0;

	mysql_free_result(rstGaiak);

	/* Aukeraren gaiak erakutsi */
	int i;
	for (i=0; i<gaikop; i++)
	{
		if (i<10)
			gaiaKokatu(i);
		else
			gaiaKokatu2(i);
	}
}

void aukerakKokatu()
{
	GdkScreen *lehioa = gtk_window_get_screen(GTK_WINDOW(frmAukerak));
	gint BenetakoLuzera = gdk_screen_get_height(lehioa);
	gint BenetakoZabalera = gdk_screen_get_width(lehioa);

	/* Aukeren labelak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), eventboxA0, BenetakoZabalera*0.01, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (eventboxA0, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA1, BenetakoZabalera*0.01, BenetakoLuzera*0.1);
	gtk_widget_set_size_request (eventboxA1, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA2, BenetakoZabalera*0.01, BenetakoLuzera*0.18);
	gtk_widget_set_size_request (eventboxA2, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA3, BenetakoZabalera*0.01, BenetakoLuzera*0.26);
	gtk_widget_set_size_request (eventboxA3, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA4, BenetakoZabalera*0.01, BenetakoLuzera*0.34);
	gtk_widget_set_size_request (eventboxA4, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA5, BenetakoZabalera*0.01, BenetakoLuzera*0.42);
	gtk_widget_set_size_request (eventboxA5, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA6, BenetakoZabalera*0.01, BenetakoLuzera*0.5);
	gtk_widget_set_size_request (eventboxA6, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA7, BenetakoZabalera*0.01, BenetakoLuzera*0.58);
	gtk_widget_set_size_request (eventboxA7, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA8, BenetakoZabalera*0.01, BenetakoLuzera*0.66);
	gtk_widget_set_size_request (eventboxA8, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxA9, BenetakoZabalera*0.01, BenetakoLuzera*0.74);
	gtk_widget_set_size_request (eventboxA9, BenetakoZabalera*0.18, BenetakoLuzera*0.07);

	/* Gaien labelak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), eventbox0, BenetakoZabalera*0.22, BenetakoLuzera*0.34);
	gtk_widget_set_size_request (eventbox0, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP0, BenetakoZabalera*0.41, BenetakoLuzera*0.34);
		gtk_widget_set_size_request (eventboxP0, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK0, BenetakoZabalera*0.41, BenetakoLuzera*0.376);
		gtk_widget_set_size_request (eventboxK0, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox1, BenetakoZabalera*0.48, BenetakoLuzera*0.34);
	gtk_widget_set_size_request (eventbox1, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP1, BenetakoZabalera*0.67, BenetakoLuzera*0.34);
		gtk_widget_set_size_request (eventboxP1, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK1, BenetakoZabalera*0.67, BenetakoLuzera*0.376);
		gtk_widget_set_size_request (eventboxK1, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox2, BenetakoZabalera*0.22, BenetakoLuzera*0.42);
	gtk_widget_set_size_request (eventbox2, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP2, BenetakoZabalera*0.41, BenetakoLuzera*0.42);
		gtk_widget_set_size_request (eventboxP2, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK2, BenetakoZabalera*0.41, BenetakoLuzera*0.456);
		gtk_widget_set_size_request (eventboxK2, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox3, BenetakoZabalera*0.48, BenetakoLuzera*0.42);
	gtk_widget_set_size_request (eventbox3, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP3, BenetakoZabalera*0.67, BenetakoLuzera*0.42);
		gtk_widget_set_size_request (eventboxP3, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK3, BenetakoZabalera*0.67, BenetakoLuzera*0.456);
		gtk_widget_set_size_request (eventboxK3, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox4, BenetakoZabalera*0.22, BenetakoLuzera*0.26);
	gtk_widget_set_size_request (eventbox4, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP4, BenetakoZabalera*0.41, BenetakoLuzera*0.26);
		gtk_widget_set_size_request (eventboxP4, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK4, BenetakoZabalera*0.41, BenetakoLuzera*0.296);
		gtk_widget_set_size_request (eventboxK4, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox5, BenetakoZabalera*0.48, BenetakoLuzera*0.26);
	gtk_widget_set_size_request (eventbox5, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP5, BenetakoZabalera*0.67, BenetakoLuzera*0.26);
		gtk_widget_set_size_request (eventboxP5, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK5, BenetakoZabalera*0.67, BenetakoLuzera*0.296);
		gtk_widget_set_size_request (eventboxK5, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox6, BenetakoZabalera*0.22, BenetakoLuzera*0.5);
	gtk_widget_set_size_request (eventbox6, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP6, BenetakoZabalera*0.41, BenetakoLuzera*0.5);
		gtk_widget_set_size_request (eventboxP6, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK6, BenetakoZabalera*0.41, BenetakoLuzera*0.536);
		gtk_widget_set_size_request (eventboxK6, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox7, BenetakoZabalera*0.48, BenetakoLuzera*0.5);
	gtk_widget_set_size_request (eventbox7, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP7, BenetakoZabalera*0.67, BenetakoLuzera*0.5);
		gtk_widget_set_size_request (eventboxP7, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK7, BenetakoZabalera*0.67, BenetakoLuzera*0.536);
		gtk_widget_set_size_request (eventboxK7, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox8, BenetakoZabalera*0.22, BenetakoLuzera*0.18);
	gtk_widget_set_size_request (eventbox8, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP8, BenetakoZabalera*0.41, BenetakoLuzera*0.18);
		gtk_widget_set_size_request (eventboxP8, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK8, BenetakoZabalera*0.41, BenetakoLuzera*0.216);
		gtk_widget_set_size_request (eventboxK8, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox9, BenetakoZabalera*0.48, BenetakoLuzera*0.18);
	gtk_widget_set_size_request (eventbox9, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP9, BenetakoZabalera*0.67, BenetakoLuzera*0.18);
		gtk_widget_set_size_request (eventboxP9, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK9, BenetakoZabalera*0.67, BenetakoLuzera*0.216);
		gtk_widget_set_size_request (eventboxK9, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox10, BenetakoZabalera*0.22, BenetakoLuzera*0.58);
	gtk_widget_set_size_request (eventbox10, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP10, BenetakoZabalera*0.41, BenetakoLuzera*0.58);
		gtk_widget_set_size_request (eventboxP10, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK10, BenetakoZabalera*0.41, BenetakoLuzera*0.616);
		gtk_widget_set_size_request (eventboxK10, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox11, BenetakoZabalera*0.48, BenetakoLuzera*0.58);
	gtk_widget_set_size_request (eventbox11, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP11, BenetakoZabalera*0.67, BenetakoLuzera*0.58);
		gtk_widget_set_size_request (eventboxP11, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK11, BenetakoZabalera*0.67, BenetakoLuzera*0.616);
		gtk_widget_set_size_request (eventboxK11, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox12, BenetakoZabalera*0.22, BenetakoLuzera*0.1);
	gtk_widget_set_size_request (eventbox12, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP12, BenetakoZabalera*0.41, BenetakoLuzera*0.1);
		gtk_widget_set_size_request (eventboxP12, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK12, BenetakoZabalera*0.41, BenetakoLuzera*0.136);
		gtk_widget_set_size_request (eventboxK12, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox13, BenetakoZabalera*0.48, BenetakoLuzera*0.1);
	gtk_widget_set_size_request (eventbox13, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP13, BenetakoZabalera*0.67, BenetakoLuzera*0.1);
		gtk_widget_set_size_request (eventboxP13, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK13, BenetakoZabalera*0.67, BenetakoLuzera*0.136);
		gtk_widget_set_size_request (eventboxK13, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox14, BenetakoZabalera*0.22, BenetakoLuzera*0.66);
	gtk_widget_set_size_request (eventbox14, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP14, BenetakoZabalera*0.41, BenetakoLuzera*0.66);
		gtk_widget_set_size_request (eventboxP14, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK14, BenetakoZabalera*0.41, BenetakoLuzera*0.696);
		gtk_widget_set_size_request (eventboxK14, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox15, BenetakoZabalera*0.48, BenetakoLuzera*0.66);
	gtk_widget_set_size_request (eventbox15, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP15, BenetakoZabalera*0.67, BenetakoLuzera*0.66);
		gtk_widget_set_size_request (eventboxP15, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK15, BenetakoZabalera*0.67, BenetakoLuzera*0.696);
		gtk_widget_set_size_request (eventboxK15, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox16, BenetakoZabalera*0.22, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (eventbox16, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP16, BenetakoZabalera*0.41, BenetakoLuzera*0.02);
		gtk_widget_set_size_request (eventboxP16, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK16, BenetakoZabalera*0.41, BenetakoLuzera*0.056);
		gtk_widget_set_size_request (eventboxK16, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox17, BenetakoZabalera*0.48, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (eventbox17, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP17, BenetakoZabalera*0.67, BenetakoLuzera*0.02);
		gtk_widget_set_size_request (eventboxP17, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK17, BenetakoZabalera*0.67, BenetakoLuzera*0.056);
		gtk_widget_set_size_request (eventboxK17, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox18, BenetakoZabalera*0.22, BenetakoLuzera*0.74);
	gtk_widget_set_size_request (eventbox18, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP18, BenetakoZabalera*0.41, BenetakoLuzera*0.74);
		gtk_widget_set_size_request (eventboxP18, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK18, BenetakoZabalera*0.41, BenetakoLuzera*0.776);
		gtk_widget_set_size_request (eventboxK18, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	gtk_fixed_move (GTK_FIXED (fixed), eventbox19, BenetakoZabalera*0.48, BenetakoLuzera*0.74);
	gtk_widget_set_size_request (eventbox19, BenetakoZabalera*0.19, BenetakoLuzera*0.07);
		/* Gai horren prezio eta kopuruen labelak ere egokitu */
		gtk_fixed_move (GTK_FIXED (fixed), eventboxP19, BenetakoZabalera*0.67, BenetakoLuzera*0.74);
		gtk_widget_set_size_request (eventboxP19, BenetakoZabalera*0.06, BenetakoLuzera*0.034);
		gtk_fixed_move (GTK_FIXED (fixed), eventboxK19, BenetakoZabalera*0.67, BenetakoLuzera*0.776);
		gtk_widget_set_size_request (eventboxK19, BenetakoZabalera*0.06, BenetakoLuzera*0.034);

	/* Kontuaren datuak azaltzeko elementuak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), eventboxAukerakoak, BenetakoZabalera*0.74, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (eventboxAukerakoak, BenetakoZabalera*0.15, BenetakoLuzera*0.29);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxAKopuruak, BenetakoZabalera*0.89, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (eventboxAKopuruak, BenetakoZabalera*0.02, BenetakoLuzera*0.29);

	gtk_fixed_move (GTK_FIXED (fixed), vseparator1, BenetakoZabalera*0.91, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (vseparator1, BenetakoZabalera*0.01, BenetakoLuzera*0.29);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxAGuztira, BenetakoZabalera*0.92, BenetakoLuzera*0.02);
	gtk_widget_set_size_request (eventboxAGuztira, BenetakoZabalera*0.07, BenetakoLuzera*0.29);

	gtk_fixed_move (GTK_FIXED (fixed), hseparator1, BenetakoZabalera*0.74, BenetakoLuzera*0.31);
	gtk_widget_set_size_request (hseparator1, BenetakoZabalera*0.25, BenetakoLuzera*0.01);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxGAtalean, BenetakoZabalera*0.74, BenetakoLuzera*0.32);
	gtk_widget_set_size_request (eventboxGAtalean, BenetakoZabalera*0.18, BenetakoLuzera*0.04);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxGuztira, BenetakoZabalera*0.92, BenetakoLuzera*0.32);
	gtk_widget_set_size_request (eventboxGuztira, BenetakoZabalera*0.07, BenetakoLuzera*0.04);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxLabel1, BenetakoZabalera*0.74, BenetakoLuzera*0.37);
	gtk_widget_set_size_request (eventboxLabel1, BenetakoZabalera*0.18, BenetakoLuzera*0.04);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxKGuztira, BenetakoZabalera*0.92, BenetakoLuzera*0.37);
	gtk_widget_set_size_request (eventboxKGuztira, BenetakoZabalera*0.07, BenetakoLuzera*0.04);

	/* Kalkulagailua egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), frameKalkulagailua, BenetakoZabalera*0.74, BenetakoLuzera*0.43);
	gtk_widget_set_size_request (frameKalkulagailua, BenetakoZabalera*0.24, BenetakoLuzera*0.31);

	/* Mugimendu labelak eta bazkidearen izena azaltzeko labelak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), eventboxKontuaEgin, BenetakoZabalera*0.03, BenetakoLuzera*0.9);
	gtk_widget_set_size_request (eventboxKontuaEgin, BenetakoZabalera*0.16, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblIzena, BenetakoZabalera*0.21, BenetakoLuzera*0.9);
	gtk_widget_set_size_request (lblIzena, BenetakoZabalera*0.58, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxKontuaUtzi, BenetakoZabalera*0.81, BenetakoLuzera*0.9);
	gtk_widget_set_size_request (eventboxKontuaUtzi, BenetakoZabalera*0.16, BenetakoLuzera*0.05);
}

void aukerakKoloreztatu()
{
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxA0, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA1, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA2, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA3, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA4, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA5, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA6, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA7, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA8, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(eventboxA9, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_fg(lblAukerak0, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak1, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak2, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak3, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak4, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak5, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak6, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak7, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak8, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_fg(lblAukerak9, GTK_STATE_NORMAL, &kolorea);

	/* Une honetan aukeraturik daogen aukera aldatuko dugu */
	if (unekoAukera>=0)
	{
		char a[5];
		sprintf(a, "%d", unekoAukera);
		gdk_color_parse("red", &kolorea);
		switch(a[0])
		{
			case '0':gtk_widget_set_sensitive(eventboxA0, TRUE);
				gtk_widget_modify_fg(lblAukerak0, GTK_STATE_NORMAL, &kolorea);
				break;
			case '1':gtk_widget_set_sensitive(eventboxA1, TRUE);
				gtk_widget_modify_fg(lblAukerak1, GTK_STATE_NORMAL, &kolorea);
				break;
			case '2':gtk_widget_set_sensitive(eventboxA2, TRUE);
				gtk_widget_modify_fg(lblAukerak2, GTK_STATE_NORMAL, &kolorea);
				break;
			case '3':gtk_widget_set_sensitive(eventboxA3, TRUE);
				gtk_widget_modify_fg(lblAukerak3, GTK_STATE_NORMAL, &kolorea);
				break;
			case '4':gtk_widget_set_sensitive(eventboxA4, TRUE);
				gtk_widget_modify_fg(lblAukerak4, GTK_STATE_NORMAL, &kolorea);
				break;
			case '5':gtk_widget_set_sensitive(eventboxA5, TRUE);
				gtk_widget_modify_fg(lblAukerak5, GTK_STATE_NORMAL, &kolorea);
				break;
			case '6':gtk_widget_set_sensitive(eventboxA6, TRUE);
				gtk_widget_modify_fg(lblAukerak6, GTK_STATE_NORMAL, &kolorea);
				break;
			case '7':gtk_widget_set_sensitive(eventboxA7, TRUE);
				gtk_widget_modify_fg(lblAukerak7, GTK_STATE_NORMAL, &kolorea);
				break;
			case '8':gtk_widget_set_sensitive(eventboxA8, TRUE);
				gtk_widget_modify_fg(lblAukerak8, GTK_STATE_NORMAL, &kolorea);
				break;
			case '9':gtk_widget_set_sensitive(eventboxA9, TRUE);
				gtk_widget_modify_fg(lblAukerak9, GTK_STATE_NORMAL, &kolorea);
				break;
			default: break;
		}
	}
}

void gaiakKoloreztatu()
{
	GdkColor gorria, urdina, beltza, grisa;
	gdk_color_parse("blue", &urdina);
	gdk_color_parse("black", &beltza);
	gdk_color_parse("red", &gorria);
	gdk_color_parse("#e3e0e0", &grisa);
	/* unekoGaia erabili, zein gai dagoen aukeratuta jakiteko */
	char g[5];
	gaia *lag;
	lag=arrGaiak[unekoAukera];
	int i;
	for (i=0; i<gaikop; i++)
	{
		if (lag[i].Zenbat>0)
		{
			if (i < 10)
			{
				sprintf(g, "%d", i);
				switch(g[0])
				{
					case '0': gtk_widget_modify_bg(eventbox0, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP0, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK0, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak0, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa0, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak0, GTK_STATE_NORMAL, &urdina);
						break;
					case '1': gtk_widget_modify_bg(eventbox1, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP1, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK1, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak1, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa1, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak1, GTK_STATE_NORMAL, &urdina);
						break;
					case '2': gtk_widget_modify_bg(eventbox2, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP2, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK2, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak2, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa2, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak2, GTK_STATE_NORMAL, &urdina);
						break;
					case '3': gtk_widget_modify_bg(eventbox3, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP3, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK3, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak3, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa3, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak3, GTK_STATE_NORMAL, &urdina);
						break;
					case '4': gtk_widget_modify_bg(eventbox4, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP4, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK4, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak4, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa4, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak4, GTK_STATE_NORMAL, &urdina);
						break;
					case '5': gtk_widget_modify_bg(eventbox5, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP5, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK5, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak5, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa5, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak5, GTK_STATE_NORMAL, &urdina);
						break;
					case '6': gtk_widget_modify_bg(eventbox6, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP6, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK6, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak6, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa6, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak6, GTK_STATE_NORMAL, &urdina);
						break;
					case '7': gtk_widget_modify_bg(eventbox7, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP7, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK7, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak7, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa7, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak7, GTK_STATE_NORMAL, &urdina);
						break;
					case '8': gtk_widget_modify_bg(eventbox8, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP8, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK8, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak8, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa8, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak8, GTK_STATE_NORMAL, &urdina);
						break;
					case '9': gtk_widget_modify_bg(eventbox9, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP9, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK9, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak9, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa9, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak9, GTK_STATE_NORMAL, &urdina);
						break;
					default: break;
				}
			}
			else
			{
				sprintf(g, "%d", i-10);
				switch(g[0])
				{
					case '0': gtk_widget_modify_bg(eventbox10, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP10, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK10, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak10, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa10, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak10, GTK_STATE_NORMAL, &urdina);
						break;
					case '1': gtk_widget_modify_bg(eventbox11, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP11, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK11, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak11, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa11, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak11, GTK_STATE_NORMAL, &urdina);
						break;
					case '2': gtk_widget_modify_bg(eventbox12, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP12, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK12, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak12, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa12, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak12, GTK_STATE_NORMAL, &urdina);
						break;
					case '3': gtk_widget_modify_bg(eventbox13, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP13, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK13, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak13, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa13, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak13, GTK_STATE_NORMAL, &urdina);
						break;
					case '4': gtk_widget_modify_bg(eventbox14, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP14, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK14, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak14, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa14, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak14, GTK_STATE_NORMAL, &urdina);
						break;
					case '5': gtk_widget_modify_bg(eventbox15, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP15, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK15, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak15, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa15, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak15, GTK_STATE_NORMAL, &urdina);
						break;
					case '6': gtk_widget_modify_bg(eventbox16, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP16, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK16, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak16, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa16, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak16, GTK_STATE_NORMAL, &urdina);
						break;
					case '7': gtk_widget_modify_bg(eventbox17, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP17, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK17, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak17, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa17, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak17, GTK_STATE_NORMAL, &urdina);
						break;
					case '8': gtk_widget_modify_bg(eventbox18, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP18, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK18, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak18, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa18, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak18, GTK_STATE_NORMAL, &urdina);
						break;
					case '9': gtk_widget_modify_bg(eventbox19, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxP19, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK19, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak19, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblPrezioa19, GTK_STATE_NORMAL, &urdina);
						  gtk_widget_modify_fg(lblKopuruak19, GTK_STATE_NORMAL, &urdina);
						break;
					default: break;
				}
			}
		}
		else
		{
			if (i < 10)
			{
				sprintf(g, "%d", i);
				switch(g[0])
				{
					case '0': gtk_widget_modify_bg(eventbox0, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP0, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK0, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak0, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa0, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak0, GTK_STATE_NORMAL, &urdina);
						break;
					case '1': gtk_widget_modify_bg(eventbox1, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP1, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK1, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak1, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa1, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak1, GTK_STATE_NORMAL, &urdina);
						break;
					case '2': gtk_widget_modify_bg(eventbox2, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP2, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK2, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak2, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa2, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak2, GTK_STATE_NORMAL, &urdina);
						break;
					case '3': gtk_widget_modify_bg(eventbox3, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP3, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK3, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak3, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa3, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak3, GTK_STATE_NORMAL, &urdina);
						break;
					case '4': gtk_widget_modify_bg(eventbox4, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP4, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK4, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak4, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa4, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak4, GTK_STATE_NORMAL, &urdina);
						break;
					case '5': gtk_widget_modify_bg(eventbox5, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP5, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK5, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak5, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa5, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak5, GTK_STATE_NORMAL, &urdina);
						break;
					case '6': gtk_widget_modify_bg(eventbox6, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP6, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK6, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak6, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa6, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak6, GTK_STATE_NORMAL, &urdina);
						break;
					case '7': gtk_widget_modify_bg(eventbox7, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP7, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK7, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak7, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa7, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak7, GTK_STATE_NORMAL, &urdina);
						break;
					case '8': gtk_widget_modify_bg(eventbox8, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP8, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK8, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak8, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa8, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak8, GTK_STATE_NORMAL, &urdina);
						break;
					case '9': gtk_widget_modify_bg(eventbox9, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP9, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK9, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak9, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa9, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak9, GTK_STATE_NORMAL, &urdina);
						break;
					default: break;
				}
			}
			else
			{
				sprintf(g, "%d", i-10);
				switch(g[0])
				{
					case '0': gtk_widget_modify_bg(eventbox10, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP10, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK10, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak10, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa10, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak10, GTK_STATE_NORMAL, &urdina);
						break;
					case '1': gtk_widget_modify_bg(eventbox11, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP11, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK11, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak11, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa11, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak11, GTK_STATE_NORMAL, &urdina);
						break;
					case '2': gtk_widget_modify_bg(eventbox12, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP12, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK12, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak12, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa12, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak12, GTK_STATE_NORMAL, &urdina);
						break;
					case '3': gtk_widget_modify_bg(eventbox13, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP13, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK13, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak13, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa13, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak13, GTK_STATE_NORMAL, &urdina);
						break;
					case '4': gtk_widget_modify_bg(eventbox14, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP14, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK14, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak14, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa14, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak14, GTK_STATE_NORMAL, &urdina);
						break;
					case '5': gtk_widget_modify_bg(eventbox15, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP15, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK15, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak15, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa15, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak15, GTK_STATE_NORMAL, &urdina);
						break;
					case '6': gtk_widget_modify_bg(eventbox16, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP16, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK16, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak16, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa16, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak16, GTK_STATE_NORMAL, &urdina);
						break;
					case '7': gtk_widget_modify_bg(eventbox17, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP17, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK17, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak17, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa17, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak17, GTK_STATE_NORMAL, &urdina);
						break;
					case '8': gtk_widget_modify_bg(eventbox18, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP18, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK18, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak18, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa18, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak18, GTK_STATE_NORMAL, &urdina);
						break;
					case '9': gtk_widget_modify_bg(eventbox19, GTK_STATE_NORMAL, &grisa);
						  gtk_widget_modify_bg(eventboxP19, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_bg(eventboxK19, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblGaiak19, GTK_STATE_NORMAL, &beltza);
						  gtk_widget_modify_fg(lblPrezioa19, GTK_STATE_NORMAL, &gorria);
						  gtk_widget_modify_fg(lblKopuruak19, GTK_STATE_NORMAL, &urdina);
						break;
					default: break;
				}
			}
		}
	}

	if (unekoGaia >= 0)
	{
		if (unekoGaia < 10)
		{
			sprintf(g, "%d", unekoGaia);
			switch(g[0])
			{
				case '0': gtk_widget_modify_bg(eventbox0, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP0, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK0, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak0, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa0, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak0, GTK_STATE_NORMAL, &urdina);
					break;
				case '1': gtk_widget_modify_bg(eventbox1, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP1, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK1, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak1, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa1, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak1, GTK_STATE_NORMAL, &urdina);
					break;
				case '2': gtk_widget_modify_bg(eventbox2, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP2, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK2, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak2, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa2, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak2, GTK_STATE_NORMAL, &urdina);
					break;
				case '3': gtk_widget_modify_bg(eventbox3, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP3, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK3, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak3, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa3, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak3, GTK_STATE_NORMAL, &urdina);
					break;
				case '4': gtk_widget_modify_bg(eventbox4, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP4, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK4, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak4, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa4, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak4, GTK_STATE_NORMAL, &urdina);
					break;
				case '5': gtk_widget_modify_bg(eventbox5, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP5, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK5, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak5, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa5, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak5, GTK_STATE_NORMAL, &urdina);
					break;
				case '6': gtk_widget_modify_bg(eventbox6, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP6, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK6, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak6, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa6, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak6, GTK_STATE_NORMAL, &urdina);
					break;
				case '7': gtk_widget_modify_bg(eventbox7, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP7, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK7, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak7, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa7, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak7, GTK_STATE_NORMAL, &urdina);
					break;
				case '8': gtk_widget_modify_bg(eventbox8, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP8, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK8, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak8, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa8, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak8, GTK_STATE_NORMAL, &urdina);
					break;
				case '9': gtk_widget_modify_bg(eventbox9, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP9, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK9, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak9, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa9, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak9, GTK_STATE_NORMAL, &urdina);
					break;
				default: break;
			}
		}
		else
		{
			sprintf(g, "%d", unekoGaia-10);
			switch(g[0])
			{
				case '0': gtk_widget_modify_bg(eventbox10, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP10, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK10, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak10, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa10, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak10, GTK_STATE_NORMAL, &urdina);
					break;
				case '1': gtk_widget_modify_bg(eventbox11, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP11, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK11, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak11, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa11, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak11, GTK_STATE_NORMAL, &urdina);
					break;
				case '2': gtk_widget_modify_bg(eventbox12, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP12, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK12, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak12, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa12, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak12, GTK_STATE_NORMAL, &urdina);
					break;
				case '3': gtk_widget_modify_bg(eventbox13, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP13, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK13, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak13, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa13, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak13, GTK_STATE_NORMAL, &urdina);
					break;
				case '4': gtk_widget_modify_bg(eventbox14, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP14, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK14, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak14, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa14, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak14, GTK_STATE_NORMAL, &urdina);
					break;
				case '5': gtk_widget_modify_bg(eventbox15, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP15, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK15, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak15, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa15, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak15, GTK_STATE_NORMAL, &urdina);
					break;
				case '6': gtk_widget_modify_bg(eventbox16, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP16, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK16, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak16, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa16, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak16, GTK_STATE_NORMAL, &urdina);
					break;
				case '7': gtk_widget_modify_bg(eventbox17, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP17, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK17, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak17, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa17, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak17, GTK_STATE_NORMAL, &urdina);
					break;
				case '8': gtk_widget_modify_bg(eventbox18, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP18, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK18, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak18, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa18, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak18, GTK_STATE_NORMAL, &urdina);
					break;
				case '9': gtk_widget_modify_bg(eventbox19, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxP19, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_bg(eventboxK19, GTK_STATE_NORMAL, &beltza);
					  gtk_widget_modify_fg(lblGaiak19, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblPrezioa19, GTK_STATE_NORMAL, &gorria);
					  gtk_widget_modify_fg(lblKopuruak19, GTK_STATE_NORMAL, &urdina);
					break;
				default: break;
			}
		}
	}
}

static void form_load()
{
	/* kontuak egiteko formularioa momentuko pantaila bereizmenera egokitu */
	aukerakKokatu();

	MYSQL_ROW row;

	/* Aukerak eta berauen gaiak kargatu */
	mysql_query(dbElkartea, "Select * from Aukerak order by AOrdena");
	rstAukerak = mysql_store_result(dbElkartea);
	aukeraKop=mysql_num_rows(rstAukerak);
	if (aukeraKop > 10)
	{
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmElkarteGastronomikoa),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_WARNING,
						GTK_BUTTONS_OK,
						"Kontua egiteko orduan azal daitezkeen aukera kopurua (10) baino gehiago daude.\nZure elkarteko administratzailearekin kontaktatu mesedez.");
		gtk_dialog_run (GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		aukeraKop=10;
	}

	arrAukerak = (char **) malloc (aukeraKop*sizeof(char *));
	arrGaiak = (gaia **) malloc (aukeraKop*sizeof(gaia *));
	
	int i;
	char sql[500];
	for (i=0; i<aukeraKop; i++)
	{
		row = mysql_fetch_row(rstAukerak);
		arrAukerak[i]=(char *) malloc(strlen(row[0])+1);
		strcpy(arrAukerak[i], row[0]);
		int AKodea = atoi(row[2]);

		/* Aukera erakutsiko dugu */
		char a[5];
		sprintf(a, "%d", i);
		if (i<10)
			aukerakErakutsi(a, row[0]);

		/* Aukera honen gaiak sartuko ditugu arrGaiak -en */
		sprintf(sql, "SELECT * FROM Gaiak, Elkartea where Elkartea.gaikodea = Gaiak.GKodea and Gaiak.AKodea = %d and Gaiak.erabilgarri order by gordena asc", atoi(row[2]));
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_store_result(dbElkartea);
		int gaikop=mysql_num_rows(rstGaiak);
		arrGaia = (gaia *) malloc(gaikop*sizeof(gaia));
		int k;
		for (k=0; k<gaikop; k++)
		{
			row=mysql_fetch_row(rstGaiak);
			strcpy(arrGaia[k].Izena, row[0]);
			arrGaia[k].AKodea = AKodea;
			arrGaia[k].Prezioa = atof(row[2]);
			arrGaia[k].Zenbat = 0;
			arrGaia[k].Menpekotasuna = atoi(row[3]);
			arrGaia[k].Kodea = atoi(row[4]);
			if (arrGaia[k].Menpekotasuna != 0)
				menpekoduna = true;
		}
		arrGaiak[i]=arrGaia;
		mysql_free_result(rstGaiak);
	}

	// menpekoduna=true bada KokatuGaldera eta frmGaldera erakutsi, bestela exekuzioa normal jarraitu
	bazkideKop=0;
	ezBazkideKop=0;
	if (menpekoduna)
		galdera(frmElkarteGastronomikoa);

	/* Uneko aukeraren gaiak erakutsi */
	unekoAukera=0;
	unekoGaia=-1;
	gaiakErakutsi();

	/* Uneko bazkidearen izena azaldu */
	char izena[100];
	sprintf(izena, "<span size='x-large'>%s</span>", unekoIzena);
	gtk_label_set_text(GTK_LABEL(lblIzena), izena);
	gtk_label_set_use_markup(GTK_LABEL(lblIzena), TRUE);

	/* Aukera eta gaien labelak koloreztatu */
	aukerakKoloreztatu();
	gaiakKoloreztatu();
}

void garbituGaiak()
{
	gtk_widget_hide(eventbox0); gtk_widget_hide(eventboxP0); gtk_widget_hide(eventboxK0);
	gtk_widget_hide(eventbox1); gtk_widget_hide(eventboxP1); gtk_widget_hide(eventboxK1);
	gtk_widget_hide(eventbox2); gtk_widget_hide(eventboxP2); gtk_widget_hide(eventboxK2);
	gtk_widget_hide(eventbox3); gtk_widget_hide(eventboxP3); gtk_widget_hide(eventboxK3);
	gtk_widget_hide(eventbox4); gtk_widget_hide(eventboxP4); gtk_widget_hide(eventboxK4);
	gtk_widget_hide(eventbox5); gtk_widget_hide(eventboxP5); gtk_widget_hide(eventboxK5);
	gtk_widget_hide(eventbox6); gtk_widget_hide(eventboxP6); gtk_widget_hide(eventboxK6);
	gtk_widget_hide(eventbox7); gtk_widget_hide(eventboxP7); gtk_widget_hide(eventboxK7);
	gtk_widget_hide(eventbox8); gtk_widget_hide(eventboxP8); gtk_widget_hide(eventboxK8);
	gtk_widget_hide(eventbox9); gtk_widget_hide(eventboxP9); gtk_widget_hide(eventboxK9);
	gtk_widget_hide(eventbox10); gtk_widget_hide(eventboxP10); gtk_widget_hide(eventboxK10);
	gtk_widget_hide(eventbox11); gtk_widget_hide(eventboxP11); gtk_widget_hide(eventboxK11);
	gtk_widget_hide(eventbox12); gtk_widget_hide(eventboxP12); gtk_widget_hide(eventboxK12);
	gtk_widget_hide(eventbox13); gtk_widget_hide(eventboxP13); gtk_widget_hide(eventboxK13);
	gtk_widget_hide(eventbox14); gtk_widget_hide(eventboxP14); gtk_widget_hide(eventboxK14);
	gtk_widget_hide(eventbox15); gtk_widget_hide(eventboxP15); gtk_widget_hide(eventboxK15);
	gtk_widget_hide(eventbox16); gtk_widget_hide(eventboxP16); gtk_widget_hide(eventboxK16);
	gtk_widget_hide(eventbox17); gtk_widget_hide(eventboxP17); gtk_widget_hide(eventboxK17);
	gtk_widget_hide(eventbox18); gtk_widget_hide(eventboxP18); gtk_widget_hide(eventboxK18);
	gtk_widget_hide(eventbox19); gtk_widget_hide(eventboxP19); gtk_widget_hide(eventboxK19);
}

/************************* Joseba frmKontuaUtzi nik sortu dut *****/
static void btmKontuaUtziAdos()
{
	gtk_widget_destroy (frmKontuaUtzi);
		mysql_free_result(rstAukerak);
		free(arrAukerak);
		free(arrGaiak);
		free(arrGaia);
		gtk_main_quit();
		gtk_widget_destroy(frmAukerak);
}
static void btmKontuaEzUtzi()
{
	gtk_widget_destroy (frmKontuaUtzi);
}
static void btmKontuaUtzi()
{

	GtkWidget *label;
	GtkWidget *botoia;
	GtkWidget *hBox, *vBox;
	GtkWidget *taula;
	GtkWidget *frame;
	GdkColor kolorea;


	/* frmKontuaUtzi sortu eta hasieratu*/
	frmKontuaUtzi = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_decorated (GTK_WINDOW(frmKontuaUtzi), FALSE);
	//gtk_window_set_type_hint (GTK_WINDOW(frmKontuaUtzi), GDK_WINDOW_TYPE_HINT_DIALOG);
	//gtk_window_set_transient_for (GTK_WINDOW(frmKontuaUtzi), GTK_WINDOW(frmElkarteGastronomikoa));
	gtk_window_set_position (GTK_WINDOW(frmKontuaUtzi), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW(frmKontuaUtzi), TRUE);

        gdk_color_parse ("#e3e0e0", &kolorea);
	gtk_widget_modify_bg (frmKontuaUtzi, GTK_STATE_NORMAL, &kolorea);
	
	label = gtk_label_new("<span size='x-large'><b>Kontua Utzi?</b></span>");
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	frame = gtk_frame_new(NULL);
	gtk_frame_set_label_widget(GTK_FRAME(frame), label);
	gtk_container_add (GTK_CONTAINER(frmKontuaUtzi), frame);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER(frame), vBox);

	/* Lehenengo lerroa sortu eta sartu (bi botoia) */
	hBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, FALSE, FALSE, 0);


	botoia = gtk_button_new_with_label ("EZ Utzi");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmKontuaEzUtzi), NULL);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, FALSE, 10);
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmKontuaUtziAdos), NULL);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, FALSE, 10);

	/* dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmKontuaUtzi);

}
/*********************** Josebak kendutakoa **************
{
	GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmAukerak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Ziur al zaude irten nahi duzula?");
	gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
	gtk_widget_destroy (mezua);
	if (erantzuna == GTK_RESPONSE_YES)
	{
		mysql_free_result(rstAukerak);
		free(arrAukerak);
		free(arrGaiak);
		free(arrGaia);
		gtk_main_quit();
		gtk_widget_destroy(frmAukerak);
	}
}
*********** Honaino *************/

/**
* Kalkulagailuaren laburpena kargatzeko funtzioa
*/
void datuakAktualizatu()
{
	int i, k;
	double batura=0;
	int kop;
	char denera[50];
	char sql[200];
	MYSQL_ROW row;

	gaia *lag;
	lag = arrGaiak[unekoAukera];
	gtk_label_set_text(GTK_LABEL(lblAukerakoak), "");
	gtk_label_set_text(GTK_LABEL(lblAKopuruak), "");
	gtk_label_set_text(GTK_LABEL(lblAGuztira), "");
	/* Uneko aukeraren gai guztien kostua kalkulatu eta azaldu */
	for (i=0; i<gaikop; i++)
	{
		batura = batura + (lag[i].Zenbat * lag[i].Prezioa);
		if (lag[i].Zenbat>0)
		{
			/* laburpeneko datuak aktualizatu */
			char testua[500];
			sprintf(testua, "<span size='large'>%s", gtk_label_get_text(GTK_LABEL(lblAukerakoak)));
			strcat (testua, lag[i].Izena);
			strcat (testua, "</span>\n");
			gtk_label_set_text(GTK_LABEL(lblAukerakoak), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblAukerakoak), TRUE);
			sprintf(testua, "<span size='large'>%s", gtk_label_get_text(GTK_LABEL(lblAKopuruak)));
			sprintf(denera, "%d", lag[i].Zenbat);
			strcat (testua, denera);
			strcat (testua, "</span>\n");
			gtk_label_set_text(GTK_LABEL(lblAKopuruak), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblAKopuruak), TRUE);
			sprintf(testua, "<span size='large'>%s", gtk_label_get_text(GTK_LABEL(lblAGuztira)));
			sprintf(denera, "%.2f", lag[i].Zenbat * lag[i].Prezioa);
			strcat (testua, denera);
			strcat (testua, "</span>\n");
			gtk_label_set_text(GTK_LABEL(lblAGuztira), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblAGuztira), TRUE);
		}
		
	}
	sprintf(denera, "<span size='x-large'>%.2f</span>", batura);
	gtk_label_set_text(GTK_LABEL(lblGuztira), denera);
	gtk_label_set_use_markup(GTK_LABEL(lblGuztira), TRUE);

	/* Kontuaren gastua kalkulatu eta azaldu */
	batura=0;
	for (i=0; i<aukeraKop; i++)
	{
		lag=arrGaiak[i];

		mysql_data_seek(rstAukerak, i);
		row=mysql_fetch_row(rstAukerak);
		sprintf(sql, "SELECT count(*) from Gaiak, Elkartea where Elkartea.Gaikodea = Gaiak.GKodea AND AKodea =%d and Gaiak.erabilgarri", atoi(row[2]));
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_store_result(dbElkartea);
		if (row=mysql_fetch_row(rstGaiak))
			kop=atoi(row[0]);
		else
			kop=0;
		mysql_free_result(rstGaiak);

		for (k=0; k<kop; k++)
		{
			batura = batura + (lag[k].Zenbat * lag[k].Prezioa);
		}
	}
	sprintf(denera, "<span size='x-large'>%.2f</span>", batura);
	gtk_label_set_text(GTK_LABEL(lblKGuztira), denera);
	gtk_label_set_use_markup(GTK_LABEL(lblKGuztira), TRUE);
}

/**
* Hurrengoa botoiaren funtzioa. Uneko egoeraren arabera hurrengo aukera kargatu edo kontua egitera pasa
*/
static void btmHurrengoa()
{
	if (strcmp(gtk_label_get_text(GTK_LABEL(lblKontuaEgin)), "Hurrengoa")==0)
	{
		garbituGaiak();
		unekoAukera++;
		unekoGaia=-1;
		gaiakErakutsi();
		/* Azkeneko aukera bada, lblKontuaEgin -en testua aldatu behar */
		if (unekoAukera==aukeraKop-1)
		{
			gtk_label_set_text(GTK_LABEL(lblKontuaEgin), "<span size='x-large'>Kontua egin</span>");
			gtk_label_set_use_markup(GTK_LABEL(lblKontuaEgin), TRUE);
		}

		/* Aukera berrriaren datuak aktualizatu */
		datuakAktualizatu();

		/* Kalkulagailua ixkutatu */
		gtk_widget_hide(frameKalkulagailua);

		aukerakKoloreztatu();
		gaiakKoloreztatu();
	}
	else
	{
		/* Kontua egiteko lehio ixkutatu eta berriz atzera itzultzen bada ere prestatu */
		gtk_widget_hide(frameKalkulagailua);
		garbituGaiak();
		unekoGaia=-1;
		unekoAukera=-1;
		aukerakKoloreztatu();
		gtk_label_set_text(GTK_LABEL(lblAukerakoak), "");
		gtk_label_set_text(GTK_LABEL(lblAKopuruak), "");
		gtk_label_set_text(GTK_LABEL(lblAGuztira), "");
		gtk_label_set_text(GTK_LABEL(lblAGuztira), "");
		/* Kontuaren datuak azaltzeko formularioa deitu */
		kontua();
		gtk_widget_hide(frmAukerak);
	}
}

char * lortuAukera(int i)
{
	char a[5];
	sprintf(a, "%d", i);

	switch(a[0])
	{
		case '0': return (gtk_label_get_text(GTK_LABEL(lblAukerak0)));
			  break;
		case '1': return (gtk_label_get_text(GTK_LABEL(lblAukerak1)));
			  break;
		case '2': return (gtk_label_get_text(GTK_LABEL(lblAukerak2)));
			  break;
		case '3': return (gtk_label_get_text(GTK_LABEL(lblAukerak3)));
			  break;
		case '4': return (gtk_label_get_text(GTK_LABEL(lblAukerak4)));
			  break;
		case '5': return (gtk_label_get_text(GTK_LABEL(lblAukerak5)));
			  break;
		case '6': return (gtk_label_get_text(GTK_LABEL(lblAukerak6)));
			  break;
		case '7': return (gtk_label_get_text(GTK_LABEL(lblAukerak7)));
			  break;
		case '8': return (gtk_label_get_text(GTK_LABEL(lblAukerak8)));
			  break;
		case '9': return (gtk_label_get_text(GTK_LABEL(lblAukerak9)));
			  break;
		default: break;
	}
}

static void btmAukerak(GtkWidget *widget, GdkEventButton *event,
				    gpointer data)
{
	/* unekoAukera zein den kalkulatzeko */
	char testua[50];
	sprintf(testua, "%s", gtk_label_get_text(data));

	/* Huneko aukera zein den jakiteko Aukera guztiak pasako ditugu euren izena hunean klikatutakoarekin konparatuz... */
	int i;
	for (i=0; i<aukeraKop; i++)
	{
		if (strcmp(testua, lortuAukera(i))==0)
			break;
	}
	/* 'i' aldagaian egongo da huneko aukera zenbakia (arrGaiak aldagaiko posizioa hain zuzen) */
	unekoAukera = i;
	unekoGaia = -1;
	garbituGaiak();
	gaiakErakutsi();

	gtk_widget_hide(frameKalkulagailua);
	datuakAktualizatu();

	aukerakKoloreztatu();
	gaiakKoloreztatu();
}

static void btmGaiak(GtkWidget *widget, GdkEventButton *event,
				    gpointer data)
{
	char testua[50];
	MYSQL_ROW row;
	char sql[200];

	gaia *lag;
	lag=arrGaiak[unekoAukera];

	/* Klikatutako labelaren testua lortu */
	sprintf(testua, "%s", gtk_label_get_text(data));

	/* Huneko Gaia zein den jakiteko gai guztiak prozesatu euren izenan hunean klikatutakoarekin konparatuz */
	int i;
	for (i=0; i<gaikop; i++)
	{
		if (strcmp(testua, lag[i].Izena)==0)
			break;
	}
	unekoGaia=i;

	sprintf(testua, "%d", lag[unekoGaia].Zenbat);

	/* Uneko Gaia lehendik kontsumituta dago? */
	if (lag[unekoGaia].Zenbat>0)
		gtk_entry_set_text(GTK_ENTRY(txtKopurua), testua);
	else
		gtk_entry_set_text(GTK_ENTRY(txtKopurua), "0");

	/* Huneko gaiaren menpekotasunaren arabera, bazkide/ez-bazkide kopuruaren arabera egin behar kalkulua */
	sprintf(testua, "%d", lag[unekoGaia].Menpekotasuna);
	switch (testua[0])
	{
		case '0': gtk_widget_show_all(frameKalkulagailua);
			  break;
		case '4': gtk_widget_show_all(frameKalkulagailua);
			  break;
		default:  galdera(frmAukerak);
			  garbituGaiak();
			  gaiakErakutsi();
			  datuakAktualizatu();
			  break;
	}

	gaiakKoloreztatu();
}

/**
* Gaiaren kontsumizio kopurua aldatzeko funtzioa
*/
void aldatuKopurua(int gaia, int zenbat)
{
	char g[5];
	char z[50];
	sprintf(z, "%d", zenbat);

	if (gaia < 10)
	{
		sprintf(g, "%d", gaia);
		switch(g[0])
		{
			case '0': gtk_label_set_text(GTK_LABEL(lblKopuruak0), z);
				  break;
			case '1': gtk_label_set_text(GTK_LABEL(lblKopuruak1), z);
				  break;
			case '2': gtk_label_set_text(GTK_LABEL(lblKopuruak2), z);
				  break;
			case '3': gtk_label_set_text(GTK_LABEL(lblKopuruak3), z);
				  break;
			case '4': gtk_label_set_text(GTK_LABEL(lblKopuruak4), z);
				  break;
			case '5': gtk_label_set_text(GTK_LABEL(lblKopuruak5), z);
				  break;
			case '6': gtk_label_set_text(GTK_LABEL(lblKopuruak6), z);
				  break;
			case '7': gtk_label_set_text(GTK_LABEL(lblKopuruak7), z);
				  break;
			case '8': gtk_label_set_text(GTK_LABEL(lblKopuruak8), z);
				  break;
			case '9': gtk_label_set_text(GTK_LABEL(lblKopuruak9), z);
				  break;
			default: break;
		}
	}
	else
	{
		gaia = gaia-10;
		sprintf(g, "%d", gaia);
		switch(g[0])
		{
			case '0': gtk_label_set_text(GTK_LABEL(lblKopuruak10), z);
				  break;
			case '1': gtk_label_set_text(GTK_LABEL(lblKopuruak11), z);
				  break;
			case '2': gtk_label_set_text(GTK_LABEL(lblKopuruak12), z);
				  break;
			case '3': gtk_label_set_text(GTK_LABEL(lblKopuruak13), z);
				  break;
			case '4': gtk_label_set_text(GTK_LABEL(lblKopuruak14), z);
				  break;
			case '5': gtk_label_set_text(GTK_LABEL(lblKopuruak15), z);
				  break;
			case '6': gtk_label_set_text(GTK_LABEL(lblKopuruak16), z);
				  break;
			case '7': gtk_label_set_text(GTK_LABEL(lblKopuruak17), z);
				  break;
			case '8': gtk_label_set_text(GTK_LABEL(lblKopuruak18), z);
				  break;
			case '9': gtk_label_set_text(GTK_LABEL(lblKopuruak19), z);
				  break;
			default: break;
		}
	}
}

/**
* Kalkulagailuaren ekintzak kontrolatzeko funtzioa
*/
static void btmZenbakia(GtkWidget *botoia, gpointer testua)
{
	char kopurua[50];
	sprintf(kopurua, "%s", gtk_entry_get_text(GTK_ENTRY(txtKopurua)));

	if (strcmp(testua, "DEL")==0)
	{
		
		if (strlen(kopurua) != 0)
		{
			int k = (atoi(kopurua) - atoi(kopurua) % 10) / 10;
			sprintf(kopurua, "%d", k);
			gtk_entry_set_text(GTK_ENTRY(txtKopurua), kopurua);
		}
	}
	else
		if (strcmp(testua, "+")==0)
		{
			int k = atoi(kopurua) + 1;
			sprintf(kopurua, "%d", k);
			gtk_entry_set_text(GTK_ENTRY(txtKopurua), kopurua);
		}
		else
			if (strcmp(testua, "-")==0)
			{
				int k = atoi(kopurua) - 1;
				sprintf(kopurua, "%d", k);
				gtk_entry_set_text(GTK_ENTRY(txtKopurua), kopurua);
			}
			else
			{
				int k = atoi(kopurua) * 10 + atoi(testua);
				sprintf(kopurua, "%d", k);
				gtk_entry_set_text (GTK_ENTRY(txtKopurua), kopurua);
			}

	gaia *lag;
	lag=arrGaiak[unekoAukera];
	if (strcmp(gtk_entry_get_text(GTK_ENTRY(txtKopurua)), "")==0)
		lag[unekoGaia].Zenbat=0;
	else
		lag[unekoGaia].Zenbat = atoi(gtk_entry_get_text(GTK_ENTRY(txtKopurua)));
	arrGaiak[unekoAukera]=lag;

	aldatuKopurua(unekoGaia, lag[unekoGaia].Zenbat);

	/* Egindako aldaketagatik datuak aktualizatu */
	datuakAktualizatu();

	gaiakKoloreztatu();
}

void aukerak()
{
	GtkWidget *taula;
	GtkWidget *alignment;
	GtkWidget *lblAtzera;
	GtkWidget *labela;
	char *zenb;

	/* Lehioa sortu eta konfiguratu */
	frmAukerak = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_decorated (GTK_WINDOW (frmAukerak), FALSE);
	gdk_color_parse("#02026a", &kolorea);
	gtk_widget_modify_bg(frmAukerak, GTK_STATE_NORMAL, &kolorea);
	gtk_window_fullscreen(GTK_WINDOW(frmAukerak));
	
	/* Lehioaren egitura definitu */
	fixed = gtk_fixed_new ();
	gtk_widget_show (fixed);
	gtk_container_add (GTK_CONTAINER (frmAukerak), fixed);

	/* Aukeren labelak sortu eta sartu */
	eventboxA0 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA0, 24, 24);
	gtk_widget_set_size_request (eventboxA0, 160, 64);
	lblAukerak0 = gtk_label_new ("lblAukerak1");
	gtk_container_add (GTK_CONTAINER (eventboxA0), lblAukerak0);
	gtk_widget_set_size_request (lblAukerak0, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA0), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak0);
	gtk_widget_set_sensitive(eventboxA0, FALSE);

	eventboxA1 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA1, 24, 96);
	gtk_widget_set_size_request (eventboxA1, 160, 64);
	lblAukerak1 = gtk_label_new ("lblAukerak2");
	gtk_container_add (GTK_CONTAINER (eventboxA1), lblAukerak1);
	gtk_widget_set_size_request (lblAukerak1, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA1), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak1);
	gtk_widget_set_sensitive(eventboxA1, FALSE);
	
	eventboxA2 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA2, 24, 168);
	gtk_widget_set_size_request (eventboxA2, 160, 64);
	lblAukerak2 = gtk_label_new ("lblAukerak3");
	gtk_container_add (GTK_CONTAINER (eventboxA2), lblAukerak2);
	gtk_widget_set_size_request (lblAukerak2, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA2), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak2);
	gtk_widget_set_sensitive(eventboxA2, FALSE);

	eventboxA3 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA3, 24, 240);
	gtk_widget_set_size_request (eventboxA3, 160, 64);
	lblAukerak3 = gtk_label_new ("lblAukerak4");
	gtk_container_add (GTK_CONTAINER (eventboxA3), lblAukerak3);
	gtk_widget_set_size_request (lblAukerak3, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA3), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak3);
	gtk_widget_set_sensitive(eventboxA3, FALSE);

	eventboxA4 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA4, 24, 312);
	gtk_widget_set_size_request (eventboxA4, 160, 64);
	lblAukerak4 = gtk_label_new ("lblAukerak5");
	gtk_container_add (GTK_CONTAINER (eventboxA4), lblAukerak4);
	gtk_widget_set_size_request (lblAukerak4, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA4), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak4);
	gtk_widget_set_sensitive(eventboxA4, FALSE);

	eventboxA5 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA5, 24, 384);
	gtk_widget_set_size_request (eventboxA5, 160, 64);
	lblAukerak5 = gtk_label_new ("lblAukerak6");
	gtk_container_add (GTK_CONTAINER (eventboxA5), lblAukerak5);
	gtk_widget_set_size_request (lblAukerak5, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA5), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak5);
	gtk_widget_set_sensitive(eventboxA5, FALSE);

	eventboxA6 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA6, 24, 456);
	gtk_widget_set_size_request (eventboxA6, 160, 64);
	lblAukerak6 = gtk_label_new ("lblAukerak7");
	gtk_container_add (GTK_CONTAINER (eventboxA6), lblAukerak6);
	gtk_widget_set_size_request (lblAukerak6, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA6), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak6);
	gtk_widget_set_sensitive(eventboxA6, FALSE);

	eventboxA7 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA7, 24, 523);
	gtk_widget_set_size_request (eventboxA7, 160, 64);
	lblAukerak7 = gtk_label_new ("lblAukerak8");
	gtk_container_add (GTK_CONTAINER (eventboxA7), lblAukerak7);
	gtk_widget_set_size_request (lblAukerak7, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA7), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak7);
	gtk_widget_set_sensitive(eventboxA7, FALSE);

	eventboxA8 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA8, 24, 598);
	gtk_widget_set_size_request (eventboxA8, 160, 64);
	lblAukerak8 = gtk_label_new ("lblAukerak9");
	gtk_container_add (GTK_CONTAINER (eventboxA8), lblAukerak8);
	gtk_widget_set_size_request (lblAukerak8, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA8), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak8);
	gtk_widget_set_sensitive(eventboxA8, FALSE);

	eventboxA9 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxA9, 24, 668);
	gtk_widget_set_size_request (eventboxA9, 160, 64);
	lblAukerak9 = gtk_label_new ("lblAukerak10");
	gtk_container_add (GTK_CONTAINER (eventboxA9), lblAukerak9);
	gtk_widget_set_size_request (lblAukerak9, 160, 64);
	g_signal_connect(G_OBJECT(eventboxA9), "button_press_event",
			G_CALLBACK(btmAukerak), (gpointer) lblAukerak9);
	gtk_widget_set_sensitive(eventboxA9, FALSE);

	/* Gai bakoitza eta beraren prezioa eta kopurua adierazteko labela sartu */
	eventbox0 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox0, 240, 310);
	gtk_widget_set_size_request (eventbox0, 176, 56);
	lblGaiak0 = gtk_label_new ("lblGaiak1");
	gtk_container_add (GTK_CONTAINER (eventbox0), lblGaiak0);
	gtk_widget_set_size_request (lblGaiak0, 176, 56);
	g_signal_connect(G_OBJECT(eventbox0), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak0);
		/* Prezioa */
		eventboxP0=gtk_event_box_new();
		lblPrezioa0 = gtk_label_new ("lblPrezioa1");
		gtk_container_add(GTK_CONTAINER(eventboxP0), lblPrezioa0);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP0, 416, 304);
		gtk_widget_set_size_request (eventboxP0, 72, 32);
		/* Kopurua */
		eventboxK0 = gtk_event_box_new();
		lblKopuruak0 = gtk_label_new ("lblKopuruak1");
		gtk_container_add(GTK_CONTAINER(eventboxK0), lblKopuruak0);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK0, 416, 336);
		gtk_widget_set_size_request (eventboxK0, 72, 32);

	eventbox1 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox1, 544, 310);
	gtk_widget_set_size_request (eventbox1, 176, 56);
	lblGaiak1 = gtk_label_new ("lblGaiak2");
	gtk_container_add (GTK_CONTAINER (eventbox1), lblGaiak1);
	gtk_widget_set_size_request (lblGaiak1, 176, 56);
	g_signal_connect(G_OBJECT(eventbox1), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak1);
		/* Prezioa */
		eventboxP1 = gtk_event_box_new();
		lblPrezioa1 = gtk_label_new ("lblPrezioa2");
		gtk_container_add(GTK_CONTAINER(eventboxP1), lblPrezioa1);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP1, 720, 304);
		gtk_widget_set_size_request (eventboxP1, 72, 32);
		/* Kopurua */
		eventboxK1 = gtk_event_box_new();
		lblKopuruak1 = gtk_label_new ("lblKopuruak2");
		gtk_container_add(GTK_CONTAINER(eventboxK1), lblKopuruak1);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK1, 720, 336);
		gtk_widget_set_size_request (eventboxK1, 72, 32);

	eventbox2 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox2, 240, 382);
	gtk_widget_set_size_request (eventbox2, 176, 56);
	lblGaiak2 = gtk_label_new ("lblGaiak3");
	gtk_container_add (GTK_CONTAINER (eventbox2), lblGaiak2);
	gtk_widget_set_size_request (lblGaiak2, 176, 56);
	g_signal_connect(G_OBJECT(eventbox2), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak2);
		/* Prezioa */
		eventboxP2 = gtk_event_box_new();
		lblPrezioa2 = gtk_label_new ("lblPrezioa3");
		gtk_container_add(GTK_CONTAINER(eventboxP2), lblPrezioa2);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP2, 416, 376);
		gtk_widget_set_size_request (eventboxP2, 72, 32);
		/* Kopurua */
		eventboxK2 = gtk_event_box_new();
		lblKopuruak2 = gtk_label_new ("lblKopuruak3");
		gtk_container_add(GTK_CONTAINER(eventboxK2), lblKopuruak2);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK2, 416, 408);
		gtk_widget_set_size_request (eventboxK2, 72, 32);

	eventbox3 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox3, 544, 382);
	gtk_widget_set_size_request (eventbox3, 176, 56);
	lblGaiak3 = gtk_label_new ("lblGaiak4");
	gtk_container_add (GTK_CONTAINER (eventbox3), lblGaiak3);
	gtk_widget_set_size_request (lblGaiak3, 176, 56);
	g_signal_connect(G_OBJECT(eventbox3), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak3);
		/* Prezioa */
		eventboxP3 = gtk_event_box_new();
		lblPrezioa3 = gtk_label_new ("lblPrezioa4");
		gtk_container_add(GTK_CONTAINER(eventboxP3), lblPrezioa3);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP3, 720, 376);
		gtk_widget_set_size_request (eventboxP3, 72, 32);
		/* Kopurua */
		eventboxK3 = gtk_event_box_new();
		lblKopuruak3 = gtk_label_new ("lblKopuruak4");
		gtk_container_add(GTK_CONTAINER(eventboxK3), lblKopuruak3);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK3, 720, 408);
		gtk_widget_set_size_request (eventboxK3, 72, 32);

	eventbox4 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox4, 240, 238);
	gtk_widget_set_size_request (eventbox4, 176, 56);
	lblGaiak4 = gtk_label_new ("lblGaiak5");
	gtk_container_add (GTK_CONTAINER (eventbox4), lblGaiak4);
	gtk_widget_set_size_request (lblGaiak4, 176, 56);
	g_signal_connect(G_OBJECT(eventbox4), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak4);
		/* Prezioa */
		eventboxP4 = gtk_event_box_new();
		lblPrezioa4 = gtk_label_new ("lblPrezioa5");
		gtk_container_add(GTK_CONTAINER(eventboxP4), lblPrezioa4);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP4, 416, 232);
		gtk_widget_set_size_request (eventboxP4, 72, 32);
		/* Kopurua */
		eventboxK4 = gtk_event_box_new();
		lblKopuruak4 = gtk_label_new ("lblKopuruak5");
		gtk_container_add(GTK_CONTAINER(eventboxK4), lblKopuruak4);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK4, 416, 264);
		gtk_widget_set_size_request (eventboxK4, 72, 32);

	eventbox5 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox5, 544, 238);
	gtk_widget_set_size_request (eventbox5, 176, 56);
	lblGaiak5 = gtk_label_new ("lblGaiak6");
	gtk_container_add (GTK_CONTAINER (eventbox5), lblGaiak5);
	gtk_widget_set_size_request (lblGaiak5, 176, 56);
	g_signal_connect(G_OBJECT(eventbox5), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak5);
		/* Prezioa */
		eventboxP5 = gtk_event_box_new();
		lblPrezioa5 = gtk_label_new ("lblPrezioa6");
		gtk_container_add(GTK_CONTAINER(eventboxP5), lblPrezioa5);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP5, 720, 232);
		gtk_widget_set_size_request (eventboxP5, 72, 32);
		/* Kopurua */
		eventboxK5 = gtk_event_box_new();
		lblKopuruak5 = gtk_label_new ("lblKopuruak6");
		gtk_container_add(GTK_CONTAINER(eventboxK5), lblKopuruak5);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK5, 720, 264);
		gtk_widget_set_size_request (eventboxK5, 72, 32);

	eventbox6 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox6, 240, 456);
	gtk_widget_set_size_request (eventbox6, 176, 56);
	lblGaiak6 = gtk_label_new ("lblGaiak7");
	gtk_container_add (GTK_CONTAINER (eventbox6), lblGaiak6);
	gtk_widget_set_size_request (lblGaiak6, 176, 56);
	g_signal_connect(G_OBJECT(eventbox6), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak6);
		/* Prezioa */
		eventboxP6 = gtk_event_box_new();
		lblPrezioa6 = gtk_label_new ("lblPrezioa7");
		gtk_container_add(GTK_CONTAINER(eventboxP6), lblPrezioa6);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP6, 416, 448);
		gtk_widget_set_size_request (eventboxP6, 72, 32);
		/* Kopurua */
		eventboxK6 = gtk_event_box_new();
		lblKopuruak6 = gtk_label_new ("lblKopuruak7");
		gtk_container_add(GTK_CONTAINER(eventboxK6), lblKopuruak6);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK6, 416, 480);
		gtk_widget_set_size_request (eventboxK6, 72, 32);

	eventbox7 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox7, 544, 456);
	gtk_widget_set_size_request (eventbox7, 176, 56);
	lblGaiak7 = gtk_label_new ("lblGaiak8");
	gtk_container_add (GTK_CONTAINER (eventbox7), lblGaiak7);
	gtk_widget_set_size_request (lblGaiak7, 176, 56);
	g_signal_connect(G_OBJECT(eventbox7), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak7);
		/* Prezioa */
		eventboxP7 = gtk_event_box_new();
		lblPrezioa7 = gtk_label_new ("lblPrezioa8");
		gtk_container_add(GTK_CONTAINER(eventboxP7), lblPrezioa7);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP7, 720, 448);
		gtk_widget_set_size_request (eventboxP7, 72, 32);
		/* Kopurua */
		eventboxK7 = gtk_event_box_new();
		lblKopuruak7 = gtk_label_new ("lblKopuruak8");
		gtk_container_add(GTK_CONTAINER(eventboxK7), lblKopuruak7);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK7, 720, 480);
		gtk_widget_set_size_request (eventboxK7, 72, 32);

	eventbox8 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox8, 240, 166);
	gtk_widget_set_size_request (eventbox8, 176, 56);
	lblGaiak8 = gtk_label_new ("lblGaiak9");
	gtk_container_add (GTK_CONTAINER (eventbox8), lblGaiak8);
	gtk_widget_set_size_request (lblGaiak8, 176, 56);
	g_signal_connect(G_OBJECT(eventbox8), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak8);
		/* Prezioa */
		eventboxP8 = gtk_event_box_new();
		lblPrezioa8 = gtk_label_new ("lblPrezioa9");
		gtk_container_add(GTK_CONTAINER(eventboxP8), lblPrezioa8);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP8, 416, 160);
		gtk_widget_set_size_request (eventboxP8, 72, 32);
		/* Kopurua */
		eventboxK8 = gtk_event_box_new();
		lblKopuruak8 = gtk_label_new ("lblKopuruak9");
		gtk_container_add(GTK_CONTAINER(eventboxK8), lblKopuruak8);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK8, 416, 192);
		gtk_widget_set_size_request (eventboxK8, 72, 32);

	eventbox9 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox9, 544, 166);
	gtk_widget_set_size_request (eventbox9, 176, 56);
	lblGaiak9 = gtk_label_new ("lblGaiak10");
	gtk_container_add (GTK_CONTAINER (eventbox9), lblGaiak9);
	gtk_widget_set_size_request (lblGaiak9, 176, 56);
	g_signal_connect(G_OBJECT(eventbox9), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak9);
		/* Prezioa */
		eventboxP9 = gtk_event_box_new();
		lblPrezioa9 = gtk_label_new ("lblPrezioa10");
		gtk_container_add(GTK_CONTAINER(eventboxP9), lblPrezioa9);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP9, 720, 160);
		gtk_widget_set_size_request (eventboxP9, 72, 32);
		/* Kopurua */
		eventboxK9 = gtk_event_box_new();
		lblKopuruak9 = gtk_label_new ("lblKopuruak10");
		gtk_container_add(GTK_CONTAINER(eventboxK9), lblKopuruak9);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK9, 720, 192);
		gtk_widget_set_size_request (eventboxK9, 72, 32);

	eventbox10 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox10, 240, 528);
	gtk_widget_set_size_request (eventbox10, 176, 56);
	lblGaiak10 = gtk_label_new ("lblGaiak11");
	gtk_container_add (GTK_CONTAINER (eventbox10), lblGaiak10);
	gtk_widget_set_size_request (lblGaiak10, 176, 56);
	g_signal_connect(G_OBJECT(eventbox10), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak10);
		/* Prezioa */
		eventboxP10 = gtk_event_box_new();
		lblPrezioa10 = gtk_label_new ("lblPrezioa11");
		gtk_container_add(GTK_CONTAINER(eventboxP10), lblPrezioa10);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP10, 416, 520);
		gtk_widget_set_size_request (eventboxP10, 72, 32);
		/* Kopurua */
		eventboxK10 = gtk_event_box_new();
		lblKopuruak10 = gtk_label_new ("lblKopuruak11");
		gtk_container_add(GTK_CONTAINER(eventboxK10), lblKopuruak10);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK10, 416, 552);
		gtk_widget_set_size_request (eventboxK10, 72, 32);

	eventbox11 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox11, 544, 528);
	gtk_widget_set_size_request (eventbox11, 176, 56);
	lblGaiak11 = gtk_label_new ("lblGaiak12");
	gtk_container_add (GTK_CONTAINER (eventbox11), lblGaiak11);
	gtk_widget_set_size_request (lblGaiak11, 176, 56);
	g_signal_connect(G_OBJECT(eventbox11), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak11);
		/* Prezioa */
		eventboxP11 = gtk_event_box_new();
		lblPrezioa11 = gtk_label_new ("lblPrezioa12");
		gtk_container_add(GTK_CONTAINER(eventboxP11), lblPrezioa11);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP11, 720, 520);
		gtk_widget_set_size_request (eventboxP11, 72, 32);
		/* Kopurua */
		eventboxK11 = gtk_event_box_new();
		lblKopuruak11 = gtk_label_new ("lblKopuruak12");
		gtk_container_add(GTK_CONTAINER(eventboxK11), lblKopuruak11);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK11, 720, 552);
		gtk_widget_set_size_request (eventboxK11, 72, 32);

	eventbox12 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox12, 240, 90);
	gtk_widget_set_size_request (eventbox12, 176, 56);
	lblGaiak12 = gtk_label_new ("lblGaiak13");
	gtk_container_add (GTK_CONTAINER (eventbox12), lblGaiak12);
	gtk_widget_set_size_request (lblGaiak12, 176, 56);
	g_signal_connect(G_OBJECT(eventbox12), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak12);
		/* Prezioa */
		eventboxP12 = gtk_event_box_new();
		lblPrezioa12 = gtk_label_new ("lblPrezioa13");
		gtk_container_add(GTK_CONTAINER(eventboxP12), lblPrezioa12);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP12, 416, 88);
		gtk_widget_set_size_request (eventboxP12, 72, 32);
		/* Kopurua */
		eventboxK12 = gtk_event_box_new();
		lblKopuruak12 = gtk_label_new ("lblKopuruak13");
		gtk_container_add(GTK_CONTAINER(eventboxK12), lblKopuruak12);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK12, 416, 120);
		gtk_widget_set_size_request (eventboxK12, 72, 32);

	eventbox13 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox13, 544, 90);
	gtk_widget_set_size_request (eventbox13, 176, 56);
	lblGaiak13 = gtk_label_new ("lblGaiak14");
	gtk_container_add (GTK_CONTAINER (eventbox13), lblGaiak13);
	gtk_widget_set_size_request (lblGaiak13, 176, 56);
	g_signal_connect(G_OBJECT(eventbox13), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak13);
		/* Prezioa */
		eventboxP13 = gtk_event_box_new();
		lblPrezioa13 = gtk_label_new ("lblPrezioa14");
		gtk_container_add(GTK_CONTAINER(eventboxP13), lblPrezioa13);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP13, 720, 88);
		gtk_widget_set_size_request (eventboxP13, 72, 32);
		/* Kopurua */
		eventboxK13 = gtk_event_box_new();
		lblKopuruak13 = gtk_label_new ("lblKopuruak14");
		gtk_container_add(GTK_CONTAINER(eventboxK13), lblKopuruak13);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK13, 720, 120);
		gtk_widget_set_size_request (eventboxK13, 72, 32);

	eventbox14 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox14, 240, 599);
	gtk_widget_set_size_request (eventbox14, 176, 56);
	lblGaiak14 = gtk_label_new ("lblGaiak15");
	gtk_container_add (GTK_CONTAINER (eventbox14), lblGaiak14);
	gtk_widget_set_size_request (lblGaiak14, 176, 56);
	g_signal_connect(G_OBJECT(eventbox14), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak14);
		/* Prezioa */
		eventboxP14 = gtk_event_box_new();
		lblPrezioa14 = gtk_label_new ("lblPrezioa15");
		gtk_container_add(GTK_CONTAINER(eventboxP14), lblPrezioa14);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP14, 416, 592);
		gtk_widget_set_size_request (eventboxP14, 72, 32);
		/* Kopurua */
		eventboxK14 = gtk_event_box_new();
		lblKopuruak14 = gtk_label_new ("lblKopuruak15");
		gtk_container_add(GTK_CONTAINER(eventboxK14), lblKopuruak14);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK14, 416, 624);
		gtk_widget_set_size_request (eventboxK14, 72, 32);

	eventbox15 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox15, 544, 599);
	gtk_widget_set_size_request (eventbox15, 176, 56);
	lblGaiak15 = gtk_label_new ("lblGaiak16");
	gtk_container_add (GTK_CONTAINER (eventbox15), lblGaiak15);
	gtk_widget_set_size_request (lblGaiak15, 176, 56);
	g_signal_connect(G_OBJECT(eventbox15), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak15);
		/* Prezioa */
		eventboxP15 = gtk_event_box_new();
		lblPrezioa15 = gtk_label_new ("lblPrezioa16");
		gtk_container_add(GTK_CONTAINER(eventboxP15), lblPrezioa15);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP15, 720, 592);
		gtk_widget_set_size_request (eventboxP15, 72, 32);
		/* Kopurua */
		eventboxK15 = gtk_event_box_new();
		lblKopuruak15 = gtk_label_new ("lblKopuruak16");
		gtk_container_add(GTK_CONTAINER(eventboxK15), lblKopuruak15);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK15, 720, 624);
		gtk_widget_set_size_request (eventboxK15, 72, 32);

	eventbox16 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox16, 240, 24);
	gtk_widget_set_size_request (eventbox16, 176, 56);
	lblGaiak16 = gtk_label_new ("lblGaiak17");
	gtk_container_add (GTK_CONTAINER (eventbox16), lblGaiak16);
	gtk_widget_set_size_request (lblGaiak16, 176, 56);
	g_signal_connect(G_OBJECT(eventbox16), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak16);
		/* Prezioa */
		eventboxP16 = gtk_event_box_new();
		lblPrezioa16 = gtk_label_new ("lblPrezioa17");
		gtk_container_add(GTK_CONTAINER(eventboxP16), lblPrezioa16);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP16, 416, 16);
		gtk_widget_set_size_request (eventboxP16, 72, 32);
		/* Kopurua */
		eventboxK16 = gtk_event_box_new();
		lblKopuruak16 = gtk_label_new ("lblKopuruak17");
		gtk_container_add(GTK_CONTAINER(eventboxK16), lblKopuruak16);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK16, 416, 48);
		gtk_widget_set_size_request (eventboxK16, 72, 32);
	
	eventbox17 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox17, 544, 24);
	gtk_widget_set_size_request (eventbox17, 176, 56);
	lblGaiak17 = gtk_label_new ("lblGaiak18");
	gtk_container_add (GTK_CONTAINER (eventbox17), lblGaiak17);
	gtk_widget_set_size_request (lblGaiak17, 176, 56);
	g_signal_connect(G_OBJECT(eventbox17), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak17);
		/* Prezioa */
		eventboxP17 = gtk_event_box_new();
		lblPrezioa17 = gtk_label_new ("lblPrezioa18");
		gtk_container_add(GTK_CONTAINER(eventboxP17), lblPrezioa17);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP17, 720, 16);
		gtk_widget_set_size_request (eventboxP17, 72, 32);
		/* Kopurua */
		eventboxK17 = gtk_event_box_new();
		lblKopuruak17 = gtk_label_new ("lblKopuruak18");
		gtk_container_add(GTK_CONTAINER(eventboxK17), lblKopuruak17);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK17, 720, 48);
		gtk_widget_set_size_request (eventboxK17, 72, 32);
	
	eventbox18 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox18, 240, 671);
	gtk_widget_set_size_request (eventbox18, 176, 56);
	lblGaiak18 = gtk_label_new ("lblGaiak19");
	gtk_container_add (GTK_CONTAINER (eventbox18), lblGaiak18);
	gtk_widget_set_size_request (lblGaiak18, 176, 56);
	g_signal_connect(G_OBJECT(eventbox18), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak18);
		/* Prezioa */
		eventboxP18 = gtk_event_box_new();
		lblPrezioa18 = gtk_label_new ("lblPrezioa19");
		gtk_container_add(GTK_CONTAINER(eventboxP18), lblPrezioa18);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP18, 416, 664);
		gtk_widget_set_size_request (eventboxP18, 72, 32);
		/* Kopurua */
		eventboxK18 = gtk_event_box_new();
		lblKopuruak18 = gtk_label_new ("lblKopuruak19");
		gtk_container_add(GTK_CONTAINER(eventboxK18), lblKopuruak18);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK18, 416, 696);
		gtk_widget_set_size_request (eventboxK18, 72, 32);
	
	eventbox19 = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventbox19, 544, 671);
	gtk_widget_set_size_request (eventbox19, 176, 56);
	lblGaiak19 = gtk_label_new ("lblGaiak20");
	gtk_container_add (GTK_CONTAINER (eventbox19), lblGaiak19);
	gtk_widget_set_size_request (lblGaiak19, 176, 56);
	g_signal_connect(G_OBJECT(eventbox19), "button_press_event",
			G_CALLBACK(btmGaiak), (gpointer) lblGaiak19);
		/* Prezioa */
		eventboxP19 = gtk_event_box_new();
		lblPrezioa19 = gtk_label_new ("lblPrezioa20");
		gtk_container_add(GTK_CONTAINER(eventboxP19), lblPrezioa19);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxP19, 720, 664);
		gtk_widget_set_size_request (eventboxP19, 72, 32);
		/* Kopurua */
		eventboxK19 = gtk_event_box_new();
		lblKopuruak19 = gtk_label_new ("lblKopuruak20");
		gtk_container_add(GTK_CONTAINER(eventboxK19), lblKopuruak19);
		gtk_fixed_put (GTK_FIXED (fixed), eventboxK19, 720, 696);
		gtk_widget_set_size_request (eventboxK19, 72, 32);

	/* Kontuaren datuak azaltzeko elementuak sortu eta sartu */
	eventboxAukerakoak = gtk_event_box_new();	
	lblAukerakoak = gtk_label_new ("");
	gtk_container_add(GTK_CONTAINER(eventboxAukerakoak), lblAukerakoak);
	gtk_widget_show_all (eventboxAukerakoak);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxAukerakoak, 832, 16);
	gtk_widget_set_size_request (eventboxAukerakoak, 208, 272);
	gtk_label_set_ellipsize(GTK_LABEL(lblAukerakoak), PANGO_ELLIPSIZE_START);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxAukerakoak, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblAukerakoak, GTK_STATE_NORMAL, &kolorea);
	
	eventboxAKopuruak = gtk_event_box_new();
	lblAKopuruak = gtk_label_new ("");
	gtk_container_add(GTK_CONTAINER(eventboxAKopuruak), lblAKopuruak);
	gtk_widget_show_all (eventboxAKopuruak);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxAKopuruak, 1048, 16);
	gtk_widget_set_size_request (eventboxAKopuruak, 40, 272);
	gtk_label_set_justify(GTK_LABEL(lblAKopuruak), GTK_JUSTIFY_RIGHT);
	gtk_label_set_ellipsize(GTK_LABEL(lblAKopuruak), PANGO_ELLIPSIZE_END);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxAKopuruak, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblAKopuruak, GTK_STATE_NORMAL, &kolorea);
	
	vseparator1 = gtk_vseparator_new ();
	gtk_widget_show (vseparator1);
	gtk_fixed_put (GTK_FIXED (fixed), vseparator1, 1088, 16);
	gtk_widget_set_size_request (vseparator1, 16, 272);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(vseparator1, GTK_STATE_NORMAL, &kolorea);
	
	eventboxAGuztira = gtk_event_box_new();
	lblAGuztira = gtk_label_new ("");
	gtk_container_add(GTK_CONTAINER(eventboxAGuztira), lblAGuztira);
	gtk_widget_show_all (eventboxAGuztira);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxAGuztira, 1104, 16);
	gtk_widget_set_size_request (eventboxAGuztira, 80, 272);
	gtk_label_set_justify(GTK_LABEL(lblAGuztira), GTK_JUSTIFY_RIGHT);
	gtk_label_set_ellipsize(GTK_LABEL(lblAGuztira), PANGO_ELLIPSIZE_END);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxAGuztira, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblAGuztira, GTK_STATE_NORMAL, &kolorea);
	
	hseparator1 = gtk_hseparator_new ();
	gtk_widget_show (hseparator1);
	gtk_fixed_put (GTK_FIXED (fixed), hseparator1, 832, 288);
	gtk_widget_set_size_request (hseparator1, 352, 16);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(hseparator1, GTK_STATE_NORMAL, &kolorea);

	eventboxGAtalean = gtk_event_box_new();
	lblGAtalean = gtk_label_new ("<span size='x-large'>Atalean:</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblGAtalean), TRUE);
	gtk_container_add(GTK_CONTAINER(eventboxGAtalean), lblGAtalean);
	gtk_widget_show_all (eventboxGAtalean);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxGAtalean, 832, 304);
	gtk_widget_set_size_request (eventboxGAtalean, 256, 32);
	gtk_label_set_ellipsize (GTK_LABEL (lblGAtalean), PANGO_ELLIPSIZE_START);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxGAtalean, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblGAtalean, GTK_STATE_NORMAL, &kolorea);
	
	eventboxGuztira = gtk_event_box_new();
	lblGuztira = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(eventboxGuztira), lblGuztira);
	gtk_widget_show_all (eventboxGuztira);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxGuztira, 1104, 304);
	gtk_widget_set_size_request (eventboxGuztira, 80, 32);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxGuztira, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblGuztira, GTK_STATE_NORMAL, &kolorea);
	
	eventboxLabel1 = gtk_event_box_new();
	label1 = gtk_label_new ("<span size='x-large'>GUZTIRA:</span>");
	gtk_label_set_use_markup(GTK_LABEL(label1), TRUE);
	gtk_container_add(GTK_CONTAINER(eventboxLabel1), label1);
	gtk_widget_show_all (eventboxLabel1);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxLabel1, 832, 344);
	gtk_widget_set_size_request (eventboxLabel1, 256, 32);
	gtk_label_set_ellipsize (GTK_LABEL (label1), PANGO_ELLIPSIZE_START);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxLabel1, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(label1, GTK_STATE_NORMAL, &kolorea);
	
	eventboxKGuztira=gtk_event_box_new();
	lblKGuztira = gtk_label_new ("");
	gtk_container_add(GTK_CONTAINER(eventboxKGuztira), lblKGuztira);
	gtk_widget_show_all (eventboxKGuztira);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxKGuztira, 1104, 344);
	gtk_widget_set_size_request (eventboxKGuztira, 80, 32);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventboxKGuztira, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblKGuztira, GTK_STATE_NORMAL, &kolorea);
	
	/* Kontsumitutako kopurua adierazteko "kalkulagailua" sortu eta sartu */
	frameKalkulagailua = gtk_frame_new (NULL);
	gdk_color_parse("#858484", &kolorea);
	gtk_widget_modify_bg(frameKalkulagailua, GTK_STATE_NORMAL, &kolorea);
	gtk_fixed_put (GTK_FIXED (fixed), frameKalkulagailua, 832, 384);
	gtk_widget_set_size_request (frameKalkulagailua, 352, 336);
	gtk_frame_set_shadow_type (GTK_FRAME (frameKalkulagailua), GTK_SHADOW_NONE);

	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment);
	gtk_container_add (GTK_CONTAINER (frameKalkulagailua), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 6, 6, 6, 6);

	taula = gtk_table_new (10, 5, TRUE);
	gtk_widget_show (taula);
	gtk_container_add (GTK_CONTAINER (alignment), taula);
	gtk_table_set_row_spacings (GTK_TABLE (taula), 4);
	gtk_table_set_col_spacings (GTK_TABLE (taula), 4);
	
		/* Kalkulagailuaren elementuak sartu */
		txtKopurua = gtk_entry_new ();
		gtk_widget_show (txtKopurua);
		gtk_table_attach (GTK_TABLE (taula), txtKopurua, 0, 5, 0, 2,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_FILL), 0, 0);
		gtk_entry_set_invisible_char (GTK_ENTRY (txtKopurua), 9679);

		labela = gtk_label_new("<span size='x-large'>-</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia12 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia12), labela);
		gtk_widget_show (cmdZenbakia12);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia12, 3, 5, 5, 8,
				(GtkAttachOptions) (GTK_FILL),
				(GtkAttachOptions) (GTK_FILL), 0, 0);
		zenb = "-";
		g_signal_connect(G_OBJECT(cmdZenbakia12), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);
		gdk_color_parse("#fdb5d5", &kolorea);
		gtk_widget_modify_bg(cmdZenbakia12, GTK_STATE_NORMAL, &kolorea);
		gtk_widget_modify_bg(cmdZenbakia12, GTK_STATE_PRELIGHT, &kolorea);

		labela = gtk_label_new("<span size='x-large'>3</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia3 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia3), labela);
		gtk_widget_show (cmdZenbakia3);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia3, 2, 3, 6, 8,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "3";
		g_signal_connect(G_OBJECT(cmdZenbakia3), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);

		labela = gtk_label_new("<span size='x-large'>2</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia2 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia2), labela);
		gtk_widget_show (cmdZenbakia2);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia2, 1, 2, 6, 8,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "2";
		g_signal_connect(G_OBJECT(cmdZenbakia2), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);

		labela = gtk_label_new("<span size='x-large'>1</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia1 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia1), labela);
		gtk_widget_show (cmdZenbakia1);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia1, 0, 1, 6, 8,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "1";
		g_signal_connect(G_OBJECT(cmdZenbakia1), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);

		labela = gtk_label_new("<span size='x-large'>4</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia4 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia4), labela);
		gtk_widget_show (cmdZenbakia4);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia4, 0, 1, 4, 6,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "4";
		g_signal_connect(G_OBJECT(cmdZenbakia4), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);

		labela = gtk_label_new("<span size='x-large'>5</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia5 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia5), labela);
		gtk_widget_show (cmdZenbakia5);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia5, 1, 2, 4, 6,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "5";
		g_signal_connect(G_OBJECT(cmdZenbakia5), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);

		labela = gtk_label_new("<span size='x-large'>6</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia6 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia6), labela);
		gtk_widget_show (cmdZenbakia6);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia6, 2, 3, 4, 6,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "6";
		g_signal_connect(G_OBJECT(cmdZenbakia6), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);

		labela = gtk_label_new("<span size='x-large'>9</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia9 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia9), labela);
		gtk_widget_show (cmdZenbakia9);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia9, 2, 3, 2, 4,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "9";
		g_signal_connect(G_OBJECT(cmdZenbakia9), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);
		
		labela = gtk_label_new("<span size='x-large'>8</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia8 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia8), labela);
		gtk_widget_show (cmdZenbakia8);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia8, 1, 2, 2, 4,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "8";
		g_signal_connect(G_OBJECT(cmdZenbakia8), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);
		
		labela = gtk_label_new("<span size='x-large'>7</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia7 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia7), labela);
		gtk_widget_show (cmdZenbakia7);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia7, 0, 1, 2, 4,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "7";
		g_signal_connect(G_OBJECT(cmdZenbakia7), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);

		labela = gtk_label_new("<span size='x-large'>DEL</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia10 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia10), labela);
		gtk_widget_show (cmdZenbakia10);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia10, 1, 5, 8, 10,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "DEL";
		g_signal_connect(G_OBJECT(cmdZenbakia10), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);
		
		labela = gtk_label_new("<span size='x-large'>0</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia0 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia0), labela);
		gtk_widget_show (cmdZenbakia0);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia0, 0, 1, 8, 10,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "0";
		g_signal_connect(G_OBJECT(cmdZenbakia0), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);
		
		labela = gtk_label_new("<span size='x-large'>+</span>");
		gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
		cmdZenbakia11 = gtk_button_new();
		gtk_container_add(GTK_CONTAINER(cmdZenbakia11), labela);
		gtk_widget_show (cmdZenbakia11);
		gtk_table_attach (GTK_TABLE (taula), cmdZenbakia11, 3, 5, 2, 5,
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
				(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
		zenb = "+";
		g_signal_connect(G_OBJECT(cmdZenbakia11), "clicked",
				G_CALLBACK(btmZenbakia), (gpointer) zenb);
		gdk_color_parse("#bff9ed", &kolorea);
		gtk_widget_modify_bg(cmdZenbakia11, GTK_STATE_NORMAL, &kolorea);
		gtk_widget_modify_bg(cmdZenbakia11, GTK_STATE_PRELIGHT, &kolorea);

	/* Aurrera jarraitzeko labela sortu eta sartu */
	eventboxKontuaEgin = gtk_event_box_new ();
	gdk_color_parse("#dcdcf9", &kolorea);
	gtk_widget_modify_bg(eventboxKontuaEgin, GTK_STATE_NORMAL, &kolorea);
	g_signal_connect(G_OBJECT(eventboxKontuaEgin), "button_press_event",
			G_CALLBACK(btmHurrengoa), NULL);
	gtk_widget_show (eventboxKontuaEgin);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxKontuaEgin, 16, 760);
	gtk_widget_set_size_request (eventboxKontuaEgin, 200, 56);
	lblKontuaEgin = gtk_label_new ("<span size='x-large'>Hurrengoa</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblKontuaEgin), TRUE);
	gdk_color_parse("#02026a", &kolorea);
	gtk_widget_modify_fg(lblKontuaEgin, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_show (lblKontuaEgin);
	gtk_container_add (GTK_CONTAINER (eventboxKontuaEgin), lblKontuaEgin);
	gtk_widget_set_size_request (lblKontuaEgin, 200, 56);
	
	/* Kontua uzteko labela sortu eta sartu */
	eventboxKontuaUtzi = gtk_event_box_new ();
	gdk_color_parse("#f1c2a5", &kolorea);
	gtk_widget_modify_bg(eventboxKontuaUtzi, GTK_STATE_NORMAL, &kolorea);
	g_signal_connect(G_OBJECT(eventboxKontuaUtzi), "button_press_event",
			G_CALLBACK(btmKontuaUtzi), NULL);
	gtk_widget_show (eventboxKontuaUtzi);
	gtk_fixed_put (GTK_FIXED (fixed), eventboxKontuaUtzi, 971, 760);
	gtk_widget_set_size_request (eventboxKontuaUtzi, 200, 56);
	lblAtzera = gtk_label_new ("<span size='x-large'>Kontua Utzi</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblAtzera), TRUE);
	gdk_color_parse("#02026a", &kolorea);
	gtk_widget_modify_fg(lblAtzera, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_show (lblAtzera);
	gtk_container_add (GTK_CONTAINER (eventboxKontuaUtzi), lblAtzera);
	gtk_widget_set_size_request (lblAtzera, 200, 56);
	
	/* Uneko bazkidearen zenbakia eta izena agertzeko labela sortu eta sartu */
	lblIzena = gtk_label_new ("label73");
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblIzena, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_show (lblIzena);
	gtk_fixed_put (GTK_FIXED (fixed), lblIzena, 272, 760);
	gtk_widget_set_size_request (lblIzena, 632, 56);

	/* Lehioa erakutsi eta martxan jarri */
	form_load();

	gtk_widget_show (frmAukerak);

	gtk_main();
}
