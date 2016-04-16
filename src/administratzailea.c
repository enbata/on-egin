#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"
#include "bazkideak.h"
#include "elkartea.h"
#include "hornitzaileak.h"
#include "aldatu.h"
#include "konfigurazio_orokorra.h"
#include "bodeganSartu.h"
#include "bodegatikElkartera.h"
#include "faltakEguneratu.h"
#include "faltenGestioa.h"

static void mnuIrten()
{
	gtk_main_quit();
	gtk_widget_destroy (frmAdministraria);
	gtk_widget_show (GTK_WIDGET(frmElkarteGastronomikoa));
}

static void mnuFaltenGestioa()
{
	faltenGestioa();
}

void administratzailea()
{
	GtkWidget *vBox;
	GtkWidget *menu_barra;
	GtkWidget *menu_nagusia;
	GtkWidget *menua;
	GtkWidget *menu_elementua;
	GtkWidget *barra;

	/* lehioa definitu */
	frmAdministraria = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_fullscreen (GTK_WINDOW(frmAdministraria));
	gtk_window_set_decorated (GTK_WINDOW(frmAdministraria), FALSE);
	
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER(frmAdministraria), vBox);
	
	/* Menua sortu eta sartu */
	menu_barra = gtk_menu_bar_new();
	gtk_box_pack_start (GTK_BOX(vBox), menu_barra, FALSE, FALSE, 0);
	
		/* Fitxategia menua sortu eta sartu menu_barran */
		menu_nagusia = gtk_menu_item_new_with_label ("Fitxategia");
		gtk_menu_shell_append (GTK_MENU_SHELL(menu_barra), menu_nagusia);
		menua = gtk_menu_new();
		gtk_menu_item_set_submenu (GTK_MENU_ITEM(menu_nagusia), menua);
	
			/* Irten aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Irten");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(mnuIrten), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);
	
		/* Elkartea menua sortu eta sartu menu_barran */
		menu_nagusia = gtk_menu_item_new_with_label ("Elkartea");
		gtk_menu_shell_append (GTK_MENU_SHELL(menu_barra), menu_nagusia);
		menua = gtk_menu_new();
		gtk_menu_item_set_submenu (GTK_MENU_ITEM(menu_nagusia), menua);
	
			/* Bazkideak aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Bazkideak");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(bazkideak), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);
	
			/* Elkartearen datuak aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Elkartearen datuak");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(elkartea), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);
	
			/* Hornitzaileak aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Hornitzaileak");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(hornitzaileak), frmAdministraria);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);
	
			/* Marra banatzailea sartu */
			barra = gtk_separator_menu_item_new();
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), barra);
	
			/* Elkarteko gaien konfigurazioa aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Elkarteko gaien konfigurazioa");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(konfigurazioOrokorra), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);

		/* Kontrola menua sortu eta sartu menu_barran */
		menu_nagusia = gtk_menu_item_new_with_label ("Kontrola");
		gtk_menu_shell_append (GTK_MENU_SHELL(menu_barra), menu_nagusia);
		menua = gtk_menu_new();
		gtk_menu_item_set_submenu (GTK_MENU_ITEM(menu_nagusia), menua);
	
			/* Bodegan sartu aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Bodegan sartu");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(bodeganSartu), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);
	
			/* Bodegatik elkartera aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Bodegatik elkartera");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(bodegatikElkartera), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);

			/* Marra banatzailea sartu */
			barra = gtk_separator_menu_item_new();
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), barra);
	
			/* Faltak eguneratu aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Faltak eguneratu");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(faltakEguneratu), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);
	
			/* Falten gestioa konfigurazioa aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Falten gestioa");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(mnuFaltenGestioa), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);

		/* Administraria menua sortu eta sartu menu_barran */
		menu_nagusia = gtk_menu_item_new_with_label ("Administraria");
		gtk_menu_shell_append (GTK_MENU_SHELL(menu_barra), menu_nagusia);
		menua = gtk_menu_new();
		gtk_menu_item_set_submenu (GTK_MENU_ITEM(menu_nagusia), menua);
	
			/* Pasahitza aldatu sartu aukera sartu */
			menu_elementua = gtk_menu_item_new_with_label ("Pasahitza aldatu");
			g_signal_connect_swapped(G_OBJECT(menu_elementua), "activate",
						G_CALLBACK(aldatu), NULL);
			gtk_menu_shell_append(GTK_MENU_SHELL(menua), menu_elementua);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmAdministraria);
	gtk_main();
}
