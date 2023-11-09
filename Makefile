CC = gcc
SRC = table.c helper.c commands.c main.c
OBJS = $(SRC:.c=.o)
EXEC = ezdb

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(OBJS) $(EXEC)