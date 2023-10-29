CC = gcc
SRC = commands.c main.c
OBJS = $(SRC:.c=.o)
EXEC = ezdb

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)