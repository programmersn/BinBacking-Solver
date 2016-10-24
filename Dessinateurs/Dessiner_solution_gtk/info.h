#ifndef _INFO_
#define _INFO_

#include "outils_dessin.h"

typedef struct Info {
	gboolean show_txt_on_objs;
	gdouble zoom;
	guint objs_line_width, container_line_width;
	guint x_container, y_container;
	guint size_font;
} Info;


void info_init_default (Info *info);

#endif  /* _INFO_ */
