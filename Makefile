# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cris <cris@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 14:04:41 by csuomins          #+#    #+#              #
#    Updated: 2026/06/18 19:31:53 by cris             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRCS = main.c \
       inits.c \
       monitor.c \
       philo_routine.c \
       start_simulations.c \
       utils.c

OBJS = $(SRCS:.c=.o)

# Colors
RESET  = \033[0m
GREEN  = \033[1;32m
YELLOW = \033[1;33m
RED    = \033[1;31m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)[LINK]$(RESET) Building $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)[OK]$(RESET) $(NAME) compiled successfully."

%.o: %.c philo.h
	@echo "$(YELLOW)[CC]$(RESET) Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "$(RED)[CLEAN]$(RESET) Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[FCLEAN]$(RESET) $(NAME) removed."

re: fclean all

.PHONY: all clean fclean re