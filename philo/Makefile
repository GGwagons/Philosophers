# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miturk <miturk@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 18:42:25 by ggwagons          #+#    #+#              #
#    Updated: 2024/05/20 14:43:43 by miturk           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	cc
FLAGS		= 	-Wall -Werror -Wextra -pthread #-fsanitize=thread 
RM			=	rm -f
SRC			=	main.c \
				philo.c \
				utils.c \
				utils2.c \
				sleep.c \
				action.c \
				steps.c
				
OBJS		=	$(SRC:.c=.o)

%.o: %.c
			$(CC) $(FLAGS) -c $< -o $@ 

all: 		$(NAME)

philo: 		$(OBJS) 
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:		
			@ $(RM) $(OBJS)


fclean: 	clean
			@ $(RM) $(NAME) 


re: fclean all

.PHONY: all clean fclean re philo