CC=gcc
CFLAGE=-Wall 

main:main.o psort.o isort.o ssort.o shell.o quick.o msort.o
	$(CC) $^ $(CFLAGE) -o $@

#%.o:%.c
#	$(CC) $^ $(CFLAGE) -c 

clean:
	-rm *.o main 
