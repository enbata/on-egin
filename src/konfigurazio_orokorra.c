#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "modSarrera.h"
#include "aukeraSartu.h"
#include "sartuGaia.h"
#define true 1
#define false 0

	static GtkWidget *lstAukerak, *lstGaiak, *checkFaltak, *frameGaiak;
	static MYSQL_RES *rstBertakoGaiak;
	static int kodea;

typedef struct
{
	gchar *balioa;
} elementua;

enum
{
	Balio_Zutabea,
	Zutabe_Kop
};

void BalioakSartu()
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	elementua a;
	MYSQL_ROW row;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstAukerak));

	gtk_list_store_clear(GTK_LIST_STORE(model));

	mysql_query(dbElkartea, "SELECT * FROM Aukerak order by AOrdena");
	rstAukerak = mysql_use_result(dbElkartea);
	while ((row=mysql_fetch_row(rstAukerak))!=NULL)
	{
		a.balioa = g_strdup (row[0]);
		gtk_list_store_append (GTK_LIST_STORE(model), &iter);
		gtk_list_store_set(GTK_LIST_STORE(model), &iter,
				Balio_Zutabea,
				a.balioa,
				-1);
	}
	mysql_free_result(rstAukerak);
}

void faltakKargatu()
{
	MYSQL_ROW row;

	mysql_query(dbElkartea, "select Faltak from ElkartekoDatuak");
	rstAukerak=mysql_use_result(dbElkartea);
	if ((row=mysql_fetch_row(rstAukerak))!=NULL)
		if ((row[0]) != NULL)
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkFaltak), atoi(row[0]));
		else
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(checkFaltak), 0);
	mysql_free_result(rstAukerak);
}

static void form_load()
{
	BalioakSartu();
	faltakKargatu();
}

static void btmAdos()
{
	MYSQL_RES *res;
	MYSQL_ROW row;

	mysql_query(dbElkartea, "Select Faltak from ElkartekoDatuak");
	res = mysql_store_result(dbElkartea);
	if ((row= mysql_fetch_row(res)) != NULL)
	{
		if (row[0]!=NULL)
		{
			if (atoi(row[0])!=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkFaltak)))
			{
				GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmKonfigurazioOrokorra),
								GTK_DIALOG_DESTROY_WITH_PARENT,
								GTK_MESSAGE_QUESTION,
								GTK_BUTTONS_YES_NO,
								"Aldaketak gordetzea nahi al duzu?");
				int erantzuna;
				if ((erantzuna=gtk_dialog_run(GTK_DIALOG(mezua)))==GTK_RESPONSE_YES)
				{
					char sql[300];
					sprintf(sql, "Update ElkartekoDatuak set Faltak=%d", gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkFaltak)));
					mysql_query(dbElkartea, sql);
				}
				gtk_widget_destroy(mezua);
			}
		}
		else
		{
			char sql[300];
			sprintf(sql, "Update ElkartekoDatuak set Faltak=%d", gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkFaltak)));
			mysql_query(dbElkartea, sql);
		}
	}
	else
	{
		char sql[300];
		sprintf(sql, "Update ElkartekoDatuak set Faltak=%d", gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkFaltak)));
		mysql_query(dbElkartea, sql);
	}
	mysql_free_result(res);
	gtk_widget_destroy (frmKonfigurazioOrokorra);
}

void aukeraMezua()
{
	GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmKonfigurazioOrokorra),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Aukeraren bat aukeratu behar duzu.");
	gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_dialog_run(GTK_DIALOG(mezua));
	gtk_widget_destroy (mezua);
}

static void btmAGora()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstAukerak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstAukerak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
// 		gtk_list_store_move_before(model, &iter, &iter);
		gchar *aukera;
		MYSQL_RES *res;
		MYSQL_ROW row;
		gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
		gchar *sql = "Select Aizenaeus from Aukerak where AOrdena <=ALL (select AOrdena from Aukerak)";
		mysql_query(dbElkartea, sql);
		res=mysql_store_result(dbElkartea);
		row=mysql_fetch_row(res);
		if (strcmp(aukera, row[0])!=0)
		{
			mysql_free_result (res);
			gchar sql[300];
			sprintf(sql, "Select AOrdena from Aukerak where Aizenaeus='%s'", aukera);
			mysql_query(dbElkartea, sql);
			res=mysql_store_result(dbElkartea);
			row=mysql_fetch_row(res);
			sprintf(sql, "Update Aukerak set AOrdena=%d where AOrdena=%d", atoi(row[0]), atoi(row[0]) - 1);
			mysql_query(dbElkartea, sql);
			sprintf(sql, "Update Aukerak set AOrdena=%d where Aizenaeus='%s'", atoi(row[0]) - 1, aukera);
			mysql_query(dbElkartea, sql);
			BalioakSartu();
			// Froga!!!
			gtk_tree_selection_select_iter(selection, &iter);
		}
		mysql_free_result (res);
	}
	else
	{
		aukeraMezua();
	}
}

