CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -I/usr/include/SDL2/
LIBS = -lSDL2 -lSDL2_ttf
SRCS = snake.c score.c
OBJS = $(SRCS:.c=.o)
TARGET = snek

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.c .o:
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(TARGET)
