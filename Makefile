EXE = philo
CFLAGS = -Wall -Wextra -Werror

SRC = philo.c \
		messages.c \
		observer.c \
		routine.c \
		utils1.c \
		free.c

OBJS = $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJS)
	cc -g $(CFLAGS) $(OBJS) -o $(EXE)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(EXE)

re: fclean all

.PHONY = all clean fclean re