static void btmABehera()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstAukerak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstAukerak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *aukera;
		MYSQL_RES *res;
		MYSQL_ROW row;
		gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
		gchar *sql = "Select Aizenaeus from Aukerak where AOrdena >=ALL (select AOrdena from Aukerak)";
		mysql_query(dbElkartea, sql);
		res=mysql_store_result(dbElkartea);
		row=mysql_fetch_row(res);
		if (strcmp(aukera, row[0])!=0)
		{
			mysql_free_result (res);
			gchar sql[300];
			sprintf(sql, "Select AOrdena from Aukerak where Aizenaeus='%s'", aukera);
			mysql_query(dbElkartea, sql);
			res=mysql_store_result(dbElkartea);
			row=mysql_fetch_row(res);
			sprintf(sql, "Update Aukerak set AOrdena=%d where AOrdena=%d", atoi(row[0]), atoi(row[0]) + 1);
			mysql_query(dbElkartea, sql);
			sprintf(sql, "Update Aukerak set AOrdena=%d where Aizenaeus='%s'", atoi(row[0]) + 1, aukera);
			mysql_query(dbElkartea, sql);
			BalioakSartu();
		}
		mysql_free_result (res);
	}
	else
	{
		aukeraMezua();
	}
}

void GaiakSartu ()
{
	char sql[300];
	GtkTreeModel *model;
	GtkTreeIter iter;
	elementua a;
	MYSQL_ROW row;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstGaiak));

	gtk_list_store_clear(GTK_LIST_STORE(model));

	sprintf(sql, "Select * from Gaiak where AKodea=%d order by GOrdena", kodea);
	mysql_query(dbElkartea, sql);
	rstBertakoGaiak=mysql_use_result(dbElkartea);
	while ((row=mysql_fetch_row(rstBertakoGaiak))!=NULL)
	{
		a.balioa = g_strdup (row[0]);
		gtk_list_store_append (GTK_LIST_STORE(model), &iter);
		gtk_list_store_set(GTK_LIST_STORE(model), &iter,
				Balio_Zutabea,
				a.balioa,
				-1);
	}
	mysql_free_result(rstBertakoGaiak);
}

static void btmGGora()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstGaiak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstGaiak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
// 		gtk_list_store_move_before(model, &iter, &iter);
		gchar *aukera;
		MYSQL_RES *res;
		MYSQL_ROW row;
		gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
		gchar sql[300];
		sprintf(sql, "Select Gizenaeus from Gaiak where GOrdena <=ALL (select GOrdena from Gaiak where AKodea=%d) and AKodea=%d", kodea, kodea);
		mysql_query(dbElkartea, sql);
		res=mysql_store_result(dbElkartea);
		row=mysql_fetch_row(res);
		if (strcmp(aukera, row[0])!=0)
		{
			mysql_free_result (res);
			gchar sql[300];
			sprintf(sql, "Select GOrdena from Gaiak where Gizenaeus='%s'", aukera);
			mysql_query(dbElkartea, sql);
			res=mysql_store_result(dbElkartea);
			row=mysql_fetch_row(res);
			sprintf(sql, "Update Gaiak set GOrdena=%d where GOrdena=%d and AKodea=%d", atoi(row[0]), atoi(row[0]) - 1, kodea);
			mysql_query(dbElkartea, sql);
			sprintf(sql, "Update Gaiak set GOrdena=%d where Gizenaeus='%s'", atoi(row[0]) - 1, aukera);
			mysql_query(dbElkartea, sql);
			GaiakSartu();
		}
		mysql_free_result (res);
	}
	else
	{
		aukeraMezua();
	}
}

