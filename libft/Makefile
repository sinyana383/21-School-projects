NAME = libft.a
CC = gcc
HEADER  =   libft.h
CFLAGS = -Werror -Wall -Wextra
SRCS =  	ft_memset		ft_bzero		ft_memcpy \
			ft_memmove		ft_memchr		ft_memcmp \
			ft_strlen		ft_strlcpy		ft_strlcat\
			ft_strchr		ft_strrchr		ft_strnstr \
			ft_strncmp		ft_isalpha      \
			ft_isdigit		ft_isalnum		ft_isascii \
			ft_isprint		ft_toupper		ft_tolower \
			ft_atoi			ft_calloc		ft_strdup\
			ft_substr		ft_strjoin		ft_strtrim\
			ft_split		ft_itoa			ft_strmapi\
			ft_striteri		ft_putchar_fd	ft_putstr_fd\
			ft_putendl_fd	ft_putnbr_fd\

SRCS_B = 	ft_lstnew		ft_lstadd_front	ft_lstsize\
			ft_lstlast		ft_lstadd_back	ft_lstdelone\
			ft_lstclear		ft_lstiter		ft_lstmap\
		

OBJS = $(addsuffix .o, $(SRCS))
OBJS_B = $(addsuffix .o, $(SRCS_B))
.PHONY: all re clean fclean bonus

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $?

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	make OBJS="$(OBJS_B)" all
clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all