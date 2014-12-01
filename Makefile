CC = gcc
CFLAGS =
OBJECTS = lkm.o
INCFLAGS = -w
LDFLAGS =
LIBS =

all: lkm

lkm: $(OBJECTS)
	$(CC) -o lkm $(OBJECTS) $(LDFLAGS) $(LIBS)


.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o
	rm -f lkm
