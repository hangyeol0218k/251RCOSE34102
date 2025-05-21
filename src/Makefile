CC = gcc
CFLAGS = -Wall -g

TARGET = main

OBJS = main.o process.o config.o scheduler.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)