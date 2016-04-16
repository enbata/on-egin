#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"
#define true 1
#define false 0

	static GtkWidget *txtIzena, *txtNA, *txtAbizena1, *txtAbizena2, *txtHelbidea, *txtTelefonoa1, *txtTelefonoa2, *txtPK, *txtHerria, *txtEmaila, *txtJaiotzeData, *txtZenbakia1, *txtZenbakia2, *txtKontuZenbakia;
	static GtkWidget *checkJubilatua;
	static GtkWidget *hBoxBilaketa;
	static GtkWidget *konboa;
	int Berria;
	int pos=0;

	MYSQL_ROW errenkada;
	GtkWidget *dialog;

void PantailaBete()
{
	if (pos == mysql_num_rows(rstBazkideak)) pos = mysql_num_rows(rstBazkideak)-1;
	if (pos == -1) pos = 0;
	mysql_data_seek (rstBazkideak, pos);
	if ((errenkada = mysql_fetch_row (rstBazkideak)) == NULL)
	{
		/*dialog = gtk_message_dialog_new(frmBazkideak,
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dago Bazkiderik");
		gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy (dialog);*/
		
		gtk_entry_set_text (GTK_ENTRY(txtZenbakia1), "");
		gtk_entry_set_text (GTK_ENTRY(txtZenbakia2), "");
		gtk_entry_set_text (GTK_ENTRY(txtAbizena1), "");
		gtk_entry_set_text (GTK_ENTRY(txtAbizena2), "");
		gtk_entry_set_text (GTK_ENTRY(txtEmaila), "");
		gtk_entry_set_text (GTK_ENTRY(txtHelbidea), "");
		gtk_entry_set_text (GTK_ENTRY(txtHerria), "");
		gtk_entry_set_text (GTK_ENTRY(txtIzena), "");
		gtk_entry_set_text (GTK_ENTRY(txtKontuZenbakia), "");
		gtk_entry_set_text (GTK_ENTRY(txtNA), "");
		gtk_entry_set_text (GTK_ENTRY(txtPK), "");
		gtk_entry_set_text (GTK_ENTRY(txtTelefonoa1), "");
		gtk_entry_set_text (GTK_ENTRY(txtTelefonoa2), "");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkJubilatua), FALSE);
		gtk_entry_set_text (GTK_ENTRY(txtJaiotzeData),"____/__/__");
		/*Berria= true;*/
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY(txtZenbakia1), errenkada[1]);
		gtk_entry_set_text (GTK_ENTRY(txtZenbakia2), errenkada[2]);
		gtk_entry_set_text (GTK_ENTRY(txtAbizena1), errenkada[3]);
		gtk_entry_set_text (GTK_ENTRY(txtAbizena2), errenkada[4]);
		gtk_entry_set_text (GTK_ENTRY(txtEmaila), errenkada[14]);
		gtk_entry_set_text (GTK_ENTRY(txtHelbidea), errenkada[5]);
		gtk_entry_set_text (GTK_ENTRY(txtHerria), errenkada[9]);
		gtk_entry_set_text (GTK_ENTRY(txtIzena), errenkada[0]);
		gtk_entry_set_text (GTK_ENTRY(txtKontuZenbakia), errenkada[13]);
		gtk_entry_set_text (GTK_ENTRY(txtNA), errenkada[12]);
		gtk_entry_set_text (GTK_ENTRY(txtPK), errenkada[8]);
		gtk_entry_set_text (GTK_ENTRY(txtTelefonoa1), errenkada[6]);
		gtk_entry_set_text (GTK_ENTRY(txtTelefonoa2), errenkada[7]);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkJubilatua), atoi(errenkada[10]));
		gtk_entry_set_text (GTK_ENTRY(txtJaiotzeData),errenkada[11]);
		Berria=false;
	}
}

