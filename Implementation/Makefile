SHELL     = /bin/bash
MAKE      = make
CC        = gcc
CFLAGS    = -W -Wall -ansi -pedantic
LIBS_DRAW = -L/usr/X11R6/lib -lX11 -lXext
OBJS_PACK = main.o lecture_probleme.o recherche_remplissage.o remplir_bande.o utiles.o
OBJS_DRAW = dessiner_solution.o ez-draw.o
PACK      = remplir_conteneur
GEN       = generateur
DRAW      = dessiner_solution
RM        = rm -f

# Uncomment for debugging option :
DEBUG = 1
ifdef DEBUG
	CFLAGS += -ggdb
endif

# Uncomment for optimization option :
#OPTIMIZ = 1
ifdef OPTIMIZ
	CFLAGS += -O2
endif

.PHONY : help all clean depend

help :
	@echo "Options du makefile : help all clean depend"

all : $(PACK) $(GEN) $(DRAW)

.c.o :
	$(CC) $*.c -c $(CFLAGS)

clean :
	$(RM) *.o $(PACK) $(GEN) $(DRAW)

depend :
	makedepend generateur.c lecture_probleme.c recherche_remplissage.c;
	makedepend remplir_bande.c utiles.c main.c ez-draw.c dessiner_solution.c

#----------------------- G E N E R A T E U R ------------------------#

$(GEN) : generateur.o
	$(CC) $^ -o $@ $(CFLAGS)


#------------------------- S O L V E U R ----------------------------#

$(PACK) : $(OBJS_PACK)
	$(CC) $^ -o $@ $(CFLAGS)


#----------------------- D E S S I N A T E U R ----------------------#

$(OBJS_DRAW) :
	$(CC) $*.c -c $(CFLAGS)

$(DRAW) : $(OBJS_DRAW)
	$(CC) $^ -o $@ $(LIBS_DRAW)



# DO NOT DELETE

remplir_bande.o: /usr/include/stdio.h /usr/include/features.h
remplir_bande.o: /usr/include/libio.h /usr/include/_G_config.h
remplir_bande.o: /usr/include/wchar.h /usr/include/stdlib.h
remplir_bande.o: /usr/include/alloca.h /usr/include/assert.h remplir_bande.h
remplir_bande.o: lecture_probleme.h recherche_remplissage.h
utiles.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
utiles.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/stdlib.h
utiles.o: /usr/include/alloca.h /usr/include/string.h /usr/include/xlocale.h
utiles.o: /usr/include/assert.h utiles.h lecture_probleme.h
utiles.o: recherche_remplissage.h remplir_bande.h
main.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/stdlib.h
main.o: /usr/include/alloca.h lecture_probleme.h recherche_remplissage.h
main.o: remplir_bande.h utiles.h
ez-draw.o: ez-draw.h /usr/include/stdio.h /usr/include/features.h
ez-draw.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ez-draw.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h
ez-draw.o: /usr/include/xlocale.h /usr/include/X11/Xlib.h
ez-draw.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
ez-draw.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
ez-draw.o: /usr/include/X11/keysym.h /usr/include/X11/keysymdef.h
ez-draw.o: /usr/include/X11/Xresource.h /usr/include/X11/extensions/Xdbe.h
ez-draw.o: /usr/include/X11/extensions/dbe.h /usr/include/time.h
dessiner_solution.o: /usr/include/stdio.h /usr/include/features.h
dessiner_solution.o: /usr/include/libio.h /usr/include/_G_config.h
dessiner_solution.o: /usr/include/wchar.h /usr/include/stdlib.h
dessiner_solution.o: /usr/include/alloca.h /usr/include/assert.h ez-draw.h
dessiner_solution.o: /usr/include/string.h /usr/include/xlocale.h
dessiner_solution.o: /usr/include/X11/Xlib.h /usr/include/X11/X.h
dessiner_solution.o: /usr/include/X11/Xfuncproto.h /usr/include/X11/Xosdefs.h
dessiner_solution.o: /usr/include/X11/Xutil.h /usr/include/X11/keysym.h
dessiner_solution.o: /usr/include/X11/keysymdef.h
dessiner_solution.o: /usr/include/X11/Xresource.h
dessiner_solution.o: /usr/include/X11/extensions/Xdbe.h
dessiner_solution.o: /usr/include/X11/extensions/dbe.h /usr/include/time.h
dessiner_solution.o: dessiner_solution.h
