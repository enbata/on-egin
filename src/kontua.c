#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include "modSarrera.h"
#include "ordainketa.h"
#include "bestelakoak.h"

	GtkWidget *lblKopuruak, *lblKultur, *lblBatura, *lblGaiak, *lblKultura, *lblSartu, *lblGuztira, *lblGuz, *lblElkartekoa, *lblZenbatElk, *lblGuztiraOsoa, *lblBakoitzakOsoa, *lblBestelakoak, *lblTituluak, *labelaGuztira, *labelaBestelakoak, *labelaBGuztira, *labelaBBakoitzak;
	GtkWidget *eventboxEGora, *eventboxEBehera, *eventboxGehi, *eventboxKen, *eventbox, *eventboxOGora, *eventboxOBehera, *eventboxSartu, *eventboxKanpokoakInprimatu;
	GtkWidget *imgEGora, *imgEBehera, *imgGehi, *imgKen, *imgOGora, *imgOBehera;
	GtkWidget *irudia;
	GtkWidget *btmInprimatu, *btmAtzera, *btmGorde;
	GtkWidget *fixed;
	GtkWidget *marra;

elem *vKontua;
int index;
double dKultura, dGuztira, dGuztiraFijoa, dBaturaOsoa;

void egokitu()
{
	GdkScreen *lehioa = gtk_window_get_screen(GTK_WINDOW(frmAukerak));
	gint BenetakoLuzera = gdk_screen_get_height(lehioa);
	gint BenetakoZabalera = gdk_screen_get_width(lehioa);

	/* Elkarteko gastuen aldea egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), lblElkartekoa, BenetakoZabalera*0.15, BenetakoLuzera*0.01);
	gtk_widget_set_size_request (lblElkartekoa, BenetakoZabalera*0.2, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxEGora, BenetakoZabalera*0.3, BenetakoLuzera*0.06);
	gtk_widget_set_size_request (eventboxEGora, BenetakoZabalera*0.16, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblGaiak, BenetakoZabalera*0.1, BenetakoLuzera*0.11);
	gtk_widget_set_size_request (lblGaiak, BenetakoZabalera*0.2, BenetakoLuzera*0.64);

	gtk_fixed_move (GTK_FIXED (fixed), lblKopuruak, BenetakoZabalera*0.3, BenetakoLuzera*0.11);
	gtk_widget_set_size_request (lblKopuruak, BenetakoZabalera*0.08, BenetakoLuzera*0.64);

	gtk_fixed_move (GTK_FIXED (fixed), lblGuztira, BenetakoZabalera*0.38, BenetakoLuzera*0.11);
	gtk_widget_set_size_request (lblGuztira, BenetakoZabalera*0.08, BenetakoLuzera*0.64);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxEBehera, BenetakoZabalera*0.3, BenetakoLuzera*0.75);
	gtk_widget_set_size_request (eventboxEBehera, BenetakoZabalera*0.16, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblKultura, BenetakoZabalera*0.1, BenetakoLuzera*0.8);
	gtk_widget_set_size_request (lblKultura, BenetakoZabalera*0.2, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblKultur, BenetakoZabalera*0.3, BenetakoLuzera*0.8);
	gtk_widget_set_size_request (lblKultur, BenetakoZabalera*0.08, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxGehi, BenetakoZabalera*0.38, BenetakoLuzera*0.8);
	gtk_widget_set_size_request (eventboxGehi, BenetakoZabalera*0.08, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), labelaGuztira, BenetakoZabalera*0.1, BenetakoLuzera*0.85);
	gtk_widget_set_size_request (labelaGuztira, BenetakoZabalera*0.2, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblBatura, BenetakoZabalera*0.3, BenetakoLuzera*0.85);
	gtk_widget_set_size_request (lblBatura, BenetakoZabalera*0.08, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxKen, BenetakoZabalera*0.38, BenetakoLuzera*0.85);
	gtk_widget_set_size_request (eventboxKen, BenetakoZabalera*0.08, BenetakoLuzera*0.05);

	/* Bi aldeak bereizteko marra egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), marra, BenetakoZabalera*0.475, BenetakoLuzera*0);
	gtk_widget_set_size_request (marra, BenetakoZabalera*0.08, BenetakoLuzera);

	/* Bestelako gastuen aldea egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), labelaBestelakoak, BenetakoZabalera*0.65, BenetakoLuzera*0.01);
	gtk_widget_set_size_request (labelaBestelakoak, BenetakoZabalera*0.2, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxSartu, BenetakoZabalera*0.65, BenetakoLuzera*0.06);
	gtk_widget_set_size_request (eventboxSartu, BenetakoZabalera*0.2, BenetakoLuzera*0.1);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxOGora, BenetakoZabalera*0.74, BenetakoLuzera*0.16);
	gtk_widget_set_size_request (eventboxOGora, BenetakoZabalera*0.16, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblGuz, BenetakoZabalera*0.54, BenetakoLuzera*0.21);
	gtk_widget_set_size_request (lblGuz, BenetakoZabalera*0.25, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblZenbatElk, BenetakoZabalera*0.79, BenetakoLuzera*0.21);
	gtk_widget_set_size_request (lblZenbatElk, BenetakoZabalera*0.1, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblTituluak, BenetakoZabalera*0.54, BenetakoLuzera*0.26);
	gtk_widget_set_size_request (lblTituluak, BenetakoZabalera*0.25, BenetakoLuzera*0.49);

	gtk_fixed_move (GTK_FIXED (fixed), lblBestelakoak, BenetakoZabalera*0.79, BenetakoLuzera*0.26);
	gtk_widget_set_size_request (lblBestelakoak, BenetakoZabalera*0.1, BenetakoLuzera*0.49);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxOBehera, BenetakoZabalera*0.74, BenetakoLuzera*0.75);
	gtk_widget_set_size_request (eventboxOBehera, BenetakoZabalera*0.16, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), labelaBGuztira, BenetakoZabalera*0.54, BenetakoLuzera*0.8);
	gtk_widget_set_size_request (labelaBGuztira, BenetakoZabalera*0.2, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblGuztiraOsoa, BenetakoZabalera*0.74, BenetakoLuzera*0.8);
	gtk_widget_set_size_request (lblGuztiraOsoa, BenetakoZabalera*0.08, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), labelaBBakoitzak, BenetakoZabalera*0.54, BenetakoLuzera*0.85);
	gtk_widget_set_size_request (labelaBBakoitzak, BenetakoZabalera*0.2, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), lblBakoitzakOsoa, BenetakoZabalera*0.74, BenetakoLuzera*0.85);
	gtk_widget_set_size_request (lblBakoitzakOsoa, BenetakoZabalera*0.08, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), eventboxKanpokoakInprimatu , BenetakoZabalera*0.82, BenetakoLuzera*0.82);
	gtk_widget_set_size_request (eventboxKanpokoakInprimatu , BenetakoZabalera*0.04, BenetakoLuzera*0.04);

	/* Ekintza botoiak egokitu */
	gtk_fixed_move (GTK_FIXED (fixed), btmAtzera, BenetakoZabalera*0.01, BenetakoLuzera*0.92);
	gtk_widget_set_size_request (btmAtzera, BenetakoZabalera*0.23, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), btmInprimatu, BenetakoZabalera*0.26, BenetakoLuzera*0.92);
	gtk_widget_set_size_request (btmInprimatu, BenetakoZabalera*0.23, BenetakoLuzera*0.05);

	gtk_fixed_move (GTK_FIXED (fixed), btmGorde, BenetakoZabalera*0.76, BenetakoLuzera*0.92);
	gtk_widget_set_size_request (btmGorde, BenetakoZabalera*0.23, BenetakoLuzera*0.05);
}

