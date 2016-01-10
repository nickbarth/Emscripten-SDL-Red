CC?=gcc
CFLAGS?=-I/usr/local/include -L/usr/local/lib -lSDL -lSDLmain -lSDL -Wl,-framework,Cocoa
EMFLAGS?=-I/usr/local/include -L/usr/local/lib -lSDL -lSDLmain -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -L/usr/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa -s USE_SDL=1

.PHONY: all main js clean

all: main

js:
	@echo --- JS ---
	emcc main.c ${EMFLAGS} -o main.html

main: main.c
	@echo --- C ---
	${CC} -O3 main.c ${CFLAGS} -o main

clean:
	rm -f main main.html main.js
