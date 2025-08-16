CFLAGS = -std=c99 -Wall -W

all: main.o plist.o
	gcc -o bin main.o plist.o ${CFLAGS} 

debug: main.o plist.o
	gcc -o bin main.o plist.o ${CFLAGS} -g

main.o: main.c plist.h
	gcc -c main.c ${CFLAGS} -g

plist.o: plist.c plist.h
	gcc -c plist.c ${CFLAGS} -g

clean:
	rm main.o plist.o bin