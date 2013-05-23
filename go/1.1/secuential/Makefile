include $(GOROOT)/src/Make.inc

OBJS=secuential_vector secuential_vector_inter secuential_vector_noacum secuential_matrix secuential_matrix_inter secuential_matrix_noacum
LOGS=gosecuential1.log gosecuential2.log gosecuential3.log

all: $(OBJS)

secuential_vector:
	6g $@.go
	6l -o $@ $@.6

secuential_vector_inter:
	6g $@.go
	6l -o $@ $@.6

secuential_vector_noacum:
	6g $@.go
	6l -o $@ $@.6

secuential_matrix:
	6g $@.go
	6l -o $@ $@.6

secuential_matrix_inter:
	6g $@.go
	6l -o $@ $@.6

secuential_matrix_noacum:
	6g $@.go
	6l -o $@ $@.6

test1:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 800 900 3000' ; (time ../../bin/$(obj) 800 900 3000) >> gosecuancial1.log 2>&1; echo 'Fin test';)
test2:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 90 8000' ; (time ../../bin/$(obj) 8000 90 8000) >> gosecuential2.log 2>&1; echo 'Fin test';)
test3:
	$(foreach obj, $(OBJS), echo 'Comienza test $(obj) 8000 10 80000' ; (time ../../bin/$(obj) 8000 10 80000) >> gosecuential3.log 2>&1; echo 'Fin test';)

tests:
	make test1 && make test2 && make test3

clean:
	rm -f *.6 $(OBJS) $(LOGS)
