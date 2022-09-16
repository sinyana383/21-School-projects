NAME = push_swap
BONUS_NAME = checker
SRCS = 	ft_push_swap \
		array_functions/ft_atoi array_functions/sort\
		list_functions/list list_functions/count_score\
		list_functions/actions list_functions/rotate_actions\
		list_functions/make_del_list list_functions/sort_list\
		list_functions/sort_with_score list_functions/make_b
SRCS_B = checker_bonus/actions checker_bonus/ch_ft_atoi\
		 checker_bonus/ch_make_del checker_bonus/check_arg_and_a\
		 checker_bonus/checker checker_bonus/list\
		 checker_bonus/rotate_actions checker_bonus/split\
		  checker_bonus/work_with_input
HEADER = ft_push_swap.h
HEADER_BONUS = checker_bonus/checker.h
L_HEADER = list_functions/list.h
OBJS = $(addsuffix .o, $(SRCS))
OBJS_B = $(addsuffix .o, $(SRCS_B))
FLAGS = -Wall -Werror -Wextra
.PHONY: clean fclean re all bonus

all : $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_B)
	cc $(FLAGS) $(OBJS_B) -o $@

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $@

ft_push_swap.o : ft_push_swap.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

array_functions/%.o : array_functions/%.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

list_functions/%.o : list_functions/%.c $(HEADER) $(L_HEADER)
	cc $(FLAGS) -c $< -o $@

checker_bonus/%.o : checker_bonus/%.c $(HEADER_BONUS)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all