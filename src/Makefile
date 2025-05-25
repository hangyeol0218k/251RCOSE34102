# Written with assistance from ChatGPT-4o, May 2025

CC = gcc
CFLAGS = -Wall -g

TARGET = main

OBJS = main.o process.o config.o scheduler.o evaluation.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)