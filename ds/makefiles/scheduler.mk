CC = gcc -ansi -pedantic-errors -Wall -Wextra -g
CFLAGS = -o
RM = rm -f
objects = ../obj/dll.o ../obj/task.o ../obj/uid.o ../obj/scheduler.o \
../obj/srtl.o ../obj/pq.o 

../bin/scheduler.out: ../test/scheduler_test.c ../lib/libscheduler.so 
		$(CC) -o $@ $^

../lib/libscheduler.so: $(objects)
		$(CC) -shared -o $@ $^
	
%.o : %.c
		$(CC) $< -c -fPIC

clean :	 	
		rm $(objects)
