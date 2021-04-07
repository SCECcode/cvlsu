# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_LDFLAGS = ${LDFLAGS}

TARGETS = libcoachella.a libcoachella.so

all: $(TARGETS)

install:
	mkdir -p ${prefix}
	mkdir -p ${prefix}/lib
	mkdir -p ${prefix}/include
	cp libcoachella.so ${prefix}/lib
	cp libcoachella.a ${prefix}/lib
	cp coachella.h ${prefix}/include

libcoachella.a: coachella_static.o 
	$(AR) rcs $@ $^

libcoachella.so: coachella.o
	$(CC) -shared $(AM_CFLAGS) -o libcoachella.so $^ $(AM_LDFLAGS)

coachella.o: coachella.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY -o $@ -c $^ $(AM_CFLAGS)
	
coachella_static.o: coachella.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS)
	
clean:
	rm -rf $(TARGETS)
	rm -rf *.o 

