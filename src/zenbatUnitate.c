#include <gtk/gtk.h>
#include "modSarrera.h"

	static GtkWidget *testua, *labelIzena;
	static int zenbat;

static void form_load(gchar *izena, int kop)
{
	char kopurua[5];
	sprintf (kopurua, "%d", kop);
	gtk_entry_set_text(testua, kopurua);
	gtk_label_set_text(labelIzena, izena);
}

static void btmUtzi()
{
	gtk_main_quit();
	gtk_widget_destroy(frmZenbatUnitate);
}

static void btmAdos(GtkWidget *botoia, gpointer *lista)
{
	GtkTreeModel *model;
	GtkTreeIter iter;

	if (zenbat == atoi(gtk_entry_get_text(testua)))
	{
		// mezua, ez dagoela faltarik esanaz
		GtkWidget *mezua = gtk_message_dialog_new(frmZenbatUnitate,
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Kopuru bera da. Ez dago faltarik.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
	else
	{
		int aldea = atoi(gtk_entry_get_text(testua))-zenbat;
		model = gtk_tree_view_get_model(lista);
		gtk_tree_store_append (model, &iter, NULL);
		gtk_tree_store_set(model, &iter,
					0, gtk_label_get_text(labelIzena),
					1, aldea,
					-1);
		// Kopuruaren zeinuaren arabera kolorea aldatu behar!!!
		
	}
	gtk_main_quit();
	gtk_widget_destroy(frmZenbatUnitate);
}

void zenbatUnitate(char *izena, int kop, gpointer lista)
{
	GtkWidget *frame;
	GtkWidget *alignment;
	GtkWidget *fixed;
	GtkWidget *labela;
	GtkWidget *botoia;
	
	/* Leihoa sortu eta konfiguratu */
	frmZenbatUnitate = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmZenbatUnitate), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmZenbatUnitate), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmZenbatUnitate), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmZenbatUnitate), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (frmZenbatUnitate, frmFaltakEguneratu);
	
	/* Leihoaren egitura sortu */
	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (frmZenbatUnitate), frame);
	labela = gtk_label_new ("<b>Elkartea</b>");
	gtk_frame_set_label_widget (GTK_FRAME (frame), labela);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (alignment), fixed);
	
	labelIzena = gtk_label_new ("label29");
	gtk_fixed_put (GTK_FIXED (fixed), labelIzena, 16, 16);
	gtk_widget_set_size_request (labelIzena, 352, 24);
	
	testua = gtk_entry_new ();
	gtk_fixed_put (GTK_FIXED (fixed), testua, 144, 88);
	gtk_widget_set_size_request (testua, 104, 24);
	gtk_entry_set_invisible_char (GTK_ENTRY (testua), 9679);
	
	labela = gtk_label_new ("Zenbat unitate daude benetan?");
	gtk_fixed_put (GTK_FIXED (fixed), labela, 88, 56);
	gtk_widget_set_size_request (labela, 216, 24);
	
	botoia = gtk_button_new_with_label("Utzi");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmUtzi), NULL);
	gtk_fixed_put (GTK_FIXED (fixed), botoia, 96, 136);
	gtk_widget_set_size_request (botoia, 80, 40);
	
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), (gpointer) lista);
	gtk_fixed_put (GTK_FIXED (fixed), botoia, 208, 136);
	gtk_widget_set_size_request (botoia, 80, 40);
	
	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmZenbatUnitate);

	form_load(izena, kop);
	zenbat = kop;

	gtk_main();
}