
OBJS := main.o sched.o tracepoint.o

CC := gcc
CFLAGS := -g

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

	
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<