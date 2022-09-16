# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 16:00:47 by ddurrand          #+#    #+#              #
#    Updated: 2021/11/23 17:27:20 by ddurrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ft_printf.h

SRCS = ft_printf ft_printf_utils libft_functions

OBJS = $(addsuffix .o, $(SRCS))

FLAGS = -Wall -Wextra -Werror

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $?

%.o : %.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all