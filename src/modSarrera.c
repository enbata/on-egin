#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <unistd.h>
#define true 1
#define false 0
#include "faltak.h"

GtkWidget *frmElkarteGastronomikoa, *frmIrten, *frmSarreraAukera, *frmAdministraria, *frmPasahitza, *frmKontuaUtzi, *frmBazkideak, *frmElkartea, *frmHornitzaileak, *frmAldatu, *frmKonfigurazioOrokorra, *frmAukeraSartu, *frmSartuGaia, *frmBodeganSartu, *frmBodegatikElkartera, *frmKendu, *frmMugitu, *frmGehiagoSartu, *frmGaiBerriaSartu, *frmFaltakEguneratu, *frmZenbatUnitate, *frmFaltenGestioa, *frmKodea, *frmFaltak, *frmFaltatikZenbat, *frmAukerak, *frmKontua, *frmOrdainketa, *frmBestelakoak, *frmGaldera, *frmKredituak;
MYSQL *dbElkartea;
MYSQL_RES *rstBazkideak, *rstDatuak, *rstHornitzaileak, *rstAukerak, *rstGaiak, *rstElkartea, *rstFaltak, *rstKontuak;
int unekoBazkidea, menpekoduna, kanpokoakZenbat, bazkideKop, ezBazkideKop;
char unekoIzena[100];
int faltaKop;
GdkColor kolorea;
char sOrdainModua[100];

typedef struct faltaBat
{
	int kodea;
	int kopurua;
	double prezioa;
} faltaBat;

faltaBat faltenBufferra[10];

typedef struct gaia
{
	char Izena[60];
	int AKodea;
	double Prezioa;
	int Zenbat;
	int Menpekotasuna;
	int Kodea;
} gaia;

typedef struct elem
{
	char Izena[60];
	int Zenbat;
	double Prezioa;
	double Guztira;
} elem;

typedef struct kanp
{
	double kopurua;
} kanp;

char **arrAukerak;
gaia *arrGaia;
gaia **arrGaiak;

kanp *vKanpokoak;

void BalioakKargatuEusk()
{
	GtkWidget *dialog;
	
	char *server = "localhost";
	char *user = "elkartea";
	char *password = "";
	char *database = "elkarte_gastronomikoa";
	
	dbElkartea = mysql_init(NULL);
	
	if (!mysql_real_connect(dbElkartea, server,
		user, password, database, 0, NULL, 0)) {
		dialog = gtk_message_dialog_new(GTK_WINDOW(frmElkarteGastronomikoa),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_ERROR,
						GTK_BUTTONS_CLOSE,
						"Arazoa izan da datu basearekin konektatzerakoan!!\n\n \tZihurtatu MySql zerbitzaria martxan dagoela eta elkarte_gastronomikoa izeneko datu basea sortuta");
		gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy (dialog);
		exit (0);
	}

}

void Hasi()
{
	BalioakKargatuEusk();
}

