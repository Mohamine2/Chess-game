# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -IcodeC
LDFLAGS =
SRCS = game.c board.c moves.c
OBJS = $(SRCS:.c=.o)
TARGET = Chess-game

# Règle pour créer l'éxécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Règle pour compiler les fichiers
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour effacer les exécutables
clean:
	rm -f $(OBJS) $(TARGET) *.o

# Règle pour lancer l'éxécutable
run: $(TARGET)
	./$(TARGET)