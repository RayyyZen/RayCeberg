CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lncursesw
SRCDIR = source
INCDIR = include

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=%.o)
TARGET = RayCeberg

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)
	rm -f $(OBJS)

%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

run: all
	./$(TARGET)