void elkarteaInprimatu()
{
	MYSQL_ROW row, row2;
	char sql[300];

	/* *.html fitxategi bat sortuko dugu gero berau inprimatzeko "lpr" komandoa erabiliz */
	mysql_query(dbElkartea, "Select * from Elkartea");
	rstDatuak = mysql_use_result(dbElkartea);
	if ((row = mysql_fetch_row(rstDatuak))!=NULL)
	{
		mysql_free_result(rstDatuak);
		FILE *fitxategia;
		fitxategia = fopen("/tmp/inprimatu.html", "w");
		fprintf(fitxategia, "<html>\n<body>\n<br><br>\n<img src=/usr/local/share/elkarte_gastronomikoa/irudiak/logoa.gif>\n");
		fprintf(fitxategia, "<b><u><center>Elkarteko gaiak</center></u></b>\n<br><br><br>\n", NULL);
		mysql_query(dbElkartea, "Select CURDATE()");
		rstDatuak = mysql_use_result(dbElkartea);
		row = mysql_fetch_row(rstDatuak);
		fprintf(fitxategia, "<b>Eguna	</b>%s\n", row[0]);
		mysql_free_result(rstDatuak);
		fprintf(fitxategia, "<br><br>\n", NULL);
		mysql_query (dbElkartea, "Select * from Aukerak ORDER BY AOrdena");
		rstAukerak = mysql_store_result(dbElkartea);
		fprintf(fitxategia, "<table width=750 cellspacing=0 frame=border rules=rows>\n", NULL);
		while ((row=mysql_fetch_row(rstAukerak))!=NULL)
		{
			fprintf(fitxategia, "<tr bgcolor=#000000><td><font color=#ffffff><b><h3>%s</h3></b></font></td><td></td></tr>\n", row[0]);
			char sql[500];
			sprintf (sql, "Select Gizenaeus, Kopurua from Gaiak, Elkartea where Gaiak.GKodea = Elkartea.Gaikodea and AKodea=%d ORDER BY GOrdena", atoi(row[2]));
			mysql_query(dbElkartea, sql);
			rstDatuak = mysql_store_result(dbElkartea);
			while ((row2=mysql_fetch_row(rstDatuak))!=NULL)
			{
				fprintf(fitxategia, "<tr bgcolor=#dcdcde><td>%s</td><td align=right>%d</td></tr>\n", row2[0], atoi(row2[1]));
			}
			mysql_free_result(rstDatuak);
		}
		fprintf(fitxategia, "</table>\n</body>\n</html>");
		mysql_free_result(rstAukerak);
		fclose(fitxategia);
		/* Sortutako fitxategia inprimatuko dugu */
		int pid,pfd[2];
		pipe(pfd);
		pid=fork();
		if (pid==0)
		{
			close(1);
			dup(pfd[1]);
			close(pfd[0]);close(pfd[1]);
			execlp("html2ps","html2ps", "/tmp/inprimatu.html",NULL);
		}
		pid=fork();
		if (pid==0)
		{
			close(0);
			dup(pfd[0]);
			close(pfd[0]);close(pfd[1]);
			execlp("lpr","lpr",NULL);
		}
		close(pfd[0]);
		close(pfd[1]);
	}
	else
	{
		mysql_free_result(rstDatuak);		
		// mezua, ez dagoela ezer inprimatzeko esanaz!
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmFaltakEguneratu),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dago ezer inprimatzeko.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
}

void TratatuFaltak()
{
	char sql[500];
	MYSQL_ROW row;

	//Faltak kargatu, ea bazkide hori egon den egunetan faltarik dagoen ikusteko
	sprintf(sql, "SELECT DISTINCT Faltak.FKodea,Faltak.GKodea,Faltak.GKopurua,Faltak.DAurrekoa,Faltak.DAzkena,Gaiak.GPrezioa,Gaiak.Gizenaeus FROM Faltak,Gaiak,Kontuak WHERE Kontuak.BKodea = %d AND Faltak.GKopurua < 0 AND Faltak.DAurrekoa <= Kontuak.Data AND Kontuak.Data <= Faltak.DAzkena AND Faltak.Gkodea = Gaiak.Gkodea AND Kontuak.KMota = 'KONTUA' ORDER BY Faltak.Daurrekoa,Gaiak.Gizenaeus", unekoBazkidea);
	mysql_query(dbElkartea, sql);
	rstDatuak = mysql_store_result(dbElkartea);
	if ((row=mysql_fetch_row(rstDatuak))!=NULL)
	{
		faltenBufferra[0].kopurua=0;
		faltak();
	}
	mysql_free_result(rstDatuak);
}

