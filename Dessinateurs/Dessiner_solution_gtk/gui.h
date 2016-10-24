#ifndef _GUI_
#define _GUI_

#include "info.h"
#include "outils_dessin.h"


typedef struct Gui {
	GtkWidget *window, *main_box, *top_box, *area;
	GtkWidget *quit_button, *zoom_spin, *show_txt_on_objs_check;
	Info *info;
} Gui;

/** Initialisation */

void gui_init        (Gui *gui, Info *info);
void gui_init_window (Gui *g);
void gui_init_layout (Gui *g);
void gui_init_area   (Gui *g);
void gui_init_quit_button            (Gui *g);
void gui_init_zoom_spin              (Gui *g);
void gui_init_show_txt_on_objs_check (Gui *g);


/** Handlers */

gboolean on_delete_event (GtkWidget *widget, GdkEvent *e, gpointer data);
void on_destroy (GtkWidget U *widget, gpointer U data);
void on_quit_button_clicked (GtkButton *button, gpointer data);
void on_zoom_spin_value_changed (GtkSpinButton *spin, gpointer data);
void on_show_txt_on_objs_check_toggled (GtkToggleButton *toggle, gpointer data);
gboolean on_area_expose (GtkWidget *widget, GdkEventExpose *e, gpointer data);


/** Dessin du remplisage */

void gui_draw_area       (GtkWidget *widget, GdkGC *gc);
void gui_draw_packing    (Gui *g, GtkWidget *widget, GdkGC *gc);
void gui_draw_pack_charachteristics (Gui *g, GdkGC *gc);
void gui_draw_container  (Info *info, GtkWidget *widget, GdkGC *gc);
void gui_draw_objects    (Gui *g, GtkWidget *widget, GdkGC *gc);


#endif  /* _GUI_ */
