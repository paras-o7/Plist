CFLAGS = -std=c99 -Wall -W

all: main.o plist.o
	gcc -o bin main.o plist.o ${CFLAGS}

main.o: main.c plist.h
	gcc -c main.c ${CFLAGS}

plist.o: plist.c plist.h
	gcc -c plist.c ${CFLAGS}

clean:
	rm main.o plist.o bin