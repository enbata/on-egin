#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "modSarrera.h"

	static gchar *izena; 
	static int kopurua=0;

static void btmUtzi()
{
	gtk_main_quit();
	gtk_widget_destroy(frmKendu);
}

static void btmAdos(GtkWidget *botoia, gpointer testua)
{
	MYSQL_ROW row;

	char sql[300];
	gchar *zenbat = (gchar *) gtk_entry_get_text(GTK_ENTRY(testua));
	if (atoi(zenbat)<=0)
	{
		//Kopuru okerra!
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmKendu),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_ERROR,
						GTK_BUTTONS_OK,
						"Sartutako unitate kopurua ez da egokia!.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
	else
	{
		if (atoi(zenbat)>kopurua)
		{
			//Ez daude hainbeste unitate!!
			GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmKendu),
							GTK_DIALOG_MODAL,
							GTK_MESSAGE_ERROR,
							GTK_BUTTONS_OK,
							"Ez daude hainbeste unitate!.");
			gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
			gtk_dialog_run(GTK_DIALOG(mezua));
			gtk_widget_destroy (mezua);
		}
		else
		{
			sprintf(sql, "Select GKodea from Gaiak where Gizenaeus='%s'", izena);
			mysql_query(dbElkartea, sql);
			rstGaiak = mysql_store_result(dbElkartea);
			row=mysql_fetch_row(rstGaiak);
			sprintf(sql, "Update Bodega set Gaikopurua=Gaikopurua-%d where Gaikodea=%d", atoi(zenbat), atoi(row[0]));
			mysql_query(dbElkartea, sql);
			mysql_free_result(rstGaiak);

		gtk_main_quit();
		gtk_widget_destroy(frmKendu);
		}
	}
}

void kendu(gchar *aukera, int kop)
{
	GtkWidget *vBox;
	GtkWidget *hBox;
	GtkWidget *irudia;
	GtkWidget *labela;
	GtkWidget *testua;
	GtkWidget *botoia;
	GtkWidget *frame;
	GtkWidget *alignment;

	/* Lehioa sortu eta hasieratu */
	frmKendu= gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmKendu), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmKendu), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmKendu), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmKendu), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmKendu), GTK_WINDOW(frmBodegatikElkartera));

	/* Lehioaren egitura sortu eta sartu */
	frame = gtk_frame_new(NULL);
	labela = gtk_label_new("<b>Elkartea</b>");
	gtk_frame_set_label_widget (GTK_FRAME (frame), labela);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	gtk_container_add(GTK_CONTAINER(frmKendu), frame);
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 0, 24, 12, 24);
	vBox = gtk_vbox_new(TRUE, 20);
	gtk_container_add(GTK_CONTAINER(alignment), vBox);
		/* Irudia eta testua sortu eta sartu */
		hBox = gtk_hbox_new(FALSE, 5);
		botoia = gtk_button_new_with_label("Utzi");
		gtk_box_pack_start(GTK_BOX(hBox), botoia, FALSE, FALSE, 0);
		hBox = gtk_hbox_new(FALSE, 5);
		irudia = gtk_image_new_from_stock ("gtk-no", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start(GTK_BOX(hBox), irudia, FALSE, FALSE, 0);
		labela = gtk_label_new("Zenbat unitate kendu nahi dituzu?");
		gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

		/* Kopurua sartzeko testu area sortu eta sartu */
		alignment = gtk_alignment_new (0.5, 0.5, 0, 0);
		gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 0, 0, 50, 50);
		gtk_box_pack_start(GTK_BOX(vBox), alignment, FALSE, FALSE, 0);
		testua = gtk_entry_new();
// 		gtk_widget_set_size_request (testua, 100, 30);
		gtk_container_add(GTK_CONTAINER(alignment), testua);

		/* Utzi eta Ados botoiak sortu eta sartu */
		hBox = gtk_hbox_new(TRUE, 20);
		botoia = gtk_button_new_with_label("Utzi");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmUtzi), NULL);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
		botoia = gtk_button_new_with_label("Ados");
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmAdos),(gpointer) testua);
		gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	/* Dena bistaratu eta prestatu */
	gtk_widget_show_all(frmKendu);
	izena = aukera;
	kopurua = kop;

	gtk_main();

}
