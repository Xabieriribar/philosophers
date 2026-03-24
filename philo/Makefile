# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xiribar <xiribar@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/24 16:39:00 by xiribar           #+#    #+#              #
#    Updated: 2026/03/24 16:39:00 by xiribar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= -Iincludes
PTHREAD		= -pthread
RM			= rm -f

SRCS		= src/main.c \
			  src/utils/philosophers_utils.c \
			  src/utils/parser_utils.c \
			  src/utils/log_utils.c \
			  src/utils/schedule_utils.c \
			  src/utils/simulation_utils.c \
			  src/utils/simulation_utils2.c \
			  src/utils/simulation_utils3.c \
			  src/utils/init_utils.c \
			  src/utils/mutexes.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PTHREAD) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
