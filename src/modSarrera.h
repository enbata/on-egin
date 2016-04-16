#include <mysql/mysql.h>
#include <gtk/gtk.h>

extern GtkWidget *frmElkarteGastronomikoa, *frmIrten, *frmSarreraAukera, *frmAdministraria, *frmPasahitza, *frmKontuaUtzi, *frmBazkideak, *frmElkartea, *frmHornitzaileak, *frmAldatu, *frmKonfigurazioOrokorra, *frmAukeraSartu, *frmSartuGaia, *frmBodeganSartu, *frmBodegatikElkartera, *frmKendu, *frmMugitu, *frmGehiagoSartu, *frmGaiBerriaSartu, *frmFaltakEguneratu, *frmZenbatUnitate, *frmFaltenGestioa, *frmKodea, *frmFaltak, *frmFaltatikZenbat, *frmAukerak, *frmKontua, *frmOrdainketa, *frmBestelakoak, *frmGaldera, *frmKredituak;
extern MYSQL *dbElkartea;
extern MYSQL_RES *rstBazkideak, *rstDatuak, *rstHornitzaileak, *rstAukerak, *rstGaiak, *rstElkartea, *rstFaltak, *rstKontuak;
extern int unekoBazkidea, menpekoduna, kanpokoakZenbat, bazkideKop, ezBazkideKop;
extern char unekoIzena[100];
extern int faltaKop;
extern GdkColor kolorea;
extern char sOrdainModua[100];

extern void BalioakKargatuEusk();
extern void Hasi();
extern void elkarteaInprimatu();
extern void TratatuFaltak();
extern void KokatuFaltak();
extern void FaltakBete();
extern faltenKontuaInprimatu();
extern void kanpokoakInprimatu(double elkartekoa);

extern char * komatikPuntura(char *kop);

typedef struct faltaBat
{
	int kodea;
	int kopurua;
	double prezioa;
} faltaBat;

extern faltaBat faltenBufferra[10];

typedef struct kanp
{
	double kopurua;
} kanp;

extern kanp *vKanpokoak;

typedef struct elem
{
	char Izena[60];
	int Zenbat;
	double Prezioa;
	double Guztira;
} elem;

extern void KontuaInprimatu(elem *zerrenda, int kop, int kultura);

typedef struct gaia
{
	char Izena[60];
	int AKodea;
	double Prezioa;
	int Zenbat;
	int Menpekotasuna;
	int Kodea;
} gaia;

extern char **arrAukerak;
extern gaia *arrGaia;
extern gaia **arrGaiak;
