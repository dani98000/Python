CC = gcc -ansi -pedantic-errors -Wall -Wextra -g
src =$(wildcard src/*.c)
obj =$(src:.c=.o)
dep =$(obj:.o=.d) 
LDFLAGS = -lGL -lglut -lpng -lz -lm
mygame:$(obj)
	$(CC) -o $@ $^$(LDFLAGS)
-include $(dep)  

%.d: %.c@$(CPP) $(CFLAGS)$< -MM -MT$(@:.d=.o)>$@



