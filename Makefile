ODIR=obj
LDIR =lib

CFLAGS= -Wall -O3 -I/usr/local/include -I/usr/include/freetype2/ -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -Iinclude/ngl -Isrc/ngl -Isrc/shaders -I/usr/include/ImageMagick -DNGL_DEBUG
CC=g++ $(CFLAGS)
SRCDIR   = src
OBJDIR   = obj
LIBDIR   = lib

LDFLAGS=-shared -lMagickCore -lMagick++ -lfreetype
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

BUILDLIB=$(LDIR)/libNGL.so

obj/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILDLIB): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.PHONY: clean

clean:
	rm -f src/*.o $(ODIR)/*.o lib/*
