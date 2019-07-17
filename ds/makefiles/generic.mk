CC = gcc -ansi -pedantic-errors -Wall -Wextra -g -I../include/
HDR = $(shell gcc -I../include/ -MM ../src/$(NAMESPACE).c)
HDR := $(filter %.h, $(HDR))
OBJ = $(patsubst ../include/%.h, ../obj/%.o, $(HDR))

../bin/$(NAMESPACE).out : ../obj/$(NAMESPACE)_test.o ../lib/lib$(NAMESPACE).so
	$(CC) -o $@ $^ -lm 

../lib/lib$(NAMESPACE).so : $(OBJ)
	$(CC) -shared -o $@  $^

../obj/%.o : ../src/%.c
	$(CC) -c -fPIC -o $@ $<
	
../obj/$(NAMESPACE)_test.o : ../test/$(NAMESPACE)_test.c $(OBJ)
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
		rm ../obj/*.o
