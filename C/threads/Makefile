# Makefile

CC=gcc
CFLAGS=-g -Wall

OBJS=matrix_user matrix_system matrix_system_row vector_user vector_system vector_system_row
LOGS=threads1.log threads2.log threads3.log

all: $(OBJS)

debug:
	make "CFLAGS=-g -Wall -DDEBUG"

matrix_user.o: matrix_user.c
matrix_system.o: matrix_system.c
matrix_system_row.o: matrix_system_row.c
vector_user.o: vector_user.c
vector_system.o: vector_system.c
vector_system_row.o: vector_system_row.c

matrix_user: matrix_user.o
	$(CC) $(CFLAGS) -lpthread -o $@ $@.o

matrix_system: matrix_system.o
	$(CC) $(CFLAGS) -lpthread -o $@ $@.o

matrix_system_row: matrix_system_row.o
	$(CC) $(CFLAGS) -lpthread -o $@ $@.o

vector_user: vector_user.o
	$(CC) $(CFLAGS) -lpthread -o $@ $@.o

vector_system: vector_system.o
	$(CC) $(CFLAGS) -lpthread -o $@ $@.o

vector_system_row: vector_system_row.o
	$(CC) $(CFLAGS) -lpthread -o $@ $@.o

test1:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 800 900 3000' ; (time ../bin/$(obj) 800 900 3000) >> threads1.log 2>&1; echo 'Fin test';)
test2:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 90 8000' ; (time ../bin/$(obj) 8000 90 8000) >> threads2.log 2>&1; echo 'Fin test';)
test3:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 10 80000' ; (time ../bin/$(obj) 8000 10 80000) >> threads3.log 2>&1; echo 'Fin test';)

tests:
	make test1 && make test2 && make test3

clean:
	rm -f *.o $(OBJS) $(LOGS)
