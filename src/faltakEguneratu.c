#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "modSarrera.h"
#include "zenbatUnitate.h"
#define true 1
#define false 0

	static GtkWidget *lstDagoena, *lstElkartea;
	static int badago;

static void form_load()
{
	MYSQL_ROW row;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstElkartea));
	gtk_tree_store_clear(GTK_TREE_STORE(model));

	mysql_query(dbElkartea, "select A.Gizenaeus , B.Kopurua from Elkartea as B INNER JOIN Gaiak as A ON Gaikodea = GKodea ORDER BY A.Gizenaeus");
	rstElkartea = mysql_use_result(dbElkartea);
	if ((row=mysql_fetch_row(rstElkartea))!=NULL)
	{
		do
		{
			gtk_tree_store_append (GTK_TREE_STORE(model), &iter, NULL);
			gtk_tree_store_set(GTK_TREE_STORE(model), &iter,
					0, row[0],
					1, atoi(row[1]),
					-1);
		}
		while ((row=mysql_fetch_row(rstElkartea))!=NULL);
	}
	else
	{
		// mezua, ez dagoela gairik elkartean esanaz!
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmFaltakEguneratu),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ez dago gairik elkartean.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
	mysql_free_result(rstElkartea);
}

/*void faltakBerritu(GtkTreeModel *model, GtkTreePath  *path, GtkTreeIter  *iter, gpointer user_data)
{
	MYSQL_ROW row;
	GtkTreeSelection *selection;
	char *datua;
	int kop;
	char sql[200];

	gtk_tree_model_get (model, iter, 0, &datua, -1);
	gtk_tree_model_get (model, iter, 1, &kop, -1);
	sprintf(sql, "Select GKodea from Gaiak where Gizenaeus='%s'", datua);
	mysql_query(dbElkartea, sql);
	rstGaiak = mysql_store_result(dbElkartea);
	row = mysql_fetch_row(rstGaiak);
	sprintf(sql, "Insert into Faltak(GKodea, GKopurua, DAurrekoa, DAzkena) values(%d, %d, '%s', CURDATE())", atoi(row[0]), kop, aurrekoData);
	mysql_query(dbElkartea, sql);
	sprintf(sql, "Update Elkartea set Kopurua=Kopurua+%d where Gaikodea=%d", kop, atoi(row[0]));
	mysql_query(dbElkartea, sql);
	mysql_free_result(rstGaiak);

	return false;
}*/

static void btmAdos()
{
	MYSQL_ROW row, row2;
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *datua;
	int kop;
	char sql[500];

	//Konprobatu behar ea Dagoena lista hutsik dagoen!!!, ala ez bada galdera egin eta FaltakEguneratu deitu
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstDagoena));
	if (gtk_tree_model_get_iter_first(model, &iter))
	{
		mysql_query(dbElkartea, "Select MAX(Eguna) from Erregistroa");
		rstDatuak = mysql_store_result(dbElkartea);
		row=mysql_fetch_row(rstDatuak);
		mysql_query(dbElkartea, "Insert into Erregistroa(Eguna, Ordua) values(CURDATE(), '')");

		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmFaltakEguneratu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Ziur al zaude falten zenbaketa amaitu duzula?");
		gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		if (erantzuna == GTK_RESPONSE_YES)
		{
// 			gtk_tree_model_foreach(GTK_TREE_MODEL(model), faltakBerritu, NULL);
			while (gtk_tree_model_get_iter_first(model, &iter))
			{
				gtk_tree_model_get (model, &iter, 0, &datua, -1);
				gtk_tree_model_get (model, &iter, 1, &kop, -1);
				sprintf(sql, "Select GKodea from Gaiak where Gizenaeus='%s'", datua);
				mysql_query(dbElkartea, sql);
				rstGaiak = mysql_store_result(dbElkartea);
				row2 = mysql_fetch_row(rstGaiak);
				sprintf(sql, "Insert into Faltak(GKodea, GKopurua, DAurrekoa, DAzkena) values(%d, %d, '%s', CURDATE())", atoi(row2[0]), kop, row[0]);
				mysql_query(dbElkartea, sql);
				sprintf(sql, "Update Elkartea set Kopurua=Kopurua+%d where Gaikodea=%d", kop, atoi(row2[0]));
				mysql_query(dbElkartea, sql);
				mysql_free_result(rstGaiak);

				gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
			}
			gtk_widget_destroy(frmFaltakEguneratu);
		}
		mysql_free_result(rstDatuak);
	}
	else
	{
		gtk_widget_destroy(frmFaltakEguneratu);
	}
}