void BilaketaHasi()
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	mysql_query (dbElkartea, "SELECT Izena,Abizena1,Abizena2,Zenbakia1 FROM Bazkideak Order by Abizena1,Abizena2,Izena");
	res = mysql_store_result (dbElkartea);
	int i=0;
	while ((row = mysql_fetch_row (res)) != NULL)
	{
		gchar esaldia[50];
		strcpy (esaldia, row[1]);
		strcat (esaldia, " ");
		strcat (esaldia,  row[2]);
		strcat (esaldia, " ");
		strcat (esaldia, row[0]);
		gtk_combo_box_remove_text (GTK_COMBO_BOX(konboa), i);
		gtk_combo_box_insert_text (GTK_COMBO_BOX(konboa), i, esaldia);
		i++;
	}
	gtk_combo_box_remove_text (GTK_COMBO_BOX(konboa), i);
	mysql_free_result(res);
}

static void form_load()
{
	mysql_query (dbElkartea, "select * from Bazkideak");
	rstBazkideak=mysql_store_result(dbElkartea);
	if ((errenkada = mysql_fetch_row(rstBazkideak)) != NULL)
	{
		Berria = false;
		PantailaBete();
	}
	else
	{
		dialog = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dago Bazkiderik");
		gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy (dialog);
		Berria = true;
		PantailaBete();
	}
}

static void btmLehenengoa()
{
	pos = 0;
	PantailaBete();
}

static void btmHurrengoa()
{
	pos++;
	PantailaBete();
}

static void btmAurrekoa()
{
	pos--;
	PantailaBete();
}

static void btmAzkenekoa()
{
	pos = mysql_num_rows(rstBazkideak)-1;
	PantailaBete();
}

static void btmBilatu()
{
	gtk_widget_show (GTK_WIDGET(hBoxBilaketa));
	BilaketaHasi();
}

int datuakKonprobatu()
{
	if ((strlen(gtk_entry_get_text(GTK_ENTRY(txtIzena))) == 0) || (strlen(gtk_entry_get_text(GTK_ENTRY(txtAbizena1))) == 0) || (strlen(gtk_entry_get_text(GTK_ENTRY(txtHelbidea))) == 0) ||  (strlen(gtk_entry_get_text(GTK_ENTRY(txtTelefonoa1))) == 0) || (strlen(gtk_entry_get_text(GTK_ENTRY(txtPK))) == 0) || (strlen(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))) == 0))
	{
		dialog = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_ERROR,
						GTK_BUTTONS_CLOSE,
						"Barkatu, uneko bazkidearen datu minimo batzuk sartzea beharrezkoa da.\n\nDatu minimoak: Izena, lehenengo abizena, lehenengo zenbakia, telefonoa, helbidea eta posta kodea.\n\nSartu derrigorrezko datu hauek eta saiatu berriz gordetzen.");
		gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy (dialog);
		return -1;
	}
	else
		return 1;
}

