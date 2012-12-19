CC=gcc

all : libgonatureanimal.so libgonaturemonkey.so libgomankindhuman.so libgodigitalcomp.so start gir2 humangir

MY_CFLAGS = `pkg-config --cflags gtk+-2.0 gobject-introspection-1.0`
MY_LIBS = `pkg-config --libs gtk+-2.0 gobject-introspection-1.0`

#=============================================================

LIB_DIR = lib
libgonatureanimal_SOURCES = $(LIB_DIR)/go_nature.c
libgonatureanimal_HEADERS = $(LIB_DIR)/go_nature.h
libgonatureanimal_OBJECTS = $(libgonatureanimal_SOURCES:.c=.o)

libgonatureanimal.so: $(libgonatureanimal_OBJECTS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ $(MY_LIBS) -lc -g
	sudo cp $@ /usr/lib

$(LIB_DIR)/%.o : $(LIB_DIR)/%.c $(libgonatureanimal_HEADERS)
	$(CC) -fPIC $(CFLAGS) $(MY_CFLAGS) -c $< -o $@

#=============================================================

LIB_DIR = lib
libgonaturemonkey_SOURCES = $(LIB_DIR)/go_monkey.c
libgonaturemonkey_HEADERS = $(LIB_DIR)/go_monkey.h
libgonaturemonkey_OBJECTS = $(libgonaturemonkey_SOURCES:.c=.o)

libgonaturemonkey.so: $(libgonaturemonkey_OBJECTS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ $(MY_LIBS) -lc -g
	sudo cp $@ /usr/lib

$(LIB_DIR)/%.o : $(LIB_DIR)/%.c $(libgonatureanimal_HEADERS)
	$(CC) -fPIC $(CFLAGS) $(MY_CFLAGS) -c $< -o $@

#=============================================================

LIB_DIR = lib
libgomankindhuman_SOURCES = $(LIB_DIR)/go_human.c
libgomankindhuman_HEADERS = $(LIB_DIR)/go_human.h
libgomankindhuman_OBJECTS = $(libgomankindhuman_SOURCES:.c=.o)

libgomankindhuman.so: $(libgomankindhuman_OBJECTS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ $(MY_LIBS) -lc -g
	sudo cp $@ /usr/lib

$(LIB_DIR)/%.o : $(LIB_DIR)/%.c $(libgomankindhuman_HEADERS)
	$(CC) -fPIC $(CFLAGS) $(MY_CFLAGS) -c $< -o $@

#=============================================================


LIB_DIR = lib
libgodigitalcomp_SOURCES = $(LIB_DIR)/go_digital.c
libgodigitalcomp_HEADERS = $(LIB_DIR)/go_digital.h
libgodigitalcomp_OBJECTS = $(libgodigitalcomp_SOURCES:.c=.o)

libgodigitalcomp.so: $(libgodigitalcomp_OBJECTS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ $(MY_LIBS) -lc -g
	sudo cp $@ /usr/lib

$(LIB_DIR)/%.o : $(LIB_DIR)/%.c $(libgodigitalcomp_HEADERS)
	$(CC) -fPIC $(CFLAGS) $(MY_CFLAGS) -c $< -o $@

#=============================================================

start_SOURCES = go_main.c
start_HEADERS = lib/*.h
start_OBJECTS = $(start_SOURCES:.c=.o)
start_LDFLAGS = -lgonatureanimal -lgonaturemonkey -lgomankindhuman -lgodigitalcomp -L.
start_CFLAGS = -I./lib

start: $(start_OBJECTS)
	$(CC) -o $@ $^ $(MY_LIBS) $(start_LDFLAGS)

%.o : %.c $(start_HEADERS)
	$(CC) $(MY_CFLAGS) -DGOIS $(CFLAGS) $(start_CFLAGS) -c $< -o $@ -g


gir:
	g-ir-scanner --namespace=Nature --nsversion=1.0 --pkg=gtk+-2.0 --pkg=gobject-2.0 --include=GObject-2.0 --program=./start -lgonatureanimal ./lib/go_nature.h -o Nature-1.0.gir --warn-all
	g-ir-compiler Nature-1.0.gir -o Nature-1.0.typelib
	sudo cp Nature-1.0.gir /usr/share/gir-1.0/
	sudo cp Nature-1.0.typelib /usr/lib/girepository-1.0/

#creating gir for both classes
gir2:
	g-ir-scanner --namespace=Nature --nsversion=1.0 --pkg=gtk+-2.0 --include=GObject-2.0 --program=./start ./lib/go_nature.h ./lib/go_monkey.h -lgonatureanimal -lgonaturemonkey -o Nature-1.0.gir --warn-all
	g-ir-compiler Nature-1.0.gir -o Nature-1.0.typelib
	sudo cp Nature-1.0.gir /usr/share/gir-1.0/
	sudo cp Nature-1.0.typelib /usr/lib/girepository-1.0/

humangir:
	g-ir-scanner --namespace=Mankind --nsversion=1.0 --pkg=gtk+-2.0 --include=GObject-2.0 --include=Nature-1.0 --program=./start ./lib/go_human.h -lgomankindhuman -o Mankind-1.0.gir --warn-all
	g-ir-compiler Mankind-1.0.gir -o Mankind-1.0.typelib
	sudo cp Mankind-1.0.typelib /usr/lib/girepository-1.0/

compgir:
	g-ir-scanner --namespace=Digital --nsversion=1.0 --pkg=gtk+-2.0 --include=GObject-2.0 --program=./start ./lib/go_digital.h -lgodigitalcomp -o Digital-1.0.gir --warn-all
	g-ir-compiler Digital-1.0.gir -o Digital-1.0.typelib
	sudo cp Digital-1.0.typelib /usr/lib/girepository-1.0/

.PHONY : clean
clean:
	rm -f lib/*.o *.so  *.o Nature* Mankind* start *~
	sudo rm -f /usr/lib/girepository-1.0/Nature-1.* /usr/share/gir-1.0/Nature-1* /usr/lib/girepository-1.0/Mankind-1.*
	@echo "Clean Done"