void KontuaEgin()
{
	MYSQL_ROW row,row2;
	int aukeraHonetan, kop, kont, i;
	double batura;
	char sql[300];

	vKontua = (elem *) malloc (0*sizeof(elem));

	i=0;
	index=0;
	batura=0;
	mysql_data_seek(rstAukerak, 0);
	while ((row=mysql_fetch_row(rstAukerak))!=NULL)
	{
		aukeraHonetan=0;
		sprintf(sql, "SELECT count(*) from Gaiak,Elkartea where Elkartea.Gaikodea = Gaiak.GKodea AND Gaiak.AKodea = %d", atoi(row[2]));
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_store_result(dbElkartea);
		row2 = mysql_fetch_row(rstGaiak);
		kop=atoi(row2[0]);

		gaia *lag;
		lag = arrGaiak[i];
		int k;
		for (k=0; k<kop; k++)
			if (lag[k].Zenbat!=0)
			{
				if (aukeraHonetan==0)
				{
					vKontua = realloc(vKontua, (index+1)*sizeof(elem));
					strcpy(vKontua[index].Izena, row[0]);
					vKontua[index].Zenbat=0;
					vKontua[index].Prezioa=0;
					vKontua[index].Guztira=0;
					index++;
					aukeraHonetan=1;
				}
				vKontua = realloc(vKontua, (index+1)*sizeof(elem));
				strcpy(vKontua[index].Izena, lag[k].Izena);
				vKontua[index].Zenbat = lag[k].Zenbat;
				vKontua[index].Prezioa=lag[k].Prezioa;
				vKontua[index].Guztira = lag[k].Zenbat * lag[k].Prezioa;
				batura = batura + lag[k].Zenbat * lag[k].Prezioa;
				index++;
			}
		i++;
	}
	dKultura=0;
	dGuztira=batura;
	dGuztiraFijoa=batura;
}

