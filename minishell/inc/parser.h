/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:44:08 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 18:06:43 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "cmd.h"

# define REDIR_OUT		1
# define REDIR_OUT_APP	2
# define REDIR_IN		3
# define REDIR_HEREDOC	4

t_cmd		*parser(t_list **l_token);

int			parser_heredoc(t_list *l_token);

int			redir_type(char *redir);
int			cmd_token_set(t_cmd *cmd, t_list **l_token);

char		*str_append_chr(char *str, char append);
char		*str_append_str(char *str, char *append);
char		*minishell_get_next_line(int fd);
int			lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));

#endif