static void btmGorde()
{
	GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Ziur al zaude datuak gorde nahi dituzula?");
	gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
	gtk_widget_destroy (mezua);
	if (erantzuna == GTK_RESPONSE_YES)
	{
		if (datuakKonprobatu() != -1)
		{
			gchar sql[500];
			if (Berria)
			{
				sprintf (sql, "insert into Bazkideak values('%s',%d,%d,'%s','%s','%s','%s','%s','%s','%s',%d,'%s','%s','%s','%s')", gtk_entry_get_text(GTK_ENTRY(txtIzena)), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))),atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia2))), gtk_entry_get_text(GTK_ENTRY(txtAbizena1)), gtk_entry_get_text(GTK_ENTRY(txtAbizena2)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa1)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa2)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkJubilatua)), gtk_entry_get_text(GTK_ENTRY(txtJaiotzeData)),gtk_entry_get_text(GTK_ENTRY(txtNA)),gtk_entry_get_text(GTK_ENTRY(txtKontuZenbakia)),gtk_entry_get_text(GTK_ENTRY(txtEmaila)));
				int erantzuna;
				if ((erantzuna = mysql_query(dbElkartea, sql)) != 0)
				{
					mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Daturen bat ez dago ondo sartuta!\n\tKontuz datarekin! UUUU/HH/EE\n\tBeste erabiltzaileren batek eduki dezake %d zenbakia hartuta!", atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))));
					gtk_dialog_run(GTK_DIALOG(mezua));
					gtk_widget_destroy(mezua);
				}
				else
				{
					Berria=false;
					mysql_free_result(rstBazkideak);
					pos=0;
					BilaketaHasi();
					form_load();
				}
			}
			else
			{
				sprintf(sql, "update Bazkideak set Izena='%s', Zenbakia1=%d, Zenbakia2=%d, Abizena1='%s', Abizena2='%s', Helbidea='%s', Tel1='%s', Tel2='%s', PK='%s', Herria='%s', Jubilatua=%d, JData='%s', NA='%s', Kontua='%s', Emaila='%s' where Izena='%s' and Abizena1='%s'and Abizena2='%s'", gtk_entry_get_text(GTK_ENTRY(txtIzena)), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))),atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia2))), gtk_entry_get_text(GTK_ENTRY(txtAbizena1)), gtk_entry_get_text(GTK_ENTRY(txtAbizena2)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa1)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa2)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkJubilatua)), gtk_entry_get_text(GTK_ENTRY(txtJaiotzeData)), gtk_entry_get_text(GTK_ENTRY(txtNA)), gtk_entry_get_text(GTK_ENTRY(txtKontuZenbakia)), gtk_entry_get_text(GTK_ENTRY(txtEmaila)), errenkada[0], errenkada[3], errenkada[4]);
				if ((erantzuna = mysql_query(dbElkartea, sql)) != 0)
				{
					mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Daturen bat ez dago ondo sartuta!\n\tKontuz datarekin! UUUU/HH/EE\n\tBeste erabiltzaileren batek eduki dezake %d zenbakia hartuta!", atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))));
					gtk_dialog_run(GTK_DIALOG(mezua));
					gtk_widget_destroy(mezua);
				}
				else
				{
					mysql_free_result(rstBazkideak);
					BilaketaHasi();
					form_load();
				}
			}
		}
	}
}

static void btmBerria()
{
	gtk_entry_set_text (GTK_ENTRY(txtZenbakia1), "");
	gtk_entry_set_text (GTK_ENTRY(txtZenbakia2), "");
	gtk_entry_set_text (GTK_ENTRY(txtAbizena1), "");
	gtk_entry_set_text (GTK_ENTRY(txtAbizena2), "");
	gtk_entry_set_text (GTK_ENTRY(txtEmaila), "");
	gtk_entry_set_text (GTK_ENTRY(txtHelbidea), "");
	gtk_entry_set_text (GTK_ENTRY(txtHerria), "");
	gtk_entry_set_text (GTK_ENTRY(txtIzena), "");
	gtk_entry_set_text (GTK_ENTRY(txtKontuZenbakia), "");
	gtk_entry_set_text (GTK_ENTRY(txtNA), "");
	gtk_entry_set_text (GTK_ENTRY(txtPK), "");
	gtk_entry_set_text (GTK_ENTRY(txtTelefonoa1), "");
	gtk_entry_set_text (GTK_ENTRY(txtTelefonoa2), "");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkJubilatua), FALSE);
	gtk_entry_set_text (GTK_ENTRY(txtJaiotzeData),"____/__/__");
	Berria= true;
}

static void btmEzabatu()
{
	if(!Berria)
	{
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Zihur al zaude datuak ezabatu nahi dituzula?");
		gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		if (erantzuna == GTK_RESPONSE_YES)
		{
			gchar sql[300];
			sprintf (sql, "delete from Bazkideak where Izena='%s' and Abizena1='%s'and Abizena2='%s'", errenkada[0], errenkada[3], errenkada[4]);
			mysql_query (dbElkartea, sql);
			mysql_free_result (rstBazkideak);
			form_load();
		}
	}
	/* Bilaketako konboa aktualizatu, erabiltzailea kendu */
	BilaketaHasi();
}

static void btmDesegin()
{
	PantailaBete();
}

static void btmBilaketaItxi()
{
	gtk_widget_hide (GTK_WIDGET(hBoxBilaketa));
}

