# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_LDFLAGS = ${LDFLAGS}

TARGETS = libcvlsu.a libcvlsu.so

all: $(TARGETS)

install:
	mkdir -p ${prefix}
	mkdir -p ${prefix}/lib
	mkdir -p ${prefix}/include
	cp libcvlsu.so ${prefix}/lib
	cp libcvlsu.a ${prefix}/lib
	cp cvlsu.h ${prefix}/include

libcvlsu.a: cvlsu_static.o 
	$(AR) rcs $@ $^

libcvlsu.so: cvlsu.o
	$(CC) -shared $(AM_CFLAGS) -o libcvlsu.so $^ $(AM_LDFLAGS)

cvlsu.o: cvlsu.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY -o $@ -c $^ $(AM_CFLAGS)
	
cvlsu_static.o: cvlsu.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS)
	
clean:
	rm -rf $(TARGETS)
	rm -rf *.o 

