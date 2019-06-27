CC = gcc -ansi -pedantic-errors -Wall -Wextra -g
RM = rm -f
CFLAGS = -std=c1y -MD -MP 
SRC = $(namespace)
all: main

main: $(SRC:%.c=%.o)
		$(cc) $(CFLAGS) -o $@ $^

-include $(SRC:%.cpp=%.d)


../bin/dll.out: ../lib/libdll.so  ../test/dll_test.c 
		$(CC) -o $@ ../test/dll_test.c ../lib/libdll.so

../lib/libdll.so: ../obj/dll.o
		$(CC) -shared -o $@ $^
	

../obj/dll.o: ../src/dll.c ../include/dll.h
		$(CC) -o $@ -fPIC -c $<
		
clean: 
		rm ../obj/dll.o
