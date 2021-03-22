# Autoconf/automake file

bin_PROGRAMS = test_coachella

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_LDFLAGS = ${LDFLAGS}

objects = test.o
TARGETS = $(bin_PROGRAMS)

all: $(bin_PROGRAMS)

install:
	mkdir -p ${prefix}/tests
	cp test_coachella ${prefix}/tests

test_coachella: $(objects)
	$(CC) -o $@ $^ $(AM_CFLAGS) -L../src -lcoachella $(AM_LDFLAGS)

$(objects): %.o: %.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS) -I../src/ $(AM_CFLAGS)
