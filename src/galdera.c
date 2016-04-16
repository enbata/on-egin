#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modSarrera.h"

	GtkWidget *lblBKop, *lblEBKop;

static void form_load()
{
	char kop[100];

	sprintf(kop, "<span size='xx-large'>%d</span>", bazkideKop);
	gtk_label_set_text(GTK_LABEL(lblBKop), kop);
	gtk_label_set_use_markup(GTK_LABEL(lblBKop), TRUE);
	sprintf(kop, "<span size='xx-large'>%d</span>", ezBazkideKop);
	gtk_label_set_text(GTK_LABEL(lblEBKop), kop);
	gtk_label_set_use_markup(GTK_LABEL(lblEBKop), TRUE);
}

static void btmZenbakia(GtkWidget *botoia, gpointer testua)
{
	char kopurua[100];
	sprintf(kopurua, "%s", gtk_label_get_text(GTK_LABEL(lblBKop)));

	if (strcmp(testua, "+")==0)
	{
		int k = atoi(kopurua) +1;
		sprintf(kopurua, "<span size='xx-large'>%d</span>", k);
		gtk_label_set_text(GTK_LABEL(lblBKop), kopurua);
		gtk_label_set_use_markup(GTK_LABEL(lblBKop), TRUE);
	}
	else
		if (strcmp(testua, "-")==0)
		{
			int k = atoi(kopurua) -1;
			sprintf(kopurua, "<span size='xx-large'>%d</span>", k);
			gtk_label_set_text(GTK_LABEL(lblBKop), kopurua);
			gtk_label_set_use_markup(GTK_LABEL(lblBKop), TRUE);
		}
		else
			if (strcmp(testua, "D")==0)
			{
				int k = atoi(kopurua) /10;
				sprintf(kopurua, "<span size='xx-large'>%d</span>", k);
				gtk_label_set_text(GTK_LABEL(lblBKop), kopurua);
				gtk_label_set_use_markup(GTK_LABEL(lblBKop), TRUE);
			}
			else
			{
				if (strcmp(kopurua, "0")==0)
				{
					sprintf(kopurua, "<span size='xx-large'>%s</span>", testua);
					gtk_label_set_text(GTK_LABEL(lblBKop), kopurua);
					gtk_label_set_use_markup(GTK_LABEL(lblBKop), TRUE);
				}
				else
				{
					sprintf(kopurua, "<span size='xx-large'>%d%d</span>", atoi(kopurua), atoi(testua));
					gtk_label_set_text(GTK_LABEL(lblBKop), kopurua);
					gtk_label_set_use_markup(GTK_LABEL(lblBKop), TRUE);
				}
			}
}

static void btmZenbakia2(GtkWidget *botoia, gpointer testua)
{
	char kopurua[100];
	sprintf(kopurua, "%s", gtk_label_get_text(GTK_LABEL(lblEBKop)));

	if (strcmp(testua, "+")==0)
	{
		int k = atoi(kopurua) +1;
		sprintf(kopurua, "<span size='xx-large'>%d</span>", k);
		gtk_label_set_text(GTK_LABEL(lblEBKop), kopurua);
		gtk_label_set_use_markup(GTK_LABEL(lblEBKop), TRUE);
	}
	else
		if (strcmp(testua, "-")==0)
		{
			int k = atoi(kopurua) -1;
			sprintf(kopurua, "<span size='xx-large'>%d</span>", k);
			gtk_label_set_text(GTK_LABEL(lblEBKop), kopurua);
			gtk_label_set_use_markup(GTK_LABEL(lblEBKop), TRUE);
		}
		else
			if (strcmp(testua, "D")==0)
			{
				int k = atoi(kopurua) /10;
				sprintf(kopurua, "<span size='xx-large'>%d</span>", k);
				gtk_label_set_text(GTK_LABEL(lblEBKop), kopurua);
				gtk_label_set_use_markup(GTK_LABEL(lblEBKop), TRUE);
			}
			else
			{
				if (strcmp(kopurua, "0")==0)
				{
					sprintf(kopurua, "<span size='xx-large'>%s</span>", testua);
					gtk_label_set_text(GTK_LABEL(lblEBKop), kopurua);
					gtk_label_set_use_markup(GTK_LABEL(lblEBKop), TRUE);
				}
				else
				{
					sprintf(kopurua, "<span size='xx-large'>%d%d</span>", atoi(kopurua), atoi(testua));
					gtk_label_set_text(GTK_LABEL(lblEBKop), kopurua);
					gtk_label_set_use_markup(GTK_LABEL(lblEBKop), TRUE);
				}
			}
}

static void btmAdos()
{
	MYSQL_ROW row, row2;
	int i, kop;
	char sql[200];
	char testua[5];

	bazkideKop = atoi(gtk_label_get_text(GTK_LABEL(lblBKop)));
	ezBazkideKop = atoi(gtk_label_get_text(GTK_LABEL(lblEBKop)));

	i=0;
	mysql_data_seek(rstAukerak, 0);
	while ((row=mysql_fetch_row(rstAukerak))!=NULL)
	{
		sprintf(sql, "SELECT count(*) from Gaiak,Elkartea where Elkartea.Gaikodea = Gaiak.GKodea AND Gaiak.AKodea = %d", atoi(row[2]));
		mysql_query(dbElkartea, sql);
		rstGaiak = mysql_store_result(dbElkartea);
		row2 = mysql_fetch_row(rstGaiak);
		kop=atoi(row2[0]);

		gaia *lag;
		lag = arrGaiak[i];
		int k;
		for (k=0; k<kop; k++)
		{
			sprintf(testua, "%d", lag[k].Menpekotasuna);
			switch (testua[0])
			{
				case '1': lag[k].Zenbat = bazkideKop + ezBazkideKop;
					break;
				case '2': lag[k].Zenbat = ezBazkideKop;
					break;
				case '3': lag[k].Zenbat = bazkideKop;
					break;
				case '4': if (lag[k].Zenbat!=0)
						lag[k].Zenbat=bazkideKop+ezBazkideKop;
				default: break;
			}
		}
		arrGaiak[i]=lag;
		i++;
	}
	gtk_main_quit();
	gtk_widget_destroy(frmGaldera);
}

