CC=gcc
CFLAGS=-c -Wall
LDFLAGS=

EXECUTABLE=bin/fliptable

all: ${EXECUTABLE}

${EXECUTABLE}: bin/tableflipper.o
	${CC} $^ -o $@

bin/tableflipper.o: src/tableflipper.c
	@mkdir -p bin/
	${CC} $< ${CFLAGS} -o $@

clean:
	@rm -rf bin/