gboolean zerrendanDago(GtkTreeModel *model, GtkTreePath  *path, GtkTreeIter  *iter, char *izena)
{
	char *datua;
	gtk_tree_model_get (model, iter, 0, &datua, -1);
	if (strcmp(izena, datua)==0) badago=true;
	return FALSE;
}

static void lstElkartea_click()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstElkartea));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstElkartea));
	gtk_tree_selection_get_selected(selection, &model, &iter);
	
	gchar *izena;
	int kop;
	gtk_tree_model_get (model, &iter, 0, &izena, -1);
	gtk_tree_model_get (model, &iter, 1, &kop, -1);
	badago=false;
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstDagoena));
	gtk_tree_model_foreach(GTK_TREE_MODEL(model), zerrendanDago, izena);
	if (badago==true)
	{
		// mezua, gai hori lehendik kontatuta dagoela esanaz
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmFaltakEguneratu),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Jadanik kontatu duzu gai hau.\nBerriro kontatu nahi baduzu lehenik eskuineko zerrendatik kendu beharko duzu");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
	else
	{
		zenbatUnitate(izena, kop, (gpointer) lstDagoena);
		gtk_tree_selection_unselect_all(selection);
	}

}

static void btmKendu()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstDagoena));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstDagoena));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		char *falta;
		gtk_tree_model_get (model, &iter, 0, &falta, -1);
		
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmFaltakEguneratu),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Ziur al zaude %s gaiaren falta kendu nahi duzula?", falta);
		gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		if (erantzuna == GTK_RESPONSE_YES)
		{
			gtk_tree_store_remove(GTK_TREE_STORE(model), &iter);
		}
		gtk_tree_selection_unselect_all(selection);
	}
	else
	{
		//Faltaren bat aukeratua izan behar du!!!
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmFaltakEguneratu),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Faltaren bat aukeratu behar duzu.");
		gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_dialog_run(GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
	}
}

static void btmElkarteaInprimatu()
{
	elkarteaInprimatu();
}

