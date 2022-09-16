NAME = philo_bonus
HEADER = philo_bonus.h
SRC = philo_bonus libft_fun initiolizer ft_itoa philo_actions
OBJ = $(addsuffix .o, $(SRC))
CFLAGS = -Werror -Wextra -Wall
GCC = cc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(GCC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	