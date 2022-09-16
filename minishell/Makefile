NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCFLAGS 	= -MMD -I./inc

LDLIBS      := -lreadline

VPATH 		= src/cmd/ src/lexer/ src/liba/ src/main/ src/parser/ src/token/ \
				src/exec/ src/exec/builtins/ src/exec/utils/ src/

SRCS        = test_main.c lexer.c lexer_token.c lexer_utilit.c \
				ft_isdigit.c ft_lstadd_back.c ft_lstclear.c ft_lstdelone.c\
				ft_lstnew.c ft_memcpy.c ft_strchr.c ft_strdup.c\
				ft_strjoin.c ft_strlen.c ft_strncmp.c ft_substr.c\
				ft_atoi.c ft_strnstr.c ft_itoa.c ft_putstr_fd.c\
				parser.c parser_cmd.c parser_utilit_str_gnl.c \
				parser_heredoc.c\
				token.c\
				cmd.c\
				built_env_utils.c built_exit.c built_unset.c built_utils.c\
				builtin_cd.c builtin_export.c builtin_writers.c\
				env_val_utils.c ft_split_utils.c ft_split.c\
				ft_strjoin_path.c ft_strjoin_val.c m_strnstr.c list_fun.c strncmp.c\
				connect.c exe.c exit_status.c main_exe.c one_cmd.c\
				path_fun.c pipe_fun.c pipeline.c print_error_and_errno.c quotes_dollars_open.c\
				file_prepare_fd.c signal.c


ODIR        = tmp
OBJS        = $(SRCS:%.c=$(ODIR)/%.o)

DDIR        = tmp
DEPS        = $(SRCS:%.c=$(DDIR)/%.d)

.PHONY: all clean fclean re deb

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(ODIR)/%.o: %.c $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

$(DEPS):
include $(wildcard $(DEPS))

all: $(NAME)

deb:
	gcc $(INCFLAGS) -g */*.c */*/*.c */*/*/*.c -o $@ $(LDLIBS)

clean:
	$(RM) -r $(DDIR) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
