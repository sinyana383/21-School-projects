NAME = philo
HEADER = philo.h
SRC =  clean_fun main philo_actions libft_fun initilizer dead_eat_check
OBJ = $(addsuffix .o, $(SRC))
FLAGS = -Werror -Wextra -Wall
GCC = cc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(GCC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	