static void btmAdos()
{
	MYSQL_ROW row;

	mysql_data_seek (rstBazkideak, 0);
	if ((row=mysql_fetch_row(rstBazkideak))!=NULL)
	{
		if (!(  (strcmp(gtk_entry_get_text(GTK_ENTRY(txtIzena)), errenkada[0])==0) &&
			(atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1)))==atoi(errenkada[1])) &&
			(atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia2)))==atoi(errenkada[2])) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtAbizena1)), errenkada[3])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtAbizena2)), errenkada[4])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), errenkada[5])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtTelefonoa1)), errenkada[6])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtTelefonoa2)), errenkada[7])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtPK)), errenkada[8])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtHerria)), errenkada[9])==0) &&
			(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkJubilatua))==atoi(errenkada[10])) &&
			(atoi(gtk_entry_get_text(GTK_ENTRY(txtJaiotzeData)))==atoi(errenkada[11])) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtNA)), errenkada[12])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtKontuZenbakia)), errenkada[13])==0) &&
			(strcmp(gtk_entry_get_text(GTK_ENTRY(txtEmaila)), errenkada[14])==0) ))
		{
			GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Aldaketak gorde nahi al dituzu?");
			int erantzuna;
			if ((erantzuna=gtk_dialog_run(GTK_DIALOG(mezua)))==GTK_RESPONSE_YES)
			{
				gtk_widget_destroy (mezua);
				if (datuakKonprobatu() != -1)
				{
					gchar sql[500];
					if (Berria)
					{
						sprintf (sql, "insert into Bazkideak values('%s',%d,%d,'%s','%s','%s','%s','%s','%s','%s',%d,'%s','%s','%s','%s')", gtk_entry_get_text(GTK_ENTRY(txtIzena)), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))),atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia2))), gtk_entry_get_text(GTK_ENTRY(txtAbizena1)), gtk_entry_get_text(GTK_ENTRY(txtAbizena2)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa1)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa2)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkJubilatua)), gtk_entry_get_text(GTK_ENTRY(txtJaiotzeData)),gtk_entry_get_text(GTK_ENTRY(txtNA)),gtk_entry_get_text(GTK_ENTRY(txtKontuZenbakia)),gtk_entry_get_text(GTK_ENTRY(txtEmaila)));
					}
					else
					{
						sprintf(sql, "update Bazkideak set Izena='%s', Zenbakia1=%d, Zenbakia2=%d, Abizena1='%s', Abizena2='%s', Helbidea='%s', Tel1='%s', Tel2='%s', PK='%s', Herria='%s', Jubilatua=%d, JData='%s', NA='%s', Kontua='%s', Emaila='%s' where Izena='%s' and Abizena1='%s'and Abizena2='%s'", gtk_entry_get_text(GTK_ENTRY(txtIzena)), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))),atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia2))), gtk_entry_get_text(GTK_ENTRY(txtAbizena1)), gtk_entry_get_text(GTK_ENTRY(txtAbizena2)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa1)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa2)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkJubilatua)), gtk_entry_get_text(GTK_ENTRY(txtJaiotzeData)), gtk_entry_get_text(GTK_ENTRY(txtNA)), gtk_entry_get_text(GTK_ENTRY(txtKontuZenbakia)), gtk_entry_get_text(GTK_ENTRY(txtEmaila)), errenkada[0], errenkada[3], errenkada[4]);
					}
					if ((erantzuna = mysql_query(dbElkartea, sql)) != 0)
					{
						mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
							GTK_DIALOG_DESTROY_WITH_PARENT,
							GTK_MESSAGE_INFO,
							GTK_BUTTONS_OK,
							"Daturen bat ez dago ondo sartuta!\n\tKontuz datarekin! UUUU/HH/EE\n\tBeste erabiltzaileren batek eduki dezake %d zenbakia hartuta!", atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))));
						gtk_dialog_run(GTK_DIALOG(mezua));
						gtk_widget_destroy(mezua);
					}
					else
					{
						mysql_free_result(rstBazkideak);
						gtk_widget_destroy(frmBazkideak);
					}
				}
			}
			else
			{
				gtk_widget_destroy (mezua);
				mysql_free_result(rstBazkideak);
				gtk_widget_destroy(frmBazkideak);
			}
		}
		else
		{
			mysql_free_result(rstBazkideak);
			gtk_widget_destroy(frmBazkideak);
		}
	}
	else
	{
		if ( (strcmp(gtk_entry_get_text(GTK_ENTRY(txtIzena)), "")!=0) && 
		     (strcmp(gtk_entry_get_text(GTK_ENTRY(txtAbizena1)), "")!=0) && 
		     (strcmp(gtk_entry_get_text(GTK_ENTRY(txtAbizena2)), "")!=0) && 
		     (strcmp(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1)), "")) )
		{
			GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Aldaketak gorde nahi al dituzu?");
			int erantzuna;
			if ((erantzuna=gtk_dialog_run(GTK_DIALOG(mezua)))==GTK_RESPONSE_YES)
			{
				gtk_widget_destroy (mezua);
				if (datuakKonprobatu() != -1)
				{
					gchar sql[500];
					
					sprintf (sql, "insert into Bazkidzabalera*0.2,luzera*0.2eak values('%s',%d,%d,'%s','%s','%s','%s','%s','%s','%s',%d,'%s','%s','%s','%s')", gtk_entry_get_text(GTK_ENTRY(txtIzena)), atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))),atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia2))), gtk_entry_get_text(GTK_ENTRY(txtAbizena1)), gtk_entry_get_text(GTK_ENTRY(txtAbizena2)), gtk_entry_get_text(GTK_ENTRY(txtHelbidea)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa1)), gtk_entry_get_text(GTK_ENTRY(txtTelefonoa2)), gtk_entry_get_text(GTK_ENTRY(txtPK)), gtk_entry_get_text(GTK_ENTRY(txtHerria)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkJubilatua)), gtk_entry_get_text(GTK_ENTRY(txtJaiotzeData)),gtk_entry_get_text(GTK_ENTRY(txtNA)),gtk_entry_get_text(GTK_ENTRY(txtKontuZenbakia)),gtk_entry_get_text(GTK_ENTRY(txtEmaila)));
					
					if ((erantzuna = mysql_query(dbElkartea, sql)) != 0)
					{
						mezua = gtk_message_dialog_new(GTK_WINDOW(frmBazkideak),
							GTK_DIALOG_DESTROY_WITH_PARENT,
							GTK_MESSAGE_INFO,
							GTK_BUTTONS_OK,
							"Daturen bat ez dago ondo sartuta!\n\tKontuz datarekin! UUUU/HH/EE\n\tBeste erabiltzaileren batek eduki dezake %d zenbakia hartuta!", atoi(gtk_entry_get_text(GTK_ENTRY(txtZenbakia1))));
						gtk_dialog_run(GTK_DIALOG(mezua));
						gtk_widget_destroy(mezua);
					}
					else
					{
						mysql_free_result(rstBazkideak);
						gtk_widget_destroy(frmBazkideak);
					}
				}
			}
			else
			{
				mysql_free_result(rstBazkideak);
				gtk_widget_destroy(frmBazkideak);
			}
		}
		else
		{
			mysql_free_result(rstBazkideak);
			gtk_widget_destroy(frmBazkideak);
		}
	}
}

