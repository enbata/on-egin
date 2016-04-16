#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <string.h>
#include "administratzailea.h"
#include "modSarrera.h"


static void btmUtzi ()
{
	gtk_widget_show (GTK_WIDGET(frmElkarteGastronomikoa));
	gtk_widget_destroy (frmPasahitza);
}

static void btmAdos(GtkWidget *botoia, gpointer testua)
{
	MYSQL_RES *emaitza;
	MYSQL_ROW errenkada;
	GtkWidget *dialog;
	
	mysql_query (dbElkartea, "select Epasahitza from ElkartekoDatuak");
	emaitza=mysql_store_result(dbElkartea);
	if ((errenkada = mysql_fetch_row(emaitza)) != NULL)
	{
		if ((errenkada[0]) != NULL)
		{
			if (strcmp(gtk_entry_get_text (testua), errenkada[0])==0)
			{
				//gtk_widget_hide(frmElkarteGastronomikoa);
				gtk_widget_destroy(frmPasahitza);
				administratzailea();
			}
			else
			{
				dialog = gtk_message_dialog_new(GTK_WINDOW(frmPasahitza),
								GTK_DIALOG_MODAL,
								GTK_MESSAGE_INFO,
								GTK_BUTTONS_OK,
								"Pasahitz okerra, saiatu berriro");
				gtk_dialog_run(GTK_DIALOG(dialog));
				gtk_widget_destroy (dialog);
			}
		}
		else
		{
			//gtk_widget_hide(frmElkarteGastronomikoa);
			gtk_widget_destroy(frmPasahitza);
			administratzailea();
		}
	}
	else
	{
		//gtk_widget_hide(frmElkarteGastronomikoa);
		gtk_widget_destroy(frmPasahitza);
		administratzailea();
	}
	mysql_free_result (emaitza);
}

void pasahitza ()
{

	GtkWidget *label;
	GtkWidget *botoia;
	GtkWidget *hBox, *vBox;
	GtkWidget *taula;
	GtkWidget *frame;
	GtkWidget *txtPasahitza;
	GdkColor kolorea;


	/* frmPasahitza sortu eta hasieratu*/
	frmPasahitza = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_fullscreen (GTK_WINDOW(frmPasahitza));
	gtk_window_set_decorated (GTK_WINDOW(frmPasahitza), FALSE);
	//gtk_window_set_type_hint (GTK_WINDOW(frmPasahitza), GDK_WINDOW_TYPE_HINT_DIALOG);
	//gtk_window_set_transient_for (GTK_WINDOW(frmPasahitza), GTK_WINDOW(frmElkarteGastronomikoa));
	//gtk_window_set_position (GTK_WINDOW(frmPasahitza), GTK_WIN_POS_CENTER_ALWAYS);
	//gtk_window_set_modal (GTK_WINDOW(frmPasahitza), TRUE);
	gdk_color_parse ("#0000A0", &kolorea);
	gtk_widget_modify_bg (frmPasahitza, GTK_STATE_NORMAL, &kolorea);
	
	label = gtk_label_new("<span size='x-large'><b>PASAHITZA</b></span>");
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	frame = gtk_frame_new(NULL);
	gtk_frame_set_label_widget(GTK_FRAME(frame), label);
	gtk_container_add (GTK_CONTAINER(frmPasahitza), frame);
	vBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER(frame), vBox);

	/* Lehenengo lerroa sortu eta sartu (label-a eta testu eremua) */
	hBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, TRUE, FALSE, 10);

	label = gtk_label_new ("<span size='large'>Pasahitza: </span>");
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	gtk_box_pack_start (GTK_BOX(hBox), label, TRUE, FALSE, 0);

	/* Bigarren lerroa sortu eta sartu (testu eremua) */
	hBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, TRUE, FALSE, 10);
	txtPasahitza = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX(hBox), txtPasahitza, TRUE, FALSE, 0);

	/* bigarren lerroa sortu eta sartu (utzi eta ados botoiak) */
	hBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vBox), hBox, TRUE, FALSE, 20);
	
	botoia = gtk_button_new_with_label ("Utzi");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, FALSE, 10);
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), (gpointer) txtPasahitza);
	gtk_widget_set_size_request (GTK_WIDGET(botoia), 100, 50);
	gtk_box_pack_start (GTK_BOX(hBox), botoia, TRUE, FALSE, 10);

	/* dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmPasahitza);

}
