CC = gcc
# CFLAGS = -O2 -Wall -I . -g
CFLAGS = -O0 -Wall -I . -g

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: lock

lock: reentrantLock.c thread.o
	$(CC) $(CFLAGS) -c lock reentrantLock.c \
	thread.o \
	$(LIB)

thread.o: thread.o
	$(CC) $(CFLAGS) -c thread.c

clean:
	rm -rf *.dSYM
	rm -f *.o
	