void faltenKontuaInprimatu()
{
	char sql[500];
	MYSQL_ROW row;

	// faltenBufferra bektoreko datuak erabiliz falten faktura bat inprimatu
	mysql_query(dbElkartea, "Delete from FaltaPrint");
	int i;
	for (i=0; i<10; i++)
	{
		if (faltenBufferra[i].kopurua!=0)
		{
			sprintf (sql, "Select Aizenaeus, AOrdena, Gizenaeus, GOrdena from Aukerak, Gaiak where Aukerak.AKodea = Gaiak.AKodea and GKodea=%d", faltenBufferra[i].kodea);
			mysql_query(dbElkartea, sql);
			rstGaiak = mysql_store_result(dbElkartea);
			row = mysql_fetch_row(rstGaiak);
			char prezioa[20];
			sprintf(prezioa, "%.2f", faltenBufferra[i].prezioa);
			sprintf (sql, "Insert into FaltaPrint(Aukera, Gaia, Kopurua, Prezioa, AOrdena, GOrdena) values ('%s','%s',%d,'%s',%d,%d)",row[0],row[2],faltenBufferra[i].kopurua, prezioa, atoi(row[1]), atoi(row[3]));
			mysql_query(dbElkartea, sql);
			mysql_free_result(rstGaiak);
		}
	}

	FILE *fitxategia;
	fitxategia = fopen("/tmp/inprimatu.html", "w");
	fprintf(fitxategia, "<html>\n<body>\n<br><br>\n<img src=/usr/local/share/elkarte_gastronomikoa/irudiak/logoa.gif>\n");
	fprintf(fitxategia, "<center><b><u>Falten kontua</u></b></center>\n<br><br><br>\n");
	sprintf(sql, "Select Izena, Abizena1, Abizena2 from Bazkideak where Zenbakia2=%d", unekoBazkidea);
	mysql_query(dbElkartea, sql);
	rstBazkideak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstBazkideak);
	fprintf(fitxategia, "<b>Bazkidea</b>  %s %s, %s\n<br>\n", row[1], row[2], row[0]);
	mysql_free_result(rstBazkideak);
	mysql_query(dbElkartea, "select CURDATE()");
	rstBazkideak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstBazkideak);
	fprintf(fitxategia, "<b>Eguna</b>  %s\n<br><br>\n", row[0]);
	mysql_free_result(rstBazkideak);

	mysql_query(dbElkartea, "Select Aukera, Gaia, Kopurua, Prezioa from FaltaPrint group by Aukera order by AOrdena, GOrdena");
	rstGaiak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstGaiak);
	char aukera[20];
	sprintf(aukera, "%s", row[0]);
	fprintf(fitxategia, "<table width=750 cellspacing=5 frame=hsides rules=rows>\n <th>Aukera</th><th>Gaia</th><th>Kopurua</th><th>*</th><th>Prezioa</th><th>Guztira</th>\n");
	fprintf(fitxategia, "<tr align=center><td><b>%s</b></td><td></td><td></td><td></td><td></td><td></td></tr>\n",aukera);
	double batura=0;
	do
	{
		if (strcmp(aukera,row[0])!=0)
		{
			sprintf(aukera, "%s", row[0]);
			fprintf(fitxategia, "<tr align=center><td><b>%s</b></td><td></td><td></td><td></td><td></td><td></td></tr>\n",aukera);
		}
		fprintf(fitxategia, "<tr align=center><td></td><td>%s</td><td>%d</td><td></td><td>%s</td><td>%.2f</td></tr>\n", row[1], atoi(row[2]), row[3], atoi(row[2])*atof(row[3]));
		batura=batura+(atoi(row[2])*atof(row[3]));
	} while ((row=mysql_fetch_row(rstGaiak))!=NULL);
	mysql_free_result(rstGaiak);

	fprintf(fitxategia, "</table>\n<br>\n<table align=right frame=border>\n<tr><td><b>Guztira: %.2f &euro</td></tr>\n</table></b></body>\n</html>", batura);
	fclose(fitxategia);

	// sortutako inprimatu.html fitxategia PostScript batetara pasako dugu gero inprimatu ahal izateko "lpr" erabiliz
	int pid,pfd[2];
	pipe(pfd);
	pid=fork();
	if (pid==0)
	{
		close(1);
		dup(pfd[1]);
		close(pfd[0]);close(pfd[1]);
		execlp("html2ps","html2ps", "/tmp/inprimatu.html",NULL);
	}
	pid=fork();
	if (pid==0)
	{
		close(0);
		dup(pfd[0]);
		close(pfd[0]);close(pfd[1]);
		execlp("lpr","lpr",NULL);
	}
	close(pfd[0]);
	close(pfd[1]);

	// faltenBufferra hasieratu falten beste faktura bat inprimatu ahal izateko
	faltenBufferra[0].kodea=0;
	faltenBufferra[1].kodea=0;
	faltenBufferra[2].kodea=0;
	faltenBufferra[3].kodea=0;
	faltenBufferra[4].kodea=0;
	faltenBufferra[5].kodea=0;
	faltenBufferra[6].kodea=0;
	faltenBufferra[7].kodea=0;
	faltenBufferra[8].kodea=0;
	faltenBufferra[9].kodea=0;
}

