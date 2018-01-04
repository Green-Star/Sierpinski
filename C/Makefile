SRCDIR=./src
OBJDIR=./obj
BINDIR=./bin
HEADDIR=./inc
_HEADERS=$(ls ($HEADDIR)/*)
_OBJS=sierpinski.o bitmap.o

CC=gcc
CFLAGS=-Wall -I$(HEADDIR)

all: $(BINDIR)/sierpinski

HEADERS=$(patsubst %,$(HEADDIR)/%,$(_HEADERS))
OBJS=$(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

$(BINDIR)/sierpinski: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(OBJS)
	rm -f $(BINDIR)/sierpinski

rebuild: clear clean all

clear:
	clear
