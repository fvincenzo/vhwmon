CC=gcc
BISON=bison
FLEX=flex

# DEBUG is set by default
DEBUG ?= 1
ifeq ($(DEBUG), 0)
	CFLAGS=-c -Wall -static
else
	CFLAGS=-DVDEBUG -g -c -Wall -static
endif

LDFLAGS=-static
BFILES=vhwmon-yacc
BFLAGS=--defines=$(BFILES).h --output=$(BFILES).c
LFILES=vhwmon-lex
LFLAGS=--header-file=$(LFILES).h --outfile=$(LFILES).c
SOURCES=vhwmon-main.c vhwmon-parameters.c vhwmon-program.c vhwmon-variables.c\
	vhwmon-opcode.c vhwmon-loops.c vhwmon-instructions.c vhwmon-utilities.c\
	$(BFILES).c $(LFILES).c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=vhwmon

all: bison-flex $(SOURCES) $(EXECUTABLE)

bison-flex:
	$(BISON) $(BFLAGS) $(BFILES).y
	$(FLEX) $(LFLAGS) $(LFILES).l
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o vhwmon $(BFILES).c $(BFILES).h $(LFILES).c $(LFILES).h