void KalkulatuDatuak()
{
	//lblKultur eta lblBatura aktualizatu. dKultura eta dGuztira erabiliz hurrenez hurren
	char guztira[50];
	char testua[500];
	sprintf(guztira, "<span size='x-large'>%.2f</span>", dKultura);
	gtk_label_set_text(GTK_LABEL(lblKultur), guztira);
	gtk_label_set_use_markup(GTK_LABEL(lblKultur), TRUE);
	sprintf(guztira, "<span size='x-large'>%.2f</span>", dGuztira);
	gtk_label_set_text(GTK_LABEL(lblBatura), guztira);
	gtk_label_set_text(GTK_LABEL(lblZenbatElk), gtk_label_get_text(GTK_LABEL(lblBatura)));
	gtk_label_set_use_markup(GTK_LABEL(lblBatura), TRUE);
	gtk_label_set_use_markup(GTK_LABEL(lblZenbatElk), TRUE);
	//intOIndizea -ren arabera, lblTituluak eta lblBestelakoak bete (vKanpokoak erabili, kanpoko gastuen bektorea)
	int i;
	dBaturaOsoa = dGuztira;
	gtk_label_set_text(GTK_LABEL(lblTituluak), "");
	gtk_label_set_text(GTK_LABEL(lblBestelakoak), "");
	for (i=1; i<vKanpokoak[0].kopurua; i++)
	{
		dBaturaOsoa = dBaturaOsoa + vKanpokoak[i].kopurua;
		sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblTituluak)));
		sprintf(guztira, "%d . Erosketa", i);
		strcat(testua, guztira);
		strcat(testua, "\n</span>");
		gtk_label_set_text(GTK_LABEL(lblTituluak), testua);
		gtk_label_set_use_markup(GTK_LABEL(lblTituluak), TRUE);
		sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblBestelakoak)));
		sprintf(guztira, "%.2f", vKanpokoak[i].kopurua);
		strcat(testua, guztira);
		strcat(testua, "\n</span>");
		gtk_label_set_text(GTK_LABEL(lblBestelakoak), testua);
		gtk_label_set_use_markup(GTK_LABEL(lblBestelakoak), TRUE);
	}
	//lblGuztiraOsoa eta lblBakoitzakOsoa bete
	sprintf(guztira, "<span size='x-large'>%.2f</span>", dBaturaOsoa);
	gtk_label_set_text(GTK_LABEL(lblGuztiraOsoa), guztira);
	gtk_label_set_use_markup(GTK_LABEL(lblGuztiraOsoa), TRUE);
	sprintf(guztira, "<span size='x-large'>%.2f</span>", dBaturaOsoa/kanpokoakZenbat);
	gtk_label_set_text(GTK_LABEL(lblBakoitzakOsoa), guztira);
	gtk_label_set_use_markup(GTK_LABEL(lblBakoitzakOsoa), TRUE);
}

