# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 19:06:37 by stapioca          #+#    #+#              #
#    Updated: 2021/11/11 19:06:37 by stapioca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ft_printf.h

LIST = ft_printf.c

OBJS = $(patsubst %.c,%.o,$(LIST))

FLAGS = -Wall -Wextra -Werror

.PHONY : all clean fclean re

all : $(NAME) $(HEADER)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $?

%.o : %.c ft_printf.h
	CC $(FLAGS) -c $< -o $@ -I ${HEADER}

clean :
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all