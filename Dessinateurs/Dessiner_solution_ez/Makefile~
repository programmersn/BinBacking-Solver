# Makefile pour EZ-Draw
#
# 21/06/2011 - Edouard.Thiel@lif.univ-mrs.fr

# Variables pour systemes Unix/X11 (linux, Mac OS, etc)
SHELL  = /bin/bash
CC     = gcc
CFLAGS = -Wall -W -ansi -pedantic -g
LIBS   = -L/usr/X11R6/lib -lX11 -lXext
RM     = rm -f

# Rajoutez vos executables a la fin de EXECS ou EXECS_M
# (dans EXEC_M, les programmes seront compile's avec -lm)
#
EXECS = dessiner_solution 

.c.o :
	$(CC) -c $(CFLAGS) $*.c

help ::
	@echo "Options du make : help all ln clean distclean"

all :: $(EXECS) 


# Cette double dependance un peu speciale est de la syntaxe GNU-make ;
# elle est equivalente a
#     demo0 : demo0.o ez-draw.o
#     demo1 : demo1.o ez-draw.o
#     ...
#     $(EXECS) :
#	      $(CC) -o $@ $^ $(LIBS)

$(EXECS) : % : %.o ez-draw.o 
	$(CC) -o $@ $^ $(LIBS)

clean ::
	$(RM) *.o core

distclean :: clean
	$(RM) *% *~ $(EXECS) $(EXECS_M)

# Cette cible cree un lien $HOME/ez-draw vers votre repertoire d'installation
ln ::
	@P=`pwd` ; N="$${HOME}/ez-draw" ;\
	if [ -h "$$N" ]; then mv -f "$$N" "$$N.old" ; fi ;\
	echo "ln -s \"$$P\" \"$$N\"" ; ln -s "$$P" "$$N" 