void KontuaBete()
{
	//intEIndizearen arabera datuak kargatu lblGaiak, lblKopuruak eta lblGuztiran

	gtk_label_set_text(GTK_LABEL(lblGaiak), "");
	gtk_label_set_text(GTK_LABEL(lblKopuruak), "");
	gtk_label_set_text(GTK_LABEL(lblGuztira), "");
	int i;
	for (i=0; i<index; i++)
	{
		if (vKontua[i].Zenbat==0)
		{
			char testua[500];
			sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblGaiak)));
			strcat (testua, vKontua[i].Izena);
			strcat (testua, "\n</span>");
			gtk_label_set_text(GTK_LABEL(lblGaiak), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblGaiak), TRUE);
			sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblKopuruak)));
			strcat (testua, "\n</span>");
			gtk_label_set_text(GTK_LABEL(lblKopuruak), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblKopuruak), TRUE);
			sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblGuztira)));
			strcat (testua, "\n</span>");
			gtk_label_set_text(GTK_LABEL(lblGuztira), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblGuztira), TRUE);
		}
		else
		{
			char testua[500];
			char denera[50];
			sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblGaiak)));
			strcat (testua, " -");
			strcat (testua, vKontua[i].Izena);
			strcat (testua, "\n</span>");
			gtk_label_set_text(GTK_LABEL(lblGaiak), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblGaiak), TRUE);
			sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblKopuruak)));
			sprintf(denera, "%d", vKontua[i].Zenbat);
			strcat (testua, denera);
			strcat (testua, "\n</span>");
			gtk_label_set_text(GTK_LABEL(lblKopuruak), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblKopuruak), TRUE);
			sprintf(testua, "<span size='x-large'>%s", gtk_label_get_text(GTK_LABEL(lblGuztira)));
			sprintf(denera, "%.2f", vKontua[i].Guztira);
			strcat (testua, denera);
			strcat (testua, "\n</span>");
			gtk_label_set_text(GTK_LABEL(lblGuztira), testua);
			gtk_label_set_use_markup(GTK_LABEL(lblGuztira), TRUE);
		}
	}
}

static void form_load()
{
	/* Lehioko osagaiak uneko pantailaren bereizmenera egokitu */
	egokitu();
	/* Kanpoko gastuak gordetzeko bektorea hasieratu, 0 gastu daudela adieraziz. kanpokoakZenbat ere hasieratu*/
	vKanpokoak = (kanp *) malloc (sizeof(kanp));
	vKanpokoak[0].kopurua=0;
	kanpokoakZenbat=1;
	/* Beharrezko datuak kargatu eta azaldu */
	KontuaEgin();
	KalkulatuDatuak();
	KontuaBete();
}

static void btmGehi()
{
	char g[50];
	sprintf(g, "%.2f", dGuztira);
	if ((dGuztira- atoi(g))<0.5)
		dGuztira = (double)atoi(g) + 0.5;
	else
		dGuztira = (double)atoi(g) + 1;
	dKultura = dGuztira - dGuztiraFijoa;
	KalkulatuDatuak();
}

static void btmKen()
{
	if (dKultura <= 0.5)
	{
		dKultura = 0;
		dGuztira = dGuztiraFijoa;
	}
	else
	{
		dKultura = dKultura - 0.5;
		dGuztira = dGuztira - 0.5;
	}
	KalkulatuDatuak();
}

static void btmInprimatu_clicked()
{
	/* Ordainketa mota lortu */
	ordainketa();
	/* cmdGorde erabilgarri jarri eta Kontua inprimatu */
	gtk_widget_set_sensitive (btmGorde, TRUE);
	KontuaInprimatu(vKontua, index, dKultura);
}

static void btmAtzera_clicked()
{
// 	free(vKontua);
	gtk_widget_show(frmAukerak);
	gtk_widget_destroy(frmKontua);
}

static void btmGorde_clicked()
{
	/* Kontu berriaren datuak gorde */
	KontuaGorde();
	/* Datuak deskargatu eta sarrerako pantaila erakutsi */
	mysql_free_result(rstAukerak);
	free(arrAukerak);
	free(arrGaiak);
	free(arrGaia);
	free(vKontua);
	gtk_widget_show(frmElkarteGastronomikoa);
	gtk_widget_destroy(frmAukerak);
	gtk_widget_destroy(frmKontua);
}

KontuaGorde()
{
	MYSQL_ROW row, row2;
	int i, kop, berria;
	char sql[500];

	/* dKultura != 0 bada, Kultura taulan lerro berri bat sartu */

	/* Egindako kontuaren datuak datu basean sartu */
	mysql_query(dbElkartea, "Select MAX(KKodea) from Kontuak");
	rstDatuak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstDatuak);
	if (row[0]!=NULL)
		berria = atoi(row[0])+1;
	else
		berria = 0;
	mysql_free_result(rstDatuak);

	mysql_data_seek(rstAukerak, 0);
	i=0;
	while ((row=mysql_fetch_row(rstAukerak))!=NULL)
	{
		sprintf(sql, "SELECT count(*) from Gaiak,Elkartea where Elkartea.Gaikodea = Gaiak.GKodea AND Gaiak.AKodea = %d", atoi(row[2]));
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_store_result(dbElkartea);
		row2 = mysql_fetch_row(rstGaiak);
		kop=atoi(row2[0]);

		gaia *lag;
		lag = arrGaiak[i];
		int k;
		for (k=0; k<kop; k++)
			if (lag[k].Zenbat!=0)
			{
				sprintf(sql, "insert into Kontuak values (%d, %d, %d, %d, %d, CURDATE(), 'KONTUA', '%s')", berria, unekoBazkidea, lag[k].Kodea, lag[k].AKodea, lag[k].Zenbat, sOrdainModua);
				mysql_query(dbElkartea, sql);
				sprintf(sql, "Update Elkartea set Kopurua = Kopurua - %d where Gaikodea = %d and Gaikodea in (Select GKodea from Gaiak where Materiala)", lag[k].Zenbat, lag[k].Kodea);
				mysql_query(dbElkartea, sql);
			}
		mysql_free_result(rstGaiak);
		i++;
	}
}

static void btmSartu()
{
	bestelakoak();
	KalkulatuDatuak();
}

static void btmKanpokoakInprimatu()
{
	kanpokoakInprimatu(dGuztira);
}

