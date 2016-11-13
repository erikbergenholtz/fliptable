CC=gcc
CFLAGS=-c -Wall
LDFLAGS=

EXECUTABLE=bin/tableflipper

all: ${EXECUTABLE}

${EXECUTABLE}: bin/tableflipper.o
	${CC} $^ -o $@

bin/tableflipper.o: src/tableflipper.c
	@mkdir bin/
	${CC} $< ${CFLAGS} -o $@

clean:
	@rm -rf bin/