void KontuaInprimatu(elem *zerrenda, int kop, double kultura)
{
	MYSQL_ROW row;
	int i;
	double batura;
	char sql[200];

	FILE *fitxategia;
	fitxategia = fopen("/tmp/inprimatu.html", "w");
	fprintf(fitxategia, "<html>\n<body>\n<br><br>\n<img src=/usr/local/share/elkarte_gastronomikoa/irudiak/logoa.gif>\n");
	fprintf(fitxategia, "<center><b><u>Elkarterako kontua</u></b></center>\n<br><br><br>\n");
	sprintf(sql, "Select Izena, Abizena1, Abizena2 from Bazkideak where Zenbakia1=%d", unekoBazkidea);
	mysql_query(dbElkartea, sql);
	rstBazkideak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstBazkideak);
	fprintf(fitxategia, "<b>Bazkidea</b>  %s %s, %s\n<br>\n", row[1], row[2], row[0]);
	mysql_free_result(rstBazkideak);
	mysql_query(dbElkartea, "select CURDATE()");
	rstBazkideak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstBazkideak);
	fprintf(fitxategia, "<b>Eguna</b>  %s\n<br>", row[0]);
	mysql_free_result(rstBazkideak);
	fprintf(fitxategia, "<b>Ordainketa-mota</b>  %s\n<br><br>\n", sOrdainModua);

	fprintf(fitxategia, "<table width=750 cellspacing=5 frame=hsides rules=rows>\n <th>Aukera</th><th>Gaia</th><th>Kopurua</th><th>*</th><th>Prezioa</th><th>Guztira</th>\n");
	batura=0;
	for (i=0; i<kop; i++)
	{
		if (zerrenda[i].Zenbat==0)
		{
			fprintf(fitxategia, "<tr align=center><td><b>%s</b></td><td></td><td></td><td></td><td></td><td></td></tr>\n",zerrenda[i].Izena);
		}
		else
		{
			fprintf(fitxategia, "<tr align=center><td></td><td>%s</td><td>%d</td><td></td><td>%.2f</td><td>%.2f</td></tr>\n", zerrenda[i].Izena, zerrenda[i].Zenbat, zerrenda[i].Prezioa, zerrenda[i].Guztira);
			batura=batura+zerrenda[i].Guztira;
		}
	}
	fprintf(fitxategia, "</table>\n<br>\n<table align=right>\n<tr><td></td><td align=right><b>%.2f &euro</center></td></tr>\n<tr><td><b>Kultur ekintzetarako diru laguntza</b></td><td align=right><b>%.2f &euro</b></td></tr>\n</table>\n", batura, kultura);
	fprintf(fitxategia, "<table align=right frame=border>\n<tr><td><b>Guztira: %.2f &euro</td></tr>\n</table></b></body>\n</html>", batura+kultura);
	fclose(fitxategia);

	// sortutako inprimatu.html fitxategia PostScript batetara pasako dugu gero inprimatu ahal izateko "lpr" erabiliz
	int pid,pfd[2];
	pipe(pfd);
	pid=fork();
	if (pid==0)
	{
		close(1);
		dup(pfd[1]);
		close(pfd[0]);close(pfd[1]);
		execlp("html2ps","html2ps", "/tmp/inprimatu.html",NULL);
	}
	pid=fork();
	if (pid==0)
	{
		close(0);
		dup(pfd[0]);
		close(pfd[0]);close(pfd[1]);
		execlp("lpr","lpr",NULL);
	}
	close(pfd[0]);
	close(pfd[1]);
}

