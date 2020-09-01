CFLAGS += -Wall -Wextra -pedantic -I include/ -MMD -MP 
LDLIBS +=

all: src/fastpng
src/fastpng: src/fastpng.o

.PHONY: clean

clean:
	rm -f src/fastpng
	rm -f src/*.o
	rm -f src/*.d

-include $(wildcard src/*.d)
