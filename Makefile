
CC     = gcc
CCLINK  = $(CC)
CFLAGS = -Wall -g -std=c99
OBJS   = ransom.o
EXEC  = prog.exe


$(EXEC) : $(OBJS)
	$(CCLINK) $(OBJS) -o prog.exe

ransom.o : ransom.c
	$(CC) -c $(CFLAGS) ransom.c


clean:
	rm -fr *.exe $(OBJS)
