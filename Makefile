# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmeredyt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 02:37:46 by pmeredyt          #+#    #+#              #
#    Updated: 2022/07/13 12:12:24 by pmeredyt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo/philo
NAME_BONUS   =   philo_bonus/philo_bonus

CC			= gcc

CFLAGS		=	-Werror -Wall -Wextra -pthread #-g -fsanitize=thread
#CFLAGS		=	-Werror -Wall -Wextra -pthread -g -fsanitize=address
#CFLAGS		=	-Werror -Wall -Wextra -pthread -g -fsanitize=address

SRCS		=	philo/main.c \
				philo/activity.c \
				philo/death.c \
				philo/utils.c \

BONUS =		philo_bonus/activity.c	\
			philo_bonus/death.c \
			philo_bonus/main.c	\
			philo_bonus/utils.c

HEADER 		=	philo/philo.h
BHEADER 	=	philo_bonus/philo_bonus.h

OBJS		=	$(SRCS:.c=.o)
BOBJS 		=   ${BONUS:%.c=%.o}

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:	 	${BOBJS} ${BHEADER}
			${CC} $(CFLAGS) ${BOBJS} -o ${NAME_BONUS}

clean		:
				rm -rf $(OBJS) $(BOBJS)

fclean		:	clean
				rm -rf $(NAME) $(NAME_BONUS)

re			:	fclean all

.PHONY: philo philo_bonus clean fclean re all
