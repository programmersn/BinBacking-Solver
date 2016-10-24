#include <stdio.h>
#include <stdlib.h>

#include "info.h"

void info_init_default (Info *info) 
{
	info->show_txt_on_objs = FALSE;
	info->zoom = 7;
	info->container_line_width = 3; info->objs_line_width = 1;
	info->x_container = 320; info->y_container = 110;
	info->size_font = 20;
}