void kanpokoakInprimatu(double elkartekoa)
{
	
	MYSQL_ROW row;
	int i;
	double batura;
	char sql[200];

	FILE *fitxategia;
	fitxategia = fopen("/tmp/inprimatu.html", "w");
	fprintf(fitxategia, "<html>\n<body>\n<br><br>\n<img src=/usr/local/share/elkarte_gastronomikoa/irudiak/logoa.gif>\n");
	fprintf(fitxategia, "<center><b><u>Kontu osoa</u></b></center>\n<br><br><br>\n");
	sprintf(sql, "Select Izena, Abizena1, Abizena2 from Bazkideak where Zenbakia2=%d", unekoBazkidea);
	mysql_query(dbElkartea, sql);
	rstBazkideak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstBazkideak);
	fprintf(fitxategia, "<b>Bazkidea</b>  %s %s, %s\n<br>\n", row[1], row[2], row[0]);
	mysql_free_result(rstBazkideak);
	mysql_query(dbElkartea, "select CURDATE()");
	rstBazkideak = mysql_store_result(dbElkartea);
	row=mysql_fetch_row(rstBazkideak);
	fprintf(fitxategia, "<b>Eguna</b>  %s\n<br>", row[0]);
	mysql_free_result(rstBazkideak);

	fprintf(fitxategia, "<table width=750 cellspacing=5 frame=hsides rules=rows>\n <th>Gastuaren arrazoia</th><th>Zenbatekoa</th>\n");
	fprintf(fitxategia, "<tr align=center><td>Elkarteko gastuak</td><td>%.2f</td></tr>\n",elkartekoa);
	batura=elkartekoa;
	for (i=1; i<vKanpokoak[0].kopurua; i++)
	{
		fprintf(fitxategia, "<tr align=center><td>%d. erosketa</td><td>%.2f</td></tr>\n", i, vKanpokoak[i].kopurua);
		batura=batura+vKanpokoak[i].kopurua;
	}
	fprintf(fitxategia, "</table>\n<table align=right>\n<tr><td></td><td><b>Guztira:</b></td><td align=right>%.2f &euro</td></tr>\n",batura);
	fprintf(fitxategia, "<tr><td><b>%d lagun,</b></td><td><b>Bakoitzak</b></td><td align=right>%.2f &euro</td></tr>\n</table>\n</body>\n</html>", kanpokoakZenbat, batura/(kanpokoakZenbat));
	fclose(fitxategia);

	// sortutako inprimatu.html fitxategia PostScript batetara pasako dugu gero inprimatu ahal izateko "lpr" erabiliz
	int pid,pfd[2];
	pipe(pfd);
	pid=fork();
	if (pid==0)
	{
		close(1);
		dup(pfd[1]);
		close(pfd[0]);close(pfd[1]);
		execlp("html2ps","html2ps", "/tmp/inprimatu.html",NULL);
	}
	pid=fork();
	if (pid==0)
	{
		close(0);
		dup(pfd[0]);
		close(pfd[0]);close(pfd[1]);
		execlp("lpr","lpr",NULL);
	}
	close(pfd[0]);
	close(pfd[1]);
}