void faltakEguneratu()
{
	GtkWidget *frame;
	GtkWidget *alignment;
	GtkWidget *NagusiaFixed;
	GtkWidget *fixed;
	GtkWidget *vBox;
	GtkWidget *irudia;
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *scrolla;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	
	/* Lehioa sortu eta konfiguratu */
	frmFaltakEguneratu = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmFaltakEguneratu), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmFaltakEguneratu), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmFaltakEguneratu), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmFaltakEguneratu), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmFaltakEguneratu), GTK_WINDOW(frmAdministraria));
	
	/* Lehioaren egitura definitu */
	frame = gtk_frame_new (NULL);
	gtk_container_add (GTK_CONTAINER (frmFaltakEguneratu), frame);

	labela = gtk_label_new("<b>Faltak eguneratu</b>");
	gtk_frame_set_label_widget (GTK_FRAME (frame), labela);
	gtk_label_set_use_markup (GTK_LABEL (labela), TRUE);
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);
	
	NagusiaFixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (alignment), NagusiaFixed);
	
	/* Elkarteko gaien aldea sortu eta sartu */
	frame = gtk_frame_new ("Elkartean egon behar lukeena");
	gtk_fixed_put (GTK_FIXED (NagusiaFixed), frame, 26, 26);
	gtk_widget_set_size_request (frame, 330, 524);
	
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frame), fixed);
	
		/* ELkarteko gaien lista sortu eta sartu */
		scrolla = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolla), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_fixed_put (GTK_FIXED (fixed), scrolla, 13, 8);
		gtk_widget_set_size_request (scrolla, 291, 376);
		model = GTK_TREE_MODEL (gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT));
		lstElkartea = gtk_tree_view_new_with_model(model);
		g_signal_connect(G_OBJECT(lstElkartea), "cursor-changed",
				G_CALLBACK(lstElkartea_click), NULL);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstElkartea),
						-1, "Zer", renderer,
						"text", 0,
						NULL);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstElkartea),
						-1, "Zenbat", renderer,
						"text", 1,
						NULL);
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolla), lstElkartea);
		
		/* Inprimatzeko botoia sortu eta sartu */
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmElkarteaInprimatu), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 24, 408);
		gtk_widget_set_size_request (botoia, 96, 80);	
		alignment = gtk_alignment_new (0.5, 0.5, 0, 0);
  		gtk_container_add (GTK_CONTAINER (botoia), alignment);
		vBox = gtk_vbox_new (FALSE, 5);	
		irudia = gtk_image_new_from_stock ("gtk-print", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vBox), irudia, FALSE, FALSE, 0);
		labela = gtk_label_new("Inprimatu\n inbentarioa");
		gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
		gtk_container_add(GTK_CONTAINER(alignment), vBox);
	
	/* Guk ikusitako gaien aldea sortu eta sartu */
	frame = gtk_frame_new ("Ikusitako gaiak");
	gtk_fixed_put (GTK_FIXED (NagusiaFixed), frame, 408, 24);
	gtk_widget_set_size_request (frame, 330, 524);
	
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frame), fixed);
	
		/* Dauden elementuen lista sortu eta sartu */
		scrolla = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolla), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_fixed_put (GTK_FIXED (fixed), scrolla, 13, 8);
		gtk_widget_set_size_request (scrolla, 291, 376);
		model = GTK_TREE_MODEL (gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT));
		lstDagoena = gtk_tree_view_new_with_model(model);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstDagoena),
						-1, "Zer", renderer,
						"text", 0,
						NULL);
		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstDagoena),
						-1, "Aldea", renderer,
						"text", 1,
						NULL);
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolla), lstDagoena);
		
		/* Kendu botoia sortu eta sartu */
		botoia = gtk_button_new ();
		g_signal_connect(G_OBJECT(botoia), "clicked",
				G_CALLBACK(btmKendu), NULL);
		gtk_fixed_put (GTK_FIXED (fixed), botoia, 24, 408);
		gtk_widget_set_size_request (botoia, 96, 80);
		alignment = gtk_alignment_new (0.5, 0.5, 0, 0);
  		gtk_container_add (GTK_CONTAINER (botoia), alignment);
		vBox = gtk_vbox_new (FALSE, 2);
		gtk_container_add (GTK_CONTAINER (alignment), vBox);
		irudia = gtk_image_new_from_stock ("gtk-close", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vBox), irudia, FALSE, FALSE, 0);
		labela = gtk_label_new("Kendu");
		gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);
	
	/* Inprimatu inbentarioa botoia sortu eta sartu */
	/*botoia = gtk_button_new ();
	gtk_fixed_put (GTK_FIXED (NagusiaFixed), botoia, 552, 568);
	gtk_widget_set_size_request (botoia, 184, 56);
	alignment = gtk_alignment_new (0.5, 0.5, 0, 0);
  	gtk_container_add (GTK_CONTAINER (botoia), alignment);
	vBox = gtk_vbox_new (FALSE, 2);
	gtk_container_add (GTK_CONTAINER (alignment), vBox);
	irudia = gtk_image_new_from_stock ("gtk-print", GTK_ICON_SIZE_BUTTON);
	gtk_box_pack_start (GTK_BOX (vBox), irudia, FALSE, FALSE, 0);
	labela = gtk_label_new("Inprimatu inbentarioa");
	gtk_box_pack_start (GTK_BOX (vBox), labela, FALSE, FALSE, 0);*/
	
	/* Ados botoia sortu eta sartu */
	botoia = gtk_button_new_with_label("Ados");
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_widget_show (botoia);
	gtk_fixed_put (GTK_FIXED (NagusiaFixed), botoia, 320, 568);
	gtk_widget_set_size_request (botoia, 120, 48);

	/* Dena bistaratu eta martxan jarri */
	gtk_widget_show_all(frmFaltakEguneratu);

	form_load();
}
