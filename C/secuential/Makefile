# Makefile

CC=gcc
CFLAGS=-g -Wall

OBJS=secuential_vector secuential_vector_inter secuential_vector_noacum secuential_matrix secuential_matrix_inter secuential_matrix_noacum
LOGS=secuential1.log secuential2.log secuential3.log

all: $(OBJS)

debug:
	make "CFLAGS=-g -Wall -DDEBUG"

secuential_vector.o: secuential_vector.c
secuential_vector_inter.o: secuential_vector_inter.c
secuential_vector_noacum.o: secuential_vector_noacum.c
secuential_matrix.o: secuential_matrix.c
secuential_matrix_inter.o: secuential_matrix_inter.c
secuential_matrix_noacum.o: secuential_matrix_noacum.c

secuential_vector: secuential_vector.o
	$(CC) -o $@ $@.o

secuential_vector_inter: secuential_vector_inter.o
	$(CC) -o $@ $@.o

secuential_vector_noacum: secuential_vector_noacum.o
	$(CC) -o $@ $@.o

secuential_matrix: secuential_matrix.o
	$(CC) -o $@ $@.o

secuential_matrix_inter: secuential_matrix_inter.o
	$(CC) -o $@ $@.o

secuential_matrix_noacum: secuential_matrix_noacum.o
	$(CC) -o $@ $@.o

test1:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 800 900 3000' ; (time ../bin/$(obj) 800 900 3000) >> secuential1.log 2>&1; echo 'Fin test';)
test2:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 90 8000' ; (time ../bin/$(obj) 8000 90 8000) >> secuential2.log 2>&1; echo 'Fin test';)
test3:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 10 80000' ; (time ../bin/$(obj) 8000 10 80000) >> secuential3.log 2>&1; echo 'Fin test';)

tests:
	make test1 && make test2 && make test3

clean:
	rm -f *.o $(OBJS) $(LOGS)
