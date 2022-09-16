/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:35:35 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 19:07:58 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define TOK_TEXT			1
# define TOK_S_QUOTE		2
# define TOK_D_QUOTE		4
# define TOK_REDIR_FILE		8
# define TOK_CONNECTED		16
# define TOK_PIPE			64
# define TOK_REDIR			512
# define TOK_HEREDOC		1024

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_token_content
{
	int		flags;
	char	*str;
}	t_c_token;

typedef struct s_cmd
{
	int				type;
	t_list			*argvs;
	t_list			*redirs;
	struct s_cmd	*next;
}	t_cmd;

extern char	**g_env;

# define ERROR		-1

# define CLEARSPACES		" \t\n"
# define QUOT_MARKS			"\'\""

// LEXER
t_list		*lexer(char *input);

// LEXER_SYNTAX
int			lexer_syntax_pipe(t_list *l_token);

// LEXER_TOKEN
int			pipe_token(char *str, int *i, t_list **l_token);
int			special_token(char *str, int *i);
int			redir_token(char *str, int *i, t_list **l_token);
int			text_token(char *str, int *i, t_list **l_token);
int			quote_token(char *str, int *i, t_list **l_token);

// LEXER_UTILIT
int			quote_len(char *str);
int			other_len(char *chr);
int			text_len(char *str);
int			free_quote(char *token_str);

// LIBA
char		*ft_substr(char const *s, unsigned int start, size_t len);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
char		*ft_strchr(const char *s, int c);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_isdigit(int c);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

// TOKEN
t_list		*token_create(char *string, int type);
t_c_token	*token_content(t_list *token);
void		c_token_destroy(void *c_token);
char		*token_to_str(t_list *l_token);

int			remove_ctlc(void);

#endif