static void btmGBehera()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstGaiak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstGaiak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *aukera;
		MYSQL_RES *res;
		MYSQL_ROW row;
		gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
		gchar sql[300];
		sprintf(sql, "Select Gizenaeus from Gaiak where GOrdena >=ALL (select GOrdena from Gaiak where AKodea=%d) and AKodea=%d", kodea, kodea);
		mysql_query(dbElkartea, sql);
		res=mysql_store_result(dbElkartea);
		row=mysql_fetch_row(res);
		if (strcmp(aukera, row[0])!=0)
		{
			mysql_free_result (res);
			gchar sql[300];
			sprintf(sql, "Select GOrdena from Gaiak where Gizenaeus='%s'", aukera);
			mysql_query(dbElkartea, sql);
			res=mysql_store_result(dbElkartea);
			row=mysql_fetch_row(res);
			sprintf(sql, "Update Gaiak set GOrdena=%d where GOrdena=%d and AKodea=%d", atoi(row[0]), atoi(row[0]) + 1, kodea);
			mysql_query(dbElkartea, sql);
			sprintf(sql, "Update Gaiak set GOrdena=%d where Gizenaeus='%s'", atoi(row[0]) + 1, aukera);
			mysql_query(dbElkartea, sql);
			GaiakSartu();
		}
		mysql_free_result (res);
	}
	else
	{
		aukeraMezua();
	}
}

static void btmEzabatu()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	MYSQL_ROW row;
	MYSQL_RES *res;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstAukerak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstAukerak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmKonfigurazioOrokorra),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_QUESTION,
						GTK_BUTTONS_YES_NO,
						"Ziur al zaude aukera ezabatu nahi duzula?");
		gint erantzuna = gtk_dialog_run (GTK_DIALOG(mezua));
		gtk_widget_destroy (mezua);
		if (erantzuna == GTK_RESPONSE_YES)
		{
			// Ea gairik duen konprobatu behar lehenik. Gaien zerrenda hutsa badago bakarrik utzi ezabatzen.
			char sql[300];
			sprintf(sql, "Select * from Gaiak where AKodea=%d", kodea);
			mysql_query(dbElkartea, sql);
			res = mysql_store_result(dbElkartea);
			if ((row=mysql_fetch_row(res))==NULL)
			{
				char sql[300];
				gchar *aukera;
				gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
				// Atzetik datorren pauso hau Aukera klikatzen duenean erabiltzea obe.
				sprintf(sql, "Select AOrdena from Aukerak where Aizenaeus='%s'", aukera);
				mysql_query(dbElkartea, sql);
				rstAukerak = mysql_store_result(dbElkartea);
				row=mysql_fetch_row(rstAukerak);
				char sql1[300];
				sprintf (sql1, "Delete from Aukerak where Aizenaeus='%s'", aukera);
				mysql_query(dbElkartea, sql1);
				char sql2[300];
				sprintf(sql2, "Update Aukerak set AOrdena=AOrdena-1 where AOrdena>%d", atoi(row[0]));
				mysql_query(dbElkartea, sql2);
				mysql_free_result(rstAukerak);
				gtk_widget_hide(frameGaiak);
				BalioakSartu();
			}
			else
			{
				GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmKonfigurazioOrokorra),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Ezin da aukera ezabatu gairik duen artean");
				gtk_dialog_run (GTK_DIALOG(mezua));
				gtk_widget_destroy (mezua);
			}
			mysql_free_result(res);
		}
	}
	else
	{
		aukeraMezua();
	}
}

static void btmBerria()
{
	gtk_widget_hide(frameGaiak);
	aukeraSartu((gpointer) lstAukerak ,true);
	BalioakSartu();
}

static void btmEditatu()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstAukerak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstAukerak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gtk_widget_hide(frameGaiak);
		aukeraSartu((gpointer) lstAukerak ,false);
		BalioakSartu();
	}
	else
	{
		aukeraMezua();
	}
}

static void lstAukerak_click()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstAukerak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstAukerak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *aukera;
		char sql[300];
		MYSQL_ROW row;

		gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
		sprintf(sql, "Select AKodea from Aukerak where Aizenaeus='%s'", aukera);
		mysql_query(dbElkartea, sql);
		rstAukerak = mysql_store_result(dbElkartea);
		row=mysql_fetch_row(rstAukerak);
		kodea=atoi(row[0]);
		GaiakSartu();
		gtk_frame_set_label(GTK_FRAME(frameGaiak), aukera);
		gtk_widget_show(frameGaiak);
		mysql_free_result(rstAukerak);
	}
}