void kontua()
{
	GtkWidget *image;
	GtkWidget *labela;
	GtkWidget *hbox;
	GtkWidget *alignment;

	/* Lehioa sortu eta konfiguratu */
	frmKontua = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_decorated (GTK_WINDOW (frmKontua), FALSE);
	gtk_window_fullscreen(GTK_WINDOW(frmKontua));
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(frmKontua, GTK_STATE_NORMAL, &kolorea);

	/* Lehioaren barneko egitura sortu */
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frmKontua), fixed);

	/* Elkarteko gastuen aldea osatu */
	lblKopuruak = gtk_label_new ("lblKopuruak");
	gtk_fixed_put (GTK_FIXED (fixed), lblKopuruak, 304, 96);
	gtk_widget_set_size_request (lblKopuruak, 32, 336);

	lblKultur = gtk_label_new ("0");
	gtk_fixed_put (GTK_FIXED (fixed), lblKultur, 256, 520);
	gtk_widget_set_size_request (lblKultur, 72, 40);
	gtk_label_set_justify (GTK_LABEL (lblKultur), GTK_JUSTIFY_RIGHT);
	gtk_label_set_ellipsize (GTK_LABEL (lblKultur), PANGO_ELLIPSIZE_END);

	lblBatura = gtk_label_new ("43,5");
	gtk_fixed_put (GTK_FIXED (fixed), lblBatura, 256, 560);
	gtk_widget_set_size_request (lblBatura, 72, 40);
	gtk_label_set_justify (GTK_LABEL (lblBatura), GTK_JUSTIFY_RIGHT);
	gtk_label_set_ellipsize (GTK_LABEL (lblBatura), PANGO_ELLIPSIZE_END);

	lblGaiak = gtk_label_new ("lblGaiak");
	gtk_fixed_put (GTK_FIXED (fixed), lblGaiak, 64, 96);
	gtk_widget_set_size_request (lblGaiak, 232, 336);
	gtk_label_set_ellipsize (GTK_LABEL (lblGaiak), PANGO_ELLIPSIZE_START);

	lblKultura = gtk_label_new ("<span size='x-large'>Kultur ekintzetarako:</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblKultura), TRUE);
	gtk_fixed_put (GTK_FIXED (fixed), lblKultura, 64, 520);
	gtk_widget_set_size_request (lblKultura, 176, 40);
	gtk_label_set_ellipsize (GTK_LABEL (lblKultura), PANGO_ELLIPSIZE_START);

	labelaGuztira = gtk_label_new ("<span size='x-large'>GUZTIRA:</span>");
	gtk_label_set_use_markup(GTK_LABEL(labelaGuztira), TRUE);
	gtk_fixed_put (GTK_FIXED (fixed), labelaGuztira, 64, 560);
	gtk_widget_set_size_request (labelaGuztira, 176, 40);
	gtk_label_set_ellipsize (GTK_LABEL (labelaGuztira), PANGO_ELLIPSIZE_START);

	eventboxEGora = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxEGora, 296, 48);
	gtk_widget_set_size_request (eventboxEGora, 96, 48);
	imgEGora = gtk_image_new_from_stock ("gtk-go-up", GTK_ICON_SIZE_BUTTON);
	gtk_container_add (GTK_CONTAINER (eventboxEGora), imgEGora);
	gtk_widget_set_size_request (imgEGora, 96, 48);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxEGora, GTK_STATE_NORMAL, &kolorea);

	eventboxEBehera = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxEBehera, 296, 432);
	gtk_widget_set_size_request (eventboxEBehera, 88, 56);
	imgEBehera = gtk_image_new_from_stock ("gtk-go-down", GTK_ICON_SIZE_BUTTON);
	gtk_container_add (GTK_CONTAINER (eventboxEBehera), imgEBehera);
	gtk_widget_set_size_request (imgEBehera, 88, 56);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxEBehera, GTK_STATE_NORMAL, &kolorea);

	eventboxGehi = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxGehi, 344, 520);
	gtk_widget_set_size_request (eventboxGehi, 48, 40);
	imgGehi = gtk_image_new_from_icon_name ("stock_up", GTK_ICON_SIZE_BUTTON);
	gtk_container_add (GTK_CONTAINER (eventboxGehi), imgGehi);
	gtk_widget_set_size_request (imgGehi, 48, 40);
	g_signal_connect(G_OBJECT(eventboxGehi), "button_press_event",
			G_CALLBACK(btmGehi), NULL);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxGehi, GTK_STATE_NORMAL, &kolorea);

	eventboxKen = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxKen, 344, 560);
	gtk_widget_set_size_request (eventboxKen, 48, 40);
	imgKen = gtk_image_new_from_icon_name ("stock_down", GTK_ICON_SIZE_BUTTON);
	gtk_container_add (GTK_CONTAINER (eventboxKen), imgKen);
	gtk_widget_set_size_request (imgKen, 48, 40);
	g_signal_connect(G_OBJECT(eventboxKen), "button_press_event",
			G_CALLBACK(btmKen), NULL);
	gtk_widget_modify_bg(eventboxKen, GTK_STATE_NORMAL, &kolorea);

	lblElkartekoa = gtk_label_new ("<span underline='single' size='xx-large'>KONTUA</span>");
	gtk_fixed_put (GTK_FIXED (fixed), lblElkartekoa, 160, 16);
	gtk_widget_set_size_request (lblElkartekoa, 160, 32);
	gtk_label_set_use_markup (GTK_LABEL (lblElkartekoa), TRUE);

	marra = gtk_vseparator_new();
	gtk_fixed_put (GTK_FIXED (fixed), marra, 345, 561);
	gtk_widget_set_size_request (marra, 5, 5);

	/* Bestelako gastuen aldea osatu */
	labelaBestelakoak = gtk_label_new ("<span underline='single' size='xx-large'>Bestelakoak</span>");
	gtk_fixed_put (GTK_FIXED (fixed), labelaBestelakoak, 560, 16);
	gtk_widget_set_size_request (labelaBestelakoak, 160, 32);
	gtk_label_set_use_markup (GTK_LABEL (labelaBestelakoak), TRUE);

	eventboxSartu = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxSartu, 568, 64);
	gtk_widget_set_size_request (eventboxSartu, 146, 52);
	lblSartu = gtk_label_new ("<span size='xx-large'><b>SARTU</b></span>\n <span size='large'>Klikatu hemen elkartetik\n kanpoko gastuak sartzeko.</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblSartu), TRUE);
	gtk_label_set_justify(GTK_LABEL(lblSartu), GTK_JUSTIFY_CENTER);
	gtk_container_add (GTK_CONTAINER (eventboxSartu), lblSartu);
	gtk_widget_set_size_request (lblSartu, 146, 52);
	g_signal_connect(G_OBJECT(eventboxSartu), "button_press_event",
			G_CALLBACK(btmSartu), NULL);
	gdk_color_parse("#e3e0e0", &kolorea);
	gtk_widget_modify_bg(eventboxSartu, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_fg(lblSartu, GTK_STATE_NORMAL, &kolorea);

	lblGuztira = gtk_label_new ("lblGuztira");
	gtk_fixed_put (GTK_FIXED (fixed), lblGuztira, 344, 96);
	gtk_widget_set_size_request (lblGuztira, 32, 336);

	lblGuz = gtk_label_new ("<span size='x-large'>Elkarteko gastua</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblGuz), TRUE);
	gtk_fixed_put (GTK_FIXED (fixed), lblGuz, 472, 168);
	gtk_widget_set_size_request (lblGuz, 208, 24);
	gtk_label_set_ellipsize (GTK_LABEL (lblGuz), PANGO_ELLIPSIZE_START);

	lblZenbatElk = gtk_label_new ("43,5");
	gtk_fixed_put (GTK_FIXED (fixed), lblZenbatElk, 696, 168);
	gtk_widget_set_size_request (lblZenbatElk, 72, 24);
	gtk_label_set_justify (GTK_LABEL (lblZenbatElk), GTK_JUSTIFY_RIGHT);
	gtk_label_set_ellipsize (GTK_LABEL (lblZenbatElk), PANGO_ELLIPSIZE_END);

	labelaBGuztira = gtk_label_new ("<span size='x-large'>GUZTIRA:</span>");
	gtk_label_set_use_markup(GTK_LABEL(labelaBGuztira), TRUE);
	gtk_fixed_put (GTK_FIXED (fixed), labelaBGuztira, 464, 528);
	gtk_widget_set_size_request (labelaBGuztira, 200, 32);
	gtk_label_set_ellipsize (GTK_LABEL (labelaBGuztira), PANGO_ELLIPSIZE_START);

	labelaBBakoitzak = gtk_label_new ("<span size='x-large'>BAKOITZAK:</span>");
	gtk_label_set_use_markup(GTK_LABEL(labelaBBakoitzak), TRUE);
	gtk_fixed_put (GTK_FIXED (fixed), labelaBBakoitzak, 464, 560);
	gtk_widget_set_size_request (labelaBBakoitzak, 200, 32);
	gtk_label_set_ellipsize (GTK_LABEL (labelaBBakoitzak), PANGO_ELLIPSIZE_START);

	lblGuztiraOsoa = gtk_label_new ("lblGuztiraOsoa");
	gtk_fixed_put (GTK_FIXED (fixed), lblGuztiraOsoa, 672, 528);
	gtk_widget_set_size_request (lblGuztiraOsoa, 48, 32);

	lblBakoitzakOsoa = gtk_label_new ("lblBakoitzakOsoa");
	gtk_fixed_put (GTK_FIXED (fixed), lblBakoitzakOsoa, 672, 560);
	gtk_widget_set_size_request (lblBakoitzakOsoa, 56, 32);

	/**************** kanpoko gaien kontua ez da inprimatuko!!!
	eventboxKanpokoakInprimatu = gtk_event_box_new();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxKanpokoakInprimatu, 744, 536);
	gtk_widget_set_size_request (eventboxKanpokoakInprimatu, 48, 40);
	irudia = gtk_image_new_from_stock ("gtk-print", GTK_ICON_SIZE_BUTTON);
	gtk_container_add(GTK_CONTAINER(eventboxKanpokoakInprimatu), irudia);
	gtk_widget_set_size_request (irudia, 48, 40);
	g_signal_connect(G_OBJECT(eventboxKanpokoakInprimatu), "button_press_event",
			G_CALLBACK(btmKanpokoakInprimatu), NULL);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_bg(eventboxKanpokoakInprimatu, GTK_STATE_NORMAL, &kolorea);
	*************************/

	eventboxOGora = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxOGora, 704, 112);
	gtk_widget_set_size_request (eventboxOGora, 96, 48);
	imgOGora = gtk_image_new_from_stock ("gtk-go-up", GTK_ICON_SIZE_BUTTON);
	gtk_container_add (GTK_CONTAINER (eventboxOGora), imgOGora);
	gtk_widget_set_size_request (imgOGora, 96, 48);
	gtk_widget_modify_bg(eventboxOGora, GTK_STATE_NORMAL, &kolorea);

	eventboxOBehera = gtk_event_box_new ();
	gtk_fixed_put (GTK_FIXED (fixed), eventboxOBehera, 704, 469);
	gtk_widget_set_size_request (eventboxOBehera, 88, 56);
	imgOBehera = gtk_image_new_from_stock ("gtk-go-down", GTK_ICON_SIZE_BUTTON);
	gtk_container_add (GTK_CONTAINER (eventboxOBehera), imgOBehera);
	gtk_widget_set_size_request (imgOBehera, 88, 56);
	gtk_widget_modify_bg(eventboxOBehera, GTK_STATE_NORMAL, &kolorea);

	lblTituluak = gtk_label_new ("lblTituluak");
	gtk_fixed_put (GTK_FIXED (fixed), lblTituluak, 464, 200);
	gtk_widget_set_size_request (lblTituluak, 216, 264);
	gtk_label_set_ellipsize (GTK_LABEL (lblTituluak), PANGO_ELLIPSIZE_START);

	lblBestelakoak = gtk_label_new ("lblBestelakoak");
	gtk_fixed_put (GTK_FIXED (fixed), lblBestelakoak, 696, 216);
	gtk_widget_set_size_request (lblBestelakoak, 72, 248);
	gtk_label_set_justify (GTK_LABEL (lblBestelakoak), GTK_JUSTIFY_RIGHT);
	gtk_label_set_ellipsize (GTK_LABEL (lblBestelakoak), PANGO_ELLIPSIZE_END);


	/* Hiru ekintza botoiak sortu eta sartu */
	btmInprimatu = gtk_button_new ();
	gtk_fixed_put (GTK_FIXED (fixed), btmInprimatu, 208, 640);
	gtk_widget_set_size_request (btmInprimatu, 144, 48);
	alignment = gtk_alignment_new (0.5, 0.5, 0, 0);
	gtk_container_add (GTK_CONTAINER (btmInprimatu), alignment);
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_container_add (GTK_CONTAINER (alignment), hbox);
	labela = gtk_label_new ("Kontua    ");
	gtk_box_pack_start (GTK_BOX (hbox), labela, FALSE, FALSE, 0);
	image = gtk_image_new_from_stock ("gtk-print", GTK_ICON_SIZE_BUTTON);
	gtk_box_pack_start (GTK_BOX (hbox), image, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(btmInprimatu), "clicked",
			G_CALLBACK(btmInprimatu_clicked), NULL);

	btmAtzera = gtk_button_new_with_label ("<< Atzera");
	gtk_fixed_put (GTK_FIXED (fixed), btmAtzera, 24, 640);
	gtk_widget_set_size_request (btmAtzera, 144, 48);
	g_signal_connect(G_OBJECT(btmAtzera), "clicked",
			G_CALLBACK(btmAtzera_clicked), NULL);

	btmGorde = gtk_button_new_with_label ("Bukatu");
	gtk_fixed_put (GTK_FIXED (fixed), btmGorde, 656, 640);
	gtk_widget_set_size_request (btmGorde, 144, 48);
	gtk_widget_set_sensitive (btmGorde, FALSE);
	g_signal_connect(G_OBJECT(btmGorde), "clicked",
			G_CALLBACK(btmGorde_clicked), NULL);

	/* Datuak kargatu */
	form_load();

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmKontua);
}
