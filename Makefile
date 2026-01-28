NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c \
       inits.c \
       monitor.c \
       philo_routine.c \
       start_simulations.c \
       utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re