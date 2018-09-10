CC = gcc

SOURCEDIR = .
BUILDDIR = build

EXCUTABLE = $(BUILDDIR)/m_ls
SOURCES = $(wildcard $(SOURCEDIR)/*.c)
OBJECTS = $(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

all : $(EXCUTABLE) 

$(EXCUTABLE) : $(OBJECTS)
	$(CC) -o $(EXCUTABLE) $<

$(OBJECTS) : | $(BUILDDIR)

$(BUILDDIR) : 
	mkdir $(BUILDDIR)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c
	$(CC) -g -c $< -o $@

.PHONY : clean
clean :
	rm -r $(BUILDDIR)

