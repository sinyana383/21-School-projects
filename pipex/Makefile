NAME = pipex
SRCS =	ft_pipex \
		libft/ft_split libft/ft_strjoin libft/ft_strnstr libft/ft_split_utils\
		pipex_utils/print pipex_utils/path_fun
OBJS = $(addsuffix .o, $(SRCS))
FLAGS = -Wall -Wextra -Werror
HEADER = ft_pipex.h

.PHONY: clean fclean re all

all : $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $@ 

%.o : %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:fclean all