static void cmbBilaketa()
{
	gchar *bazkidea;
	bazkidea = gtk_combo_box_get_active_text (GTK_COMBO_BOX(konboa));
	mysql_data_seek (rstBazkideak, 0);
	pos=-1;
	while ((errenkada=mysql_fetch_row(rstBazkideak)) != NULL)
	{
		pos++;
		gchar esaldia[50];
		strcpy (esaldia, errenkada[3]);
		strcat (esaldia, " ");
		strcat (esaldia,  errenkada[4]);
		strcat (esaldia, " ");
		strcat (esaldia, errenkada[0]);
		if (strcmp(esaldia, bazkidea)==0) break;
	}
	PantailaBete();
}

void bazkideak()
{
	GtkWidget *hBox;
	GtkWidget *botoia;
	GtkWidget *taula;
	GtkWidget *labela;
	GtkWidget *irudia;
	GtkWidget *frame;
	GtkWidget *barra;

	/* lehioa hasieratu */
	frmBazkideak = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW(frmBazkideak), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW(frmBazkideak), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmBazkideak), GTK_WINDOW(frmAdministraria));
	gtk_window_set_position (GTK_WINDOW(frmBazkideak), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW(frmBazkideak), TRUE);

	frame = gtk_frame_new ("BAZKIDEAK");
	gtk_container_add (GTK_CONTAINER(frmBazkideak), frame);

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

	/* Bilatzeko konboa eta botoia sortu eta sartu */
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

	/* Bazkidearen datuak azaltzeko testu areak sortu eta sartu */
	frame = gtk_frame_new ("");
	gtk_table_attach_defaults (GTK_TABLE(taula), frame, 0, 10, 2, 3);
	taula = gtk_table_new (9, 8, FALSE);
	gtk_container_add (GTK_CONTAINER(frame), taula);
		/* Sortutako taula egituran elementuak sartu */
		barra = gtk_hseparator_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), barra, 0, 7, 0, 1);
		labela = gtk_label_new ("Izena");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 1, 2);
		txtIzena = gtk_entry_new();
		gtk_entry_set_max_length (GTK_ENTRY(txtIzena), 10);
		gtk_table_attach_defaults (GTK_TABLE(taula), txtIzena, 1, 2, 1, 2);
		labela = gtk_label_new("N.A.");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 1, 2);
		txtNA = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtNA, 4, 5, 1, 2);
		labela = gtk_label_new("1.abizena");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 2, 3);
		txtAbizena1 = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtAbizena1, 1, 2, 2, 3);
		labela = gtk_label_new("2.abizena");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 2, 3);
		txtAbizena2 = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtAbizena2, 4, 5, 2, 3);
		labela = gtk_label_new("Helbidea");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 3, 4);
		txtHelbidea = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtHelbidea, 1, 2, 3, 4);
		labela = gtk_label_new("1.telefonoa");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 3, 4);
		txtTelefonoa1 = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtTelefonoa1, 4, 5, 3, 4);
		labela = gtk_label_new("2.telefonoa");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 4, 5);
		txtTelefonoa2 = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtTelefonoa2, 4, 5, 4, 5);
		labela = gtk_label_new ("Posta kodea");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 5, 6);
		txtPK = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtPK, 1, 2, 5, 6);
		labela = gtk_label_new ("Herria");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 5, 6);
		txtHerria = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtHerria, 4, 5, 5, 6);
		/*labela = gtk_label_new ("Jubilatua");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 5, 6, 5, 6);*/
		checkJubilatua = gtk_check_button_new_with_label("Jubilatua");
		gtk_table_attach_defaults (GTK_TABLE(taula), checkJubilatua, 5, 6, 5, 6);
		labela = gtk_label_new ("E-maila");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 6, 7);
		txtEmaila = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtEmaila, 1, 2, 6, 7);
		labela = gtk_label_new ("Jaiotze-data");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 6, 7);
		txtJaiotzeData = gtk_entry_new();
		gtk_entry_set_text (GTK_ENTRY(txtJaiotzeData),"____/__/__");
		gtk_table_attach_defaults (GTK_TABLE(taula), txtJaiotzeData, 4, 5, 6, 7);
		labela = gtk_label_new ("1.zenbakia");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 1, 7, 8);
		txtZenbakia1 = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtZenbakia1, 1, 2, 7, 8);
		labela = gtk_label_new ("2.zenbakia");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 3, 4, 7, 8);
		txtZenbakia2 = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtZenbakia2, 4, 5, 7, 8);
		labela = gtk_label_new ("Kontu zenbakia");
		gtk_table_attach_defaults (GTK_TABLE(taula), labela, 0, 2, 8, 9);
		txtKontuZenbakia = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE(taula), txtKontuZenbakia, 3, 5, 8, 9);
	
	/* Beharrezkoa bistaratu eta gainontzekoa ixkutatu */
	gtk_widget_show_all(frmBazkideak);
	gtk_widget_hide (GTK_WIDGET(hBoxBilaketa));

	form_load();
}
