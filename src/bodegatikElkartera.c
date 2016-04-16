#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "modSarrera.h"
#include "kendu.h"
#include "mugitu.h"
#include "gehiagoSartu.h"
#include "gaiBerriaSartu.h"

	static GtkWidget *lstElkartea, *lstBodega;

static void btmAdos()
{
	gtk_widget_destroy(frmBodegatikElkartera);
}

static void form_load()
{
	listakBete();
}

void listakBete()
{
	MYSQL_ROW row;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(lstBodega);

	gtk_tree_store_clear(model);

	mysql_query(dbElkartea, "select A.Gizenaeus , B.Gaikopurua from Bodega as B INNER JOIN Gaiak as A ON Gaikodea = GKodea ORDER BY A.Gizenaeus");
	rstDatuak = mysql_use_result(dbElkartea);
	while ((row=mysql_fetch_row(rstDatuak))!=NULL)
	{
		gtk_tree_store_append (model, &iter, NULL);
		gtk_tree_store_set(model, &iter,
				0, row[0],
				1, atoi(row[1]),
				-1);
	}
	mysql_free_result (rstDatuak);

	model = gtk_tree_view_get_model(lstElkartea);

	gtk_tree_store_clear(model);

	mysql_query(dbElkartea, "select A.Gizenaeus , B.Kopurua from Elkartea as B INNER JOIN Gaiak as A ON Gaikodea = GKodea ORDER BY A.Gizenaeus");
	rstDatuak = mysql_use_result(dbElkartea);
	while ((row=mysql_fetch_row(rstDatuak))!=NULL)
	{
		gtk_tree_store_append (model, &iter, NULL);
		gtk_tree_store_set(model, &iter,
				0, row[0],
				1, atoi(row[1]),
				-1);
	}
	mysql_free_result (rstDatuak);
}

