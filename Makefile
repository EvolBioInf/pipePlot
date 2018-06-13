CC=gcc
CFLAGS= -O3 -Wall -Wshadow -pedantic -std=gnu99 -g
# The source files, object files, libraries and executable name.
SRCFILES= pipePlot.c interface.c eprintf.c
OBJFILES= pipePlot.o interface.o eprintf.o
LIBS= -lm
EXECFILE=pipePlot
DIRECTORY=PipePlot
# The make rule for the executable
.PHONY : all
all : $(EXECFILE)
$(EXECFILE) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(EXECFILE) $(OBJFILES) $(LIBS)
$(EXECFILE).o: interface.h eprintf.h
interface.o: interface.h
eprintf.o: eprintf.h

# Other Standard make rules
lint : 
	lint $(SRCFILES) | more
clean:
	rm -f *.o *~
