CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
INCLUDES = -I/usr/include/SDL2/
LIBS = -lSDL2 -lSDL2_ttf
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

TARGET = snek

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)