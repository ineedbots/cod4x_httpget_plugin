CC=gcc
CPP=g++
TARGET_NAME=httpget

ifeq ($(OS),Windows_NT)
EXT=dll
CFLAGS=-m32 -Wall -O1 -g -mtune=core2
LFLAGS=-m32 -g -shared -static-libgcc -static-libstdc++
LIBS=-L.. -lcom_plugin
CLEAN = del *.o
else
EXT=so
CFLAGS=-m32 -Wall -O1 -g -fvisibility=hidden -mtune=core2
LFLAGS=-m32 -g -shared
LIBS=
CLEAN = rm *.o
endif

all: 
	$(CC) $(CFLAGS) $(DFLAGS) -c *.c
	$(CC) $(LFLAGS) -o $(TARGET_NAME).$(EXT) *.o $(LIBS) $(CONVLIB) 
	
clean:
	$(CLEAN)