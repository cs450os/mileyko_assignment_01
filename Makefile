CC      = gcc
CFLAGS  = -std=c11 -O2 -Wall -Wextra -Wpedantic -D_GNU_SOURCE
TARGET  = procs
OBJS    = main.o procs.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o:  main.c procs.h
procs.o: procs.c procs.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
