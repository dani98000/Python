NAMESPACE = $(patsubst ../src/%.c, %, $(wildcard ../src/*.c))

all: $(NAMESPACE)

$(NAMESPACE): 
	$mmake -f ../makefiles/generic.mk NAMESPACE=$@ 
