#	$(wildcard *.c): include all files "*.c" in the folder
#	patsubst: transform "*.c" to "*.o"
OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
TARGET =sorting

$(TARGET): $(OBJS)
	gcc -o $@ $^

# sorting.o: sorting.c
# 	gcc -c sorting.c

clean:
	rm -f *.o $(TARGET)
	rm -f testGraphe.txt