#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"

	GtkWidget *lista, *txtZenbakiak, *lblZenbat;

static void form_load()
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	char kopurua[50];
	int i;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lista));
	for (i=1; i<vKanpokoak[0].kopurua; i++)
	{
		sprintf(kopurua, "%.2f", vKanpokoak[i].kopurua);
		gtk_tree_store_append (GTK_TREE_STORE(model), &iter, NULL);
		gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
				0, kopurua,
				-1);
	}
	if (kanpokoakZenbat>1)
	{
		sprintf(kopurua, "<span size='xx-large'><b> %d </b></span>", kanpokoakZenbat);
		gtk_label_set_text(GTK_LABEL(lblZenbat), kopurua);
		gtk_label_set_use_markup(GTK_LABEL(lblZenbat), TRUE);
	}
}

static void btmUtzi()
{
	gtk_main_quit();
	gtk_widget_destroy(frmBestelakoak);
}

static void btmGehitu()
{
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lista));
	if (strcmp(gtk_entry_get_text(GTK_ENTRY(txtZenbakiak)), "0")!=0)
	{
		gtk_tree_store_append (GTK_TREE_STORE(model), &iter, NULL);
		gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
				0, gtk_entry_get_text(GTK_ENTRY(txtZenbakiak)),
				-1);
		gtk_entry_set_text(GTK_ENTRY(txtZenbakiak), "0");
	}
}

static void btmKendu()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lista));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lista));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		char *kopurua;
		gtk_tree_model_get (model, &iter, 0, &kopurua, -1);
		gtk_entry_set_text(GTK_ENTRY(txtZenbakiak), kopurua);
		gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
		gtk_tree_selection_unselect_all(selection);
	}
}

static void btmGehi()
{
	char kop[50];
	int zenbat = atoi(gtk_label_get_text(GTK_LABEL(lblZenbat)));
	zenbat++;
	sprintf(kop, "<span size='xx-large'><b> %d </b></span>", zenbat);
	gtk_label_set_text(GTK_LABEL(lblZenbat), kop);
	gtk_label_set_use_markup(GTK_LABEL(lblZenbat), TRUE);
}

static void btmKen()
{
	char kop[50];
	int zenbat = atoi(gtk_label_get_text(GTK_LABEL(lblZenbat)));
	if (zenbat>1)
	{
		zenbat--;
		sprintf(kop, "<span size='xx-large'><b> %d </b></span>", zenbat);
		gtk_label_set_text(GTK_LABEL(lblZenbat), kop);
		gtk_label_set_use_markup(GTK_LABEL(lblZenbat), TRUE);
	}
}

static void btmAdos()
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	int index;
	char *kopurua;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lista));
	if (gtk_tree_model_get_iter_first(model, &iter))
	{
		vKanpokoak = (kanp *) malloc (sizeof(kanp));
		index=1;
		while (gtk_tree_model_get_iter_first(model, &iter))
		{
			vKanpokoak = realloc(vKanpokoak, (index+1)*sizeof(kanp));
			gtk_tree_model_get (model, &iter, 0, &kopurua, -1);
			vKanpokoak[index].kopurua = atof(kopurua);
			gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
			index++;
		}
		vKanpokoak[0].kopurua = index;
	}
	kanpokoakZenbat = atoi(gtk_label_get_text(GTK_LABEL(lblZenbat)));
	gtk_main_quit();
	gtk_widget_destroy(frmBestelakoak);
}

static void btmZenbakia(GtkWidget *botoia)
{
	char testua[50];
	char kopurua[50];
	sprintf(kopurua, "%s", gtk_entry_get_text(GTK_ENTRY(txtZenbakiak)));
	sprintf(testua, "%s", gtk_button_get_label(GTK_BUTTON(botoia)));

	if (strcmp(testua, "C")==0)
		gtk_entry_set_text(GTK_ENTRY(txtZenbakiak), "0");
	else
		if (strcmp(testua, ",")==0)
		{
			strcat(kopurua, ",");
			gtk_entry_set_text(GTK_ENTRY(txtZenbakiak), kopurua);
		}
		else
		{
			if (strcmp(kopurua, "0")==0)
				gtk_entry_set_text (GTK_ENTRY(GTK_ENTRY(txtZenbakiak)), testua);
			else
			{
				strcat(kopurua, testua);
				gtk_entry_set_text (GTK_ENTRY(GTK_ENTRY(txtZenbakiak)), kopurua);
			}
		}
}

