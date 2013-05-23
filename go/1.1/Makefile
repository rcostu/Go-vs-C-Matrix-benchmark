# Makefile

DIRS=parallel secuential

all:
	$(foreach dirs, $(DIRS), cd $(dirs); make ; cd ..;)

test1:
	$(foreach dirs, $(DIRS), cd $(dirs); make test1; cd ..;)

test2:
	$(foreach dirs, $(DIRS), cd $(dirs); make test2; cd ..;)

test3:
	$(foreach dirs, $(DIRS), cd $(dirs); make test3; cd ..;)

tests:
	$(foreach dirs, $(DIRS), cd $(dirs); make tests; cd ..;)

clean:
	$(foreach dirs, $(DIRS), cd $(dirs); make clean; cd ..;)
