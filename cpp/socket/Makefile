CC = g++
CFLAGS = -c -Wall
INCLUDES = # use -I/path/to/directory
LDFLAGS =  # use -L/path/to/libs/directory
LFLAGS =   # use -lnameOfLib

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(patsubst %.cc, %.o, $(wildcard *.cc)))

.PHONY: all clean

all: $(OBJDIR) $(OBJ)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(OBJDIR)
