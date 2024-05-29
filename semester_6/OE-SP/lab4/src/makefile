CC = gcc
TARGET = int

$(TARGET): main.o integral.o 
	$(CC) $^ -o $@ -lm

main.o: main.c 
	$(CC) -c $<

integral.o: integral.c
	$(CC) -c $<
	
clean:
	rm -f *.o
