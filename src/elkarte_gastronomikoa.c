#include <gtk/gtk.h>
#include "sarrera_aukera.h"
#include "kodea.h"
#include "modSarrera.h"

int egoera = 0;

static void label1_click ()
{	
	if (egoera == 0) egoera = 1;
	else egoera = 0;
}

static void label2_click ()
{
	if (egoera == 1) egoera = 2;
	else egoera = 0;
}

static void label3_click ()
{
	if (egoera == 2) egoera = 3;
	else egoera = 0;
}

static void label4_click ()
{
	if (egoera == 3) SarreraAukera();
	egoera = 0;
}

static void btmTaula()
{
	egoera =0;
}

static void btmInfo()
{
	kredituak();
}

int main( int argc, char *argv[])
{
	GtkWidget *taula;
	GtkWidget *botoia;
	GtkWidget *label;
	GtkWidget *irudia;
	GtkWidget *event_box;
	GdkColor kolorea;
	gchar *text;
	gchar *testua;
	PangoAttrList *attrs;

	gtk_init (&argc, &argv);

	/* Lehioa definitu */
	frmElkarteGastronomikoa = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_fullscreen (GTK_WINDOW(frmElkarteGastronomikoa));
	gtk_window_set_decorated(GTK_WINDOW(frmElkarteGastronomikoa),FALSE);
	gdk_color_parse ("#0000A0", &kolorea);
	gtk_widget_modify_bg (frmElkarteGastronomikoa, GTK_STATE_NORMAL, &kolorea);

	/* Widget-ak lehilan kokatzeko taula sortu eta lehioan sartu */
	taula = gtk_table_new (8,6,TRUE);
	gtk_container_add(GTK_CONTAINER(frmElkarteGastronomikoa),taula);

	/* Label -ak sartu */

		/* Label1: */
		label = gtk_label_new("");
		event_box = gtk_event_box_new();
		gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &kolorea);
		gtk_table_attach_defaults (GTK_TABLE(taula), event_box, 0, 1, 0, 1);
		gtk_container_add (GTK_CONTAINER(event_box),label);
		gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
		g_signal_connect (G_OBJECT (event_box), "button_press_event",
			G_CALLBACK (label1_click), NULL);
	
		/* Label2: */
		label = gtk_label_new("");
		event_box = gtk_event_box_new();
		gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &kolorea);
		gtk_table_attach_defaults (GTK_TABLE(taula), event_box, 5, 6, 0, 1);
		gtk_container_add (GTK_CONTAINER(event_box),label);
		gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
		g_signal_connect (G_OBJECT (event_box), "button_press_event",
			G_CALLBACK (label2_click), NULL);
	
		/* Label3: */
		label = gtk_label_new("");
		event_box = gtk_event_box_new();
		gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &kolorea);
		gtk_table_attach_defaults (GTK_TABLE(taula), event_box, 5, 6, 7, 8);
		gtk_container_add (GTK_CONTAINER(event_box),label);
		gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
		g_signal_connect (G_OBJECT (event_box), "button_press_event",
			G_CALLBACK (label3_click), NULL);
	
		/* Label4: */
		label = gtk_label_new("");
		event_box = gtk_event_box_new();
		gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL, &kolorea);
		gtk_table_attach_defaults (GTK_TABLE(taula), event_box, 0, 1, 7, 8);
		gtk_container_add (GTK_CONTAINER(event_box),label);
		gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
		g_signal_connect (G_OBJECT (event_box), "button_press_event",
			G_CALLBACK (label4_click), NULL);

	/* Irudia sortu eta sartu */
	irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/logoa.png");
	gtk_widget_set_size_request (irudia, 225, 225);
	gtk_table_attach_defaults (GTK_TABLE(taula), irudia, 0, 6, 0, 6);

	/* Ekin!! labela sortu eta sartu taulan */
	label = gtk_label_new ("<span size='xx-large'><b>Ekin!!</b></span>");
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	event_box = gtk_event_box_new();
	gdk_color_parse ("#00AA00", &kolorea);
	gtk_widget_modify_bg (event_box, GTK_STATE_NORMAL ,&kolorea);
	gdk_color_parse ("yellow", &kolorea);
	gtk_widget_modify_fg (label, GTK_STATE_NORMAL ,&kolorea);
	gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
	g_signal_connect(G_OBJECT(event_box), "button_press_event",
			G_CALLBACK(kodea),NULL);
	gtk_widget_set_size_request(event_box, 200, 50);
	gtk_table_attach (GTK_TABLE(taula), event_box, 2, 4, 6, 7,GTK_EXPAND,GTK_EXPAND,0,0);
	gtk_container_add (GTK_CONTAINER(event_box), label);

	/* Informazioa botoia sortu eta sartu */
	botoia = gtk_button_new();
	irudia = gtk_image_new_from_file ("/usr/local/share/elkarte_gastronomikoa/irudiak/info.png");
	gtk_container_add (GTK_CONTAINER(botoia), irudia);
	/*botoia = gtk_button_new_from_stock ("gtk-info");*/
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmInfo),NULL);
	gtk_widget_set_size_request(botoia, 50, 50);
	gtk_table_attach (GTK_TABLE(taula), botoia, 4, 5, 6, 7,GTK_EXPAND,GTK_EXPAND,0,0);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmElkarteGastronomikoa);

		/* Datu basearekin konexio ezarri, bektoreak kargatu... */
		BalioakKargatuEusk();

	gtk_main();
	return (0);
}
