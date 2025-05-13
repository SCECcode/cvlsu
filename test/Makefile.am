# Autoconf/automake file

bin_PROGRAMS = test_cvlsu

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} -I../src
AM_LDFLAGS = ${LDFLAGS} -L../src -lcvlsu

objects = test_api.o
TARGETS = $(bin_PROGRAMS)

all: $(bin_PROGRAMS)

install:
	mkdir -p ${prefix}/tests
	cp test_cvlsu ${prefix}/tests

test_cvlsu$(EXEEXT): $(objects)
	$(CC) -o $@ $^ $(AM_LDFLAGS)

$(objects): %.o: %.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS) 

run_unit : test_cvlsu
	./test_cvlsu

clean :
	rm -rf *~ *.o test_cvlsu