void gaiaMezua()
{
	GtkWidget *mezua = gtk_message_dialog_new(GTK_WINDOW(frmKonfigurazioOrokorra),
						GTK_DIALOG_MODAL,
						GTK_MESSAGE_INFO,
						GTK_BUTTONS_OK,
						"Gairen bat aukeratu behar duzu editatzeko.");
	gtk_window_set_position (GTK_WINDOW(mezua), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_dialog_run(GTK_DIALOG(mezua));
	gtk_widget_destroy (mezua);
}

static void btmEditatuGaia()
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(lstGaiak));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(lstGaiak));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gchar *aukera;

		gtk_tree_model_get (model, &iter, Balio_Zutabea, &aukera, -1);
		sartuGaia(aukera);
		GaiakSartu();
	}
	else
	{
		gaiaMezua();
	}
}

void konfigurazioOrokorra()
{
	GtkWidget *frame;
	GtkWidget *fixed1;
	GtkWidget *fixed3;
	GtkWidget *button;
	GtkWidget *image;
	GtkWidget *fixed2;
	GtkWidget *vbox;
	GtkWidget *label;
	GtkWidget *hbox;
	GtkWidget *scrolla;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	
	frmKonfigurazioOrokorra = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmKonfigurazioOrokorra), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmKonfigurazioOrokorra), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmKonfigurazioOrokorra), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmKonfigurazioOrokorra), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for (GTK_WINDOW(frmKonfigurazioOrokorra), GTK_WINDOW(frmAdministraria));
	
	frame = gtk_frame_new ("");
	gtk_container_add (GTK_CONTAINER (frmKonfigurazioOrokorra), frame);
	label = gtk_label_new (("<b>Konfigurazio Orokorra</b>"));
	gtk_frame_set_label_widget (GTK_FRAME (frame), label);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);;
	
	fixed1 = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frame), fixed1);
	gtk_container_set_border_width (GTK_CONTAINER (fixed1), 0);

	/* Gaien zatia sortu eta sartu */
	frameGaiak = gtk_frame_new ("");
	gtk_fixed_put (GTK_FIXED (fixed1), frameGaiak, 424, 24);
	gtk_widget_set_size_request (frameGaiak, 384, 528);
	
	fixed3 = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frameGaiak), fixed3);
	
		/* Gora mugitzeko botoia sartu */
		button = gtk_button_new ();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmGGora), NULL);
		gtk_fixed_put (GTK_FIXED (fixed3), button, 304, 40);
		gtk_widget_set_size_request (button, 48, 48);
		image = gtk_image_new_from_stock ("gtk-go-up", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (button), image);

		/* Behera mugitzeko botoia sartu */
		button = gtk_button_new ();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmGBehera), NULL);
		gtk_fixed_put (GTK_FIXED (fixed3), button, 304, 344);
		gtk_widget_set_size_request (button, 48, 48);
		image = gtk_image_new_from_stock ("gtk-go-down", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (button), image);

		/* Gaien lista sortu eta sartu */
		scrolla = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolla), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_fixed_put (GTK_FIXED (fixed3), scrolla, 8, 24);
		gtk_widget_set_size_request (scrolla, 288, 376);
		model = GTK_TREE_MODEL (gtk_list_store_new(Zutabe_Kop, G_TYPE_STRING));
		lstGaiak = gtk_tree_view_new_with_model(model);
		renderer = gtk_cell_renderer_text_new ();
        	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstGaiak),
						-1, "Sartuta dituen gaiak", renderer,
						"text", Balio_Zutabea,
						NULL);
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolla), lstGaiak);

		/* Editatu botoia sartu */
		button = gtk_button_new();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmEditatuGaia), NULL);
		gtk_fixed_put (GTK_FIXED (fixed3), button, 16, 416);
		gtk_widget_set_size_request (button, 88, 80);
		vbox = gtk_vbox_new(FALSE, 5);
		image = gtk_image_new_from_stock ("gtk-edit", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);
		label = gtk_label_new("Editatu");
		gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
		gtk_container_add(GTK_CONTAINER(button), vbox);

	/* Ados botoia sortu eta sartu */
	button = gtk_button_new_with_mnemonic (("Ados"));
	gtk_fixed_put (GTK_FIXED (fixed1), button, 328, 560);
	gtk_widget_set_size_request (button, 144, 56);
	g_signal_connect(G_OBJECT(button), "clicked",
			G_CALLBACK(btmAdos), NULL);
	
	/* Aukeren zatia osatu eta sartu */
	frame = gtk_frame_new ("");
	gtk_fixed_put (GTK_FIXED (fixed1), frame, 5, 24);
	gtk_widget_set_size_request (frame, 384, 528);
	
	fixed2 = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (frame), fixed2);

		/* Aukeren lista sortu eta sartu */
		scrolla = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolla), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_fixed_put (GTK_FIXED (fixed2), scrolla, 5, 24);
		gtk_widget_set_size_request (scrolla, 296, 376);
		model = GTK_TREE_MODEL (gtk_list_store_new(Zutabe_Kop, G_TYPE_STRING));
		lstAukerak = gtk_tree_view_new_with_model(model);
		g_signal_connect(G_OBJECT(lstAukerak), "cursor-changed",
				G_CALLBACK(lstAukerak_click), NULL);
		renderer = gtk_cell_renderer_text_new ();
        	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (lstAukerak),
						-1, "Sartuta dauden aukerak", renderer,
						"text", Balio_Zutabea,
						NULL);
		gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolla), lstAukerak);
		
		
		/* Ezabatu botoia sartu */
		button = gtk_button_new ();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmEzabatu), NULL);
		gtk_fixed_put (GTK_FIXED (fixed2), button, 16, 416);
		gtk_widget_set_size_request (button, 88, 80);
		vbox = gtk_vbox_new (FALSE, 5);
		gtk_container_add (GTK_CONTAINER (button), vbox);
		image = gtk_image_new_from_stock ("gtk-delete", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vbox), image, TRUE, TRUE, 0);
		label = gtk_label_new (("Ezabatu"));
		gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
		
		/* Editatu botoia sartu */
		button = gtk_button_new ();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmEditatu), NULL);
		gtk_fixed_put (GTK_FIXED (fixed2), button, 208, 416);
		gtk_widget_set_size_request (button, 88, 80);
		vbox = gtk_vbox_new (FALSE, 5);
		image = gtk_image_new_from_stock ("gtk-edit", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vbox), image, TRUE, TRUE, 0);
		label = gtk_label_new_with_mnemonic (("Editatu"));
		gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
		gtk_container_add (GTK_CONTAINER (button), vbox);
		
		/* Gora mugitzeko botoia sartu */
		button = gtk_button_new ();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmAGora), NULL);
		gtk_fixed_put (GTK_FIXED (fixed2), button, 309, 40);
		gtk_widget_set_size_request (button, 48, 48);
		image = gtk_image_new_from_stock ("gtk-go-up", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (button), image);
		
		/* Behera mugitzeko botoia sartu */
		button = gtk_button_new ();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmABehera), NULL);
		gtk_fixed_put (GTK_FIXED (fixed2), button, 309, 344);
		gtk_widget_set_size_request (button, 48, 48);
		image = gtk_image_new_from_stock ("gtk-go-down", GTK_ICON_SIZE_BUTTON);
		gtk_container_add (GTK_CONTAINER (button), image);
		
		/* Berria botoia sartu */
		button = gtk_button_new ();
		g_signal_connect(G_OBJECT(button), "clicked",
				G_CALLBACK(btmBerria), NULL);
		gtk_fixed_put (GTK_FIXED (fixed2), button, 112, 416);
		gtk_widget_set_size_request (button, 88, 80);
		vbox = gtk_vbox_new (FALSE, 5);
		image = gtk_image_new_from_stock ("gtk-add", GTK_ICON_SIZE_BUTTON);
		gtk_box_pack_start (GTK_BOX (vbox), image, TRUE, TRUE, 0);
		label = gtk_label_new_with_mnemonic (("Berria"));
		gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
		gtk_container_add (GTK_CONTAINER (button), vbox);
	
	/* Falten gestioaren zatia osatu eta sartu */
	frame = gtk_frame_new ("");
	gtk_fixed_put (GTK_FIXED (fixed1), frame, 600, 568);
	
	hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER(frame), hbox);
	
	label = gtk_label_new (("Falten Gestioa"));
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);
	
	checkFaltak = gtk_check_button_new_with_mnemonic ("");
	gtk_box_pack_start (GTK_BOX (hbox), checkFaltak, FALSE, FALSE, 0);
	
	/* Ezkutatu beharrezkoa eta gainontzeko dena erakutsi */
	gtk_widget_show_all (frmKonfigurazioOrokorra);
	gtk_widget_hide(frameGaiak);

	form_load();
}
