OBJS = Test.o cJSON.o
CC = gcc
CFLAGS = -c


Test:$(OBJS)
	$(CC) -o Test $(OBJS) -lm
Test.o:Test.c
	$(CC) $(CFLAGS) Test.c 
cJSON.o:cJSON.c
	$(CC) $(CFLAGS) cJSON.c

.PHONY:clean
clean:
	rm -rf *.o unittest
	@echo "Clean done!"

