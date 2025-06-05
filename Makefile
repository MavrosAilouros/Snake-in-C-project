CC = gcc
CFALGS = -Wall -Wextra
INCLUDES = -I/usr/include/SDL2/
LIBS = -lSDL2
SRCS = snake.c
OBJS = $(SRCS:.c=.o)
TARGET = snek

$(TARGET) : $(OBJS)
	$(CC) $(CFALGS) -o $(TARGET) $(OBJS) $(LIBS)

.c .o:
			$(CC) $(CFALGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(TARGET)
