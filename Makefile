CC = gcc -std=c17

CFLAGS = -c -Wall -Werror -Wextra

all: Hamlet

Hamlet: main.o Hamlet.o Sorting.o
	$(CC) Objects/main.o Objects/Hamlet.o Objects/Sorting.o ../My_Lib/My_Lib.a -o Hamlet.out

main.o: main.c
	$(CC) $(CFLAGS) main.c -o Objects/main.o

Hamlet.o: Hamlet.c
	$(CC) $(CFLAGS) Hamlet.c -o Objects/Hamlet.o

Sorting.o: Sorting.c
	$(CC) $(CFLAGS) Sorting.c -o Objects/Sorting.o

run:
	./Hamlet.out "hamlet.txt" "sorted.txt"

clean:
	rm -rf Objects/main.o Objects/Hamlet.o Objects/Sorting.o
	rm Hamlet.out

clean_log:
	rm log_file.log