static void btmKenduBodegatik()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(lstBodega);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstBodega));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *aukera;
		int kop;

		gtk_tree_model_get (model, &iter, 0, &aukera, -1);
		gtk_tree_model_get (model, &iter, 1, &kop, -1);

		kendu(aukera, kop);

		listakBete();
	}
	else
	{
		//Gairen bat aukeratua izan behar du!!!
		GtkWidget *mezua = gtk_message_dialog_new(frmBodegatikElkartera,
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Bodegako gairen bat aukeratu behar duzu!.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
}

static void btmElkartera()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(lstBodega);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstBodega));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *aukera;
		int kop;

		gtk_tree_model_get (model, &iter, 0, &aukera, -1);
		gtk_tree_model_get (model, &iter, 1, &kop, -1);

		mugitu(aukera, kop);

		listakBete();
	}
	else
	{
		//Gairen bat aukeratua izan behar du!!!
		GtkWidget *mezua = gtk_message_dialog_new(frmBodegatikElkartera,
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Bodegako gairen bat aukeratu behar duzu!.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
}

static void btmGaiaGehitu()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(lstElkartea);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstElkartea));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *izena;
		gchar kop[5];
		int kopurua;
		gtk_tree_model_get (model, &iter, 0, &izena, -1);
		gtk_tree_model_get (model, &iter, 1, &kopurua, -1);
		sprintf(kop, "%d" , kopurua);
		gehiagoSartu(izena, kop);
		listakBete();
	}
	else
	{
		//Gairen bat aukeratu behar duzu!!
		GtkWidget *mezua = gtk_message_dialog_new(frmBodegatikElkartera,
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Elkarteko gairen bat aukeratu behar duzu!.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
}

static void btmBerriaSartu()
{
	gaiBerriaSartu();
	listakBete();
}

void bodegatikElkartera()
{
	GtkWidget *frame;
	GtkWidget *fixedNagusia;
	GtkWidget *frameBodega;
	GtkWidget *alignment;
	GtkWidget *fixed;
	GtkWidget *botoia;
	GtkWidget *vBox;
	GtkWidget *irudia;
	GtkWidget *labela;
	GtkWidget *frameElkartea;
	GtkWidget *scrolla;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	
	/* Lehioa sortu eta konfiguratu */
	frmBodegatikElkartera = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmBodegatikElkartera), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmBodegatikElkartera), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmBodegatikElkartera), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmBodegatikElkartera), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (frmBodegatikElkartera, frmAdministraria);
	
	/* Formularioa osatzeko egitura sortu */
	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (frmBodegatikElkartera), frame);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 0, 24, 12, 24);
	
	fixedNagusia = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (alignment), fixedNagusia);
	
	/* Bodegaren zatia sortu */
	frameBodega = gtk_frame_new ("Bodega");
	gtk_fixed_put (GTK_FIXED (fixedNagusia), frameBodega, 16, 16);
	gtk_widget_set_size_request (frameBodega, 360, 544);
	
		/* Bodegaren egitura sortu */
		fixed = gtk_fixed_new ();
		gtk_container_add (GTK_CONTAINER (frameBodega), fixed);
		
		/* lstBodega lista sortu eta sartu */
		scrolla = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolla), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		model = GTK_TREE_MODEL (gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT));
		gtk_fixed_put (GTK_FIXED (fixed), scrolla, 17, 8);
		gtk_widget_set_size_request (scrolla, 296, 392);
		lstBodega = gtk_tree_view_new_with_model(model);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstBodega),
						-1, "Zer", renderer,
						"text", 0,
						NULL);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstBodega),
						-1, "Zenbat", renderer,
						"text", 1,
						NULL);
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolla), lstBodega);
	
		/* Kendu Bodegatik botoia sortu eta sartu */
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmKenduBodegatik), NULL);
		gtk_widget_show (botoia);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 25, 416);
		gtk_widget_set_size_request (botoia, 104, 96);
		vBox = gtk_vbox_new (TRUE, 4);
		gtk_container_add (GTK_CONTAINER (botoia), vBox);
		irudia = gtk_image_new_from_stock ("gtk-no", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vBox), irudia, FALSE, FALSE, 0);
		labela = gtk_label_new(" Kendu\nBodegatik");
		gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	
	/* Elkartearen zatia sortu eta sartu */
	frameElkartea = gtk_frame_new ("Elkartea");
	gtk_fixed_put (GTK_FIXED (fixedNagusia), frameElkartea, 544, 16);
	gtk_widget_set_size_request (frameElkartea, 360, 544);
	
		/* Elkartearen egitura sortu */
		fixed = gtk_fixed_new ();
		gtk_widget_show (fixed);
		gtk_container_add (GTK_CONTAINER (frameElkartea), fixed);
		
		/* lstElkartea sortu eta sartu */
		scrolla = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolla), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_fixed_put (GTK_FIXED (fixed), scrolla, 17, 8);
		gtk_widget_set_size_request (scrolla, 296, 392);
		model = GTK_TREE_MODEL (gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT));
		lstElkartea = gtk_tree_view_new_with_model(model);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstElkartea ),
						-1, "Zer", renderer,
						"text", 0,
						NULL);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstElkartea ),
						-1, "Zenbat", renderer,
						"text", 1,
						NULL);
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolla), lstElkartea);
		
		/* Gaia gehitu botoia sortu eta sartu */
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmGaiaGehitu), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 25, 416);
		gtk_widget_set_size_request (botoia, 104, 96);
		vBox = gtk_vbox_new (TRUE, 4);
		gtk_container_add (GTK_CONTAINER (botoia), vBox);
		irudia = gtk_image_new_from_stock ("gtk-add", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vBox), irudia, FALSE, FALSE, 0);
		labela = gtk_label_new(" Gaia\nGehitu");
		gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
		
		/* Berria sartu botoia sortu eta sartu */
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmBerriaSartu), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 145, 416);
		gtk_widget_set_size_request (botoia, 104, 96);
		vBox = gtk_vbox_new (TRUE, 4);
		gtk_container_add (GTK_CONTAINER (botoia), vBox);
		irudia = gtk_image_new_from_stock ("gtk-goto-top", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vBox), irudia, FALSE, FALSE, 0);
		labela = gtk_label_new("Berria\nSartu");
		gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	
	/* Elkartera botoia sortu eta sartu */
	botoia = gtk_button_new ();
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmElkartera), NULL);
	gtk_fixed_put (GTK_FIXED (fixedNagusia), botoia, 400, 192);
	gtk_widget_set_size_request (botoia, 128, 88);
	vBox = gtk_vbox_new (TRUE, 4);
	gtk_container_add (GTK_CONTAINER (botoia), vBox);
	irudia = gtk_image_new_from_stock ("gtk-goto-last", GTK_ICON_SIZE_BUTTON);
	gtk_box_pack_start (GTK_BOX (vBox), irudia, FALSE, FALSE, 0);
	labela = gtk_label_new("elkartera");
	gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	
	/* Ados botoia sortu eta sartu */
	botoia = gtk_button_new_with_label ("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_fixed_put (GTK_FIXED (fixedNagusia), botoia, 392, 576);
	gtk_widget_set_size_request (botoia, 144, 56);
	
	labela = gtk_label_new("<b>Bodegatik Elkartera</b>");
	gtk_frame_set_label_widget (GTK_FRAME (frame), labela);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);

	/* Dena bistaratu */
	gtk_widget_show_all(frmBodegatikElkartera);

	form_load();
}