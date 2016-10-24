#include <stdio.h>
#include <stdlib.h>
#include "gui.h"
#include "lecture_solution.h"

/** ------------------- I N I T I A L I S A T I O N S -----------------------*/

void gui_init (Gui *g, Info *info)
{
	g->info = info;
	
	gui_init_window (g);
	gui_init_layout (g);
	gui_init_area   (g);
	gui_init_quit_button (g);
	gui_init_zoom_spin   (g);
	gui_init_show_txt_on_objs_check (g);
}

void gui_init_window (Gui *g)
{
	g->window = gtk_window_new  (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (g->window), 1100, 700);
	gtk_window_set_title        (GTK_WINDOW (g->window), 
															 "Packing  :  dessin du remplissage");
	
	g_signal_connect (g->window, "delete-event", G_CALLBACK (on_delete_event),
										g);
	
	g_signal_connect (g->window, "destroy", G_CALLBACK (on_destroy), g);
}

void gui_init_layout (Gui *g)
{	
	g->main_box = gtk_vbox_new (!HOMOGENEOUS, 5);
	gtk_container_add (GTK_CONTAINER (g->window), g->main_box);
	
	g->top_box = gtk_hbox_new (!HOMOGENEOUS, 5);
	gtk_box_pack_start (GTK_BOX (g->main_box), g->top_box, !EXPAND, !FILL, 5);
}

void gui_init_area (Gui *g)
{	
	g->area = gtk_drawing_area_new ();
	gtk_box_pack_start (GTK_BOX (g->main_box), g->area, EXPAND, FILL, 5);
	g_signal_connect (g->area, "expose-event", G_CALLBACK (on_area_expose), g);
}

void gui_init_quit_button (Gui *g)
{
	g->quit_button = gtk_button_new_with_label ("Quitter");
	gtk_box_pack_start (GTK_BOX (g->top_box), g->quit_button, !EXPAND, !FILL, 15);
	g_signal_connect (g->quit_button, "clicked", 
									  G_CALLBACK (on_quit_button_clicked), g);
}

void gui_init_zoom_spin (Gui *g)
{
	g->zoom_spin = gtk_spin_button_new_with_range (0.1, 50, 0.01);
	gtk_box_pack_start (GTK_BOX (g->top_box), g->zoom_spin, !EXPAND, !FILL, 20);
	g_signal_connect (g->zoom_spin, "value-changed", 
									  G_CALLBACK (on_zoom_spin_value_changed), g);
	
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (g->zoom_spin), g->info->zoom);
}

void gui_init_show_txt_on_objs_check (Gui *g)
{
	GtkWidget *toggle = g->show_txt_on_objs_check;
	
	toggle = gtk_check_button_new_with_label 
															("Afficher les noms sur les objets");
	gtk_box_pack_start (GTK_BOX(g->top_box), toggle, !EXPAND, !FILL, 20);
	g_signal_connect (toggle, "toggled", 
										G_CALLBACK (on_show_txt_on_objs_check_toggled), g);

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(toggle), 
																g->info->show_txt_on_objs);
}


/** --------------------- H A N D L E R S -----------------------------------*/

gboolean on_delete_event (GtkWidget U *widget, GdkEvent U *e, gpointer U data)
{
	gboolean prevent_from_destroying = FALSE;
	printf("on_delete_event\n");
	
	return prevent_from_destroying;
}

void on_destroy (GtkWidget U *widget, gpointer U data)
{
	printf("on_destroy\n");
	gtk_main_quit ();
}

void on_quit_button_clicked (GtkButton U *button, gpointer U data)
{
	printf("on_quit_button_clicked\n");
	gtk_main_quit ();
}

void on_zoom_spin_value_changed (GtkSpinButton *spin, gpointer data)
{
	Gui *g = data;
	
	g->info->zoom = gtk_spin_button_get_value (spin);
	
	gtk_widget_queue_draw (g->area);
}

void on_show_txt_on_objs_check_toggled (GtkToggleButton *toggle, gpointer data)
{
	Gui *g = data;

	g->info->show_txt_on_objs = gtk_toggle_button_get_active 
															  (GTK_TOGGLE_BUTTON (toggle));
															  
	gtk_widget_queue_draw (g->area);
}

gboolean on_area_expose (GtkWidget *widget, GdkEventExpose U *e, gpointer data)
{
	Gui *g = data;
	GdkGC *gc = gdk_gc_new (widget->window);

	gui_draw_area (widget, gc);
	gui_draw_pack_charachteristics (g, gc);
	gui_draw_packing (g, widget, gc);
	
	g_object_unref (gc);
	
	return TRUE;
}


/** ------------------ D E S S I N    R E M P L I S S A G E -----------------*/

void gui_draw_area (GtkWidget *widget, GdkGC *gc)
{
	guint w = widget->allocation.width, h = widget->allocation.height;
		
	gc_set_rgb_fg (gc, 0xFFFFFF);
	gdk_draw_rectangle (widget->window, gc, TRUE, 0, 0, w, h);
}

void gui_draw_packing (Gui *g, GtkWidget *widget, GdkGC *gc)
{
	gui_draw_container (g->info, widget, gc);
	gui_draw_objects   (g, widget, gc);

	gtk_widget_queue_draw (g->area);
}

void gui_draw_pack_charachteristics (Gui *g, GdkGC *gc)
{
	PangoLayout *pango_layout = gtk_widget_create_pango_layout (g->area, NULL);
	
	font_set_name (pango_layout, "Times, bold 20");
	font_set_size (pango_layout, g->info->size_font);
	font_draw_text (g->area, gc, pango_layout, FONT_TC, 50, 100, "Salam");

	gtk_widget_queue_draw (g->area);
	g_object_unref(pango_layout);
}

void gui_draw_container (Info *info, GtkWidget *widget, GdkGC *gc)
{
	GdkDrawable *drawable = widget->window;
	gdouble z = info->zoom;
	guint x_c = info->x_container-2, y_c = info->y_container-2;
	
	set_color (gc, 0, 50, 20);
	gdk_gc_set_line_attributes (gc, info->container_line_width, GDK_LINE_SOLID,
															GDK_CAP_NOT_LAST, GDK_JOIN_MITER);
	
	gdk_draw_rectangle (drawable, gc, FALSE, x_c, y_c, 
											z*largeur_conteneur+4, z*hauteur_conteneur+4);
}

void gui_draw_objects (Gui *g, GtkWidget *widget, GdkGC *gc)
{
	int i;
	Info *info = g->info;
	GdkDrawable *drawable = widget->window;
	gdouble z = info->zoom;
	guint x_c = info->x_container, y_c = info->y_container;
	guint H = hauteur_conteneur;
	
	for (i = 0; i < nb_obj; i++) {
		set_color (gc, 0, 112, 49);
		gdk_draw_rectangle (drawable, gc, TRUE, x_c + z*Obj_Solution[i]->x,
																						y_c + z*Obj_Solution[i]->y,
																						z*Obj_Solution[i]->l,
																						z*Obj_Solution[i]->h);
		set_color (gc, 255, 255, 255);
		gdk_gc_set_line_attributes (gc, info->objs_line_width, GDK_LINE_SOLID,
																GDK_CAP_NOT_LAST, GDK_JOIN_MITER);
		gdk_draw_rectangle (drawable, gc, FALSE, x_c + z*Obj_Solution[i]->x,
																					   y_c + z*Obj_Solution[i]->y,
																						 z*Obj_Solution[i]->l,
																						 z*Obj_Solution[i]->h);
	}
}

