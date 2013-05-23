include $(GOROOT)/src/Make.inc

OBJS=vector_user vector_system vector_system_row matrix_user matrix_system matrix_system_row
LOGS=gothreads1.log gothreads2.log gothreads3.log

all: $(OBJS)

vector_user:
	6g $@.go
	6l -o $@ $@.6

vector_system:
	6g $@.go
	6l -o $@ $@.6

vector_system_row:
	6g $@.go
	6l -o $@ $@.6

matrix_user:
	6g $@.go
	6l -o $@ $@.6

matrix_system:
	6g $@.go
	6l -o $@ $@.6

matrix_system_row:
	6g $@.go
	6l -o $@ $@.6

test1:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 800 900 3000' ; (time ../../bin/$(obj) 800 900 3000) >> gothreads1.log 2>&1; echo 'Fin test';)
test2:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 90 8000' ; (time ../../bin/$(obj) 8000 90 8000) >> gothreads2.log 2>&1; echo 'Fin test';)
test3:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 10 80000' ; (time ../../bin/$(obj) 8000 10 80000) >> gothreads3.log 2>&1; echo 'Fin test';)

tests:
	make test1 && make test2 && make test3

clean:
	rm -f *.6 $(OBJS) $(LOGS)
