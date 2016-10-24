SHELL  = /bin/bash
CC     = gcc
CFLAGS = -Wall -W -ansi -pedantic
LIBS   = -L/usr/X11R6/lib -lX11 -lXext
RM     = rm -f
EXECS = dessiner_solution 

#DEBUG = 1
ifdef DEBUG
	CFLAGS += ggdb
endif

#OPT = 1
ifdef OPT
	CFLAGS += -O2
endif

.c.o :
	$(CC) -c $(CFLAGS) $*.c

help ::
	@echo "Options du make : help all clean distclean"

all :: $(EXECS) 

$(EXECS) : % : %.o ez-draw.o 
	$(CC) -o $@ $^ $(LIBS)

clean ::
	$(RM) *.o core

distclean :: clean
	$(RM) *% *~ $(EXECS)
