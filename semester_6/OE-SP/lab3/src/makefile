CC = gcc
TARGET = morse_convert

$(TARGET): main.o morse.o morse_dictionary.o
	$(CC) $^ -o $@ 

main.o: main.c 
	$(CC) -c $<

morse.o: morse.c
	$(CC) -c $^

morse_dictionary.o: morse_dictionary.c 
	$(CC) -c $^
	
clean:
	rm -f *.o