void bestelakoak()
{
	GtkWidget *frame;
	GtkWidget *alignment;
	GtkWidget *fixed;
	GtkWidget *cmdGehi;
	GtkWidget *cmdKendu;
	GtkWidget *cmdAdos;
	GtkWidget *cmdUtzi;
	GtkWidget *cmdKen;
	GtkWidget *labela;
	GtkWidget *cmdGehitu;
	GtkWidget *taula;
	GtkWidget *eventbox;
	GtkWidget *cmdZenbakiak3;
	GtkWidget *cmdZenbakiak2;
	GtkWidget *cmdZenbakiak4;
	GtkWidget *cmdZenbakiak5;
	GtkWidget *cmdZenbakiak6;
	GtkWidget *cmdZenbakiak9;
	GtkWidget *cmdZenbakiak8;
	GtkWidget *cmdZenbakiak7;
	GtkWidget *cmdZenbakiak0;
	GtkWidget *cmdZenbakiak10;
	GtkWidget *cmdZenbakiak11;
	GtkWidget *cmdZenbakiak1;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	
	/* Lehioa sortu eta konfiguratu */
	frmBestelakoak = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_position (GTK_WINDOW (frmBestelakoak), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmBestelakoak), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmBestelakoak), FALSE);
	//gtk_window_set_type_hint (GTK_WINDOW (frmBestelakoak), GDK_WINDOW_TYPE_HINT_DIALOG);
	//gtk_window_set_transient_for(GTK_WINDOW(frmBestelakoak), GTK_WINDOW(frmKontua));
	
	/* Lehioaren egitura sortu eta kokatu */
	frame = gtk_frame_new ("");
	gtk_container_add (GTK_CONTAINER (frmBestelakoak), frame);
	gdk_color_parse("#e3e0e0", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (alignment), fixed);

	labela = gtk_label_new ("<span size='large'><b> Sartu zerrendan bestelako gastuak </b></span>");
	gtk_fixed_put (GTK_FIXED (fixed), labela, 0, 0);
	gtk_widget_set_size_request (labela, 312, 32);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);

	/* Kalkulagailua sortu eta kokatu */
	frame = gtk_frame_new (NULL);
	gtk_fixed_put (GTK_FIXED (fixed), frame, 0, 32);
	gdk_color_parse("#858484", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_set_size_request (frame, 250, 300);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);

	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add(GTK_CONTAINER(frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	
	taula = gtk_table_new (10, 3, TRUE);
	gtk_container_add (GTK_CONTAINER (alignment), taula);
	gtk_table_set_row_spacings (GTK_TABLE (taula), 4);
	gtk_table_set_col_spacings (GTK_TABLE (taula), 4);
	
	txtZenbakiak = gtk_entry_new ();
	gtk_table_attach (GTK_TABLE (taula), txtZenbakiak, 0, 3, 0, 2,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_FILL), 0, 0);
	gtk_entry_set_invisible_char (GTK_ENTRY (txtZenbakiak), 9679);
	gtk_entry_set_text(GTK_ENTRY(txtZenbakiak), "0");
	
	cmdZenbakiak3 = gtk_button_new_with_label("3");
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak3, 2, 3, 6, 8,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak3), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak2 = gtk_button_new_with_label("2");
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak2, 1, 2, 6, 8,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak2), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak4 = gtk_button_new_with_label("4");
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak4, 0, 1, 4, 6,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak4), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak5 = gtk_button_new_with_label("5");
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak5, 1, 2, 4, 6,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak5), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak6 = gtk_button_new_with_label("6");
	gtk_widget_show (cmdZenbakiak6);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak6, 2, 3, 4, 6,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak6), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak9 = gtk_button_new_with_label("9");
	gtk_widget_show (cmdZenbakiak9);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak9, 2, 3, 2, 4,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak9), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak8 = gtk_button_new_with_label("8");
	gtk_widget_show (cmdZenbakiak8);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak8, 1, 2, 2, 4,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak8), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak7 = gtk_button_new_with_label("7");
	gtk_widget_show (cmdZenbakiak7);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak7, 0, 1, 2, 4,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak7), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak0 = gtk_button_new_with_label("0");
	gtk_widget_show (cmdZenbakiak0);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak0, 0, 1, 8, 10,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak0), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak10 = gtk_button_new_with_label(",");
	gtk_widget_show (cmdZenbakiak10);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak10, 1, 2, 8, 10,
			(GtkAttachOptions) (GTK_FILL),
			(GtkAttachOptions) (GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak10), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak11 = gtk_button_new_with_label("C");
	gtk_widget_show (cmdZenbakiak11);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak11, 2, 3, 8, 10,
			(GtkAttachOptions) (GTK_FILL),
			(GtkAttachOptions) (GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak11), "clicked",
				G_CALLBACK(btmZenbakia), NULL);
	
	cmdZenbakiak1 = gtk_button_new_with_label("1");
	gtk_widget_show (cmdZenbakiak1);
	gtk_table_attach (GTK_TABLE (taula), cmdZenbakiak1, 0, 1, 6, 8,
			(GtkAttachOptions) (GTK_FILL),
			(GtkAttachOptions) (GTK_FILL), 0, 0);
	g_signal_connect(G_OBJECT(cmdZenbakiak1), "clicked",
				G_CALLBACK(btmZenbakia), NULL);

	labela = gtk_label_new("<span size='x-large'>>></span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	cmdGehitu = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cmdGehitu), labela);
	gtk_fixed_put (GTK_FIXED (fixed), cmdGehitu, 256, 136);
	gtk_widget_set_size_request (cmdGehitu, 96, 64);
	g_signal_connect(G_OBJECT(cmdGehitu), "clicked",
			G_CALLBACK(btmGehitu), NULL);
	
	labela = gtk_label_new("<span size='x-large'> Kendu </span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	cmdKendu = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cmdKendu), labela);
	gtk_fixed_put (GTK_FIXED (fixed), cmdKendu, 256, 216);
	gtk_widget_set_size_request (cmdKendu, 96, 64);
	g_signal_connect(G_OBJECT(cmdKendu), "clicked",
			G_CALLBACK(btmKendu), NULL);

	model = GTK_TREE_MODEL (gtk_tree_store_new(1, G_TYPE_STRING));
	lista = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lista),
					-1, "Sartutakoak", renderer,
					"text", 0,
					NULL);
	gtk_fixed_put (GTK_FIXED (fixed), lista, 368, 0);
	gtk_widget_set_size_request (lista, 208, 560);

	labela = gtk_label_new ("<span size='large'><b> Zenbat zarete ordaintzeko? </b></span>");
	gtk_fixed_put (GTK_FIXED (fixed), labela, 16, 344);
	gtk_widget_set_size_request (labela, 296, 32);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);

	labela = gtk_label_new("<span size='x-large'>+</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	cmdGehi = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cmdGehi), labela);
	gtk_fixed_put (GTK_FIXED (fixed), cmdGehi, 112, 384);
	gtk_widget_set_size_request (cmdGehi, 64, 48);
	g_signal_connect(G_OBJECT(cmdGehi), "clicked",
			G_CALLBACK(btmGehi), NULL);
	gdk_color_parse("#bff9ed", &kolorea);
	gtk_widget_modify_bg(cmdGehi, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(cmdGehi, GTK_STATE_PRELIGHT, &kolorea);
	
	labela = gtk_label_new("<span size='x-large'>-</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	cmdKen = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cmdKen), labela);
	gtk_fixed_put (GTK_FIXED (fixed), cmdKen, 176, 384);
	gtk_widget_set_size_request (cmdKen, 64, 48);
	g_signal_connect(G_OBJECT(cmdKen), "clicked",
			G_CALLBACK(btmKen), NULL);
	gdk_color_parse("#fdb5d5", &kolorea);
	gtk_widget_modify_bg(cmdKen, GTK_STATE_NORMAL, &kolorea);
	gtk_widget_modify_bg(cmdKen, GTK_STATE_PRELIGHT, &kolorea);
	
	lblZenbat = gtk_label_new ("<span size='xx-large'><b>1</b></span>");
	gtk_widget_set_size_request (lblZenbat, 96, 48);
	gtk_label_set_use_markup (GTK_LABEL (lblZenbat), TRUE);
	eventbox = gtk_event_box_new();
	gtk_widget_set_size_request (eventbox, 96, 48);
	gtk_container_add(GTK_CONTAINER(eventbox), lblZenbat);
	gdk_color_parse("black", &kolorea);
	gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblZenbat, GTK_STATE_NORMAL, &kolorea);
	gtk_fixed_put (GTK_FIXED (fixed), eventbox, 16, 384);

	labela = gtk_label_new("<span size='x-large'>Ados</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	cmdAdos = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cmdAdos), labela);
	gtk_widget_show (cmdAdos);
	gtk_fixed_put (GTK_FIXED (fixed), cmdAdos, 24, 480);
	gtk_widget_set_size_request (cmdAdos, 136, 48);
	g_signal_connect(G_OBJECT(cmdAdos), "clicked",
			G_CALLBACK(btmAdos), NULL);
	
	labela = gtk_label_new("<span size='x-large'>Utzi</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	cmdUtzi = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(cmdUtzi), labela);
	gtk_widget_show (cmdUtzi);
	gtk_fixed_put (GTK_FIXED (fixed), cmdUtzi, 192, 480);
	gtk_widget_set_size_request (cmdUtzi, 136, 48);
	g_signal_connect(G_OBJECT(cmdUtzi), "clicked",
			G_CALLBACK(btmUtzi), NULL);

	/* Dena bistaratu eta martxan jarri */
	form_load();
	gtk_widget_show_all(frmBestelakoak);
	gtk_main();
}