void galdera(GtkWidget *lehioa)
{
	GtkWidget *frame;
	GtkWidget *vBox, *hBox;
	GtkWidget *labela;
	GtkWidget *botoia;
	GtkWidget *alignment;
	char *zenb;

	/* Lehioa sortu eta kofiguratu */
	frmGaldera = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (frmGaldera), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_modal (GTK_WINDOW (frmGaldera), TRUE);
	gtk_window_set_decorated (GTK_WINDOW (frmGaldera), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW (frmGaldera), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_transient_for(GTK_WINDOW(frmGaldera), GTK_WINDOW(lehioa));

	/* Lehioko egitura sortu eta kokatu */
	frame = gtk_frame_new("");
	gtk_container_add(GTK_CONTAINER(frmGaldera), frame);
	gdk_color_parse("#293966", &kolorea);
	gtk_widget_modify_bg(frame, GTK_STATE_NORMAL, &kolorea);

	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 12, 12, 12, 12);

	vBox = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(alignment), vBox);

	/* Lehioko egiturak sortu eta kokatzen joan */
	labela = gtk_label_new("<span size='xx-large'><b>Zenbat pertsona etorri zarete?</b></span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_fg(labela, GTK_STATE_NORMAL, &kolorea);
	gtk_box_pack_start(GTK_BOX(vBox), labela, FALSE, FALSE, 0);

	hBox = gtk_hbox_new(FALSE, 3);
	labela = gtk_label_new("<span size='x-large'>Bazkideak:</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	gtk_widget_modify_fg(labela, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("#545357", &kolorea);
	gtk_widget_modify_bg(labela, GTK_STATE_NORMAL, &kolorea);
	gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
	lblBKop = gtk_label_new("<span size='xx-large'>0</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblBKop), TRUE);
	gtk_widget_modify_bg(lblBKop, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblBKop, GTK_STATE_NORMAL, &kolorea);
	gtk_box_pack_start(GTK_BOX(hBox), lblBKop, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	hBox = gtk_hbox_new(TRUE, 0);
	labela = gtk_label_new("<span size='x-large'>0</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_widget_set_size_request(botoia, 60, 60);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="0";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>1</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="1";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>2</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="2";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>3</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="3";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>4</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="4";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>5</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="5";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>6</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="6";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>7</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="7";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>8</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="8";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>9</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="9";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>+</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="+";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>-</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="-";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>D</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	zenb="D";
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia), (gpointer) zenb);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	hBox = gtk_hbox_new(FALSE, 3);
	labela = gtk_label_new("<span size='x-large'>Ez Bazkideak:</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	gdk_color_parse("white", &kolorea);
	gtk_widget_modify_fg(labela, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("#545357", &kolorea);
	gtk_widget_modify_bg(labela, GTK_STATE_NORMAL, &kolorea);
	gtk_box_pack_start(GTK_BOX(hBox), labela, FALSE, FALSE, 0);
	lblEBKop = gtk_label_new("<span size='xx-large'>0</span>");
	gtk_label_set_use_markup(GTK_LABEL(lblEBKop), TRUE);
	gtk_widget_modify_bg(lblEBKop, GTK_STATE_NORMAL, &kolorea);
	gdk_color_parse("yellow", &kolorea);
	gtk_widget_modify_fg(lblEBKop, GTK_STATE_NORMAL, &kolorea);
	gtk_box_pack_start(GTK_BOX(hBox), lblEBKop, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	hBox = gtk_hbox_new(TRUE, 0);
	labela = gtk_label_new("<span size='x-large'>0</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_widget_set_size_request(botoia, 60, 60);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="0";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>1</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="1";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>2</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="2";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>3</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="3";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>4</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="4";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>5</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="5";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>6</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="6";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>7</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="7";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>8</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="8";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>9</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="9";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>+</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="+";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>-</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="-";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	labela = gtk_label_new("<span size='x-large'>D</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	gtk_box_pack_start(GTK_BOX(hBox), botoia, TRUE, TRUE, 0);
	zenb="D";
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmZenbakia2), (gpointer) zenb);
	gtk_box_pack_start(GTK_BOX(vBox), hBox, FALSE, FALSE, 0);

	/* Ados eta Atzera botoiak sortu eta sartu */
	labela = gtk_label_new("<span size='x-large'>Ados</span>");
	gtk_label_set_use_markup(GTK_LABEL(labela), TRUE);
	botoia = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(botoia), labela);
	g_signal_connect(G_OBJECT(botoia), "clicked",
			G_CALLBACK(btmAdos), NULL);
	gtk_widget_set_size_request(botoia, 100, 50);
	gtk_box_pack_start(GTK_BOX(vBox), botoia, FALSE, FALSE, 20);

	/* Dena bistaratu eta martxan jarri */
	form_load();
	gtk_widget_show_all(frmGaldera);
	gtk_main();
}
