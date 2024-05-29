CC = gcc
TARGET = lab5

$(TARGET): main.o 
	$(CC) $^ -o $@ -lm

main.o: main.c 
	$(CC) -c $<

clean:
	rm -f *.o
