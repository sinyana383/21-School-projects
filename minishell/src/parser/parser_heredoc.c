/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:33:06 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 17:35:47 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	heredoc_merge(t_list *redir_file, t_list **l_token)
{
	t_list	*iter;
	t_list	*tmp;

	if (token_content(redir_file)->flags & TOK_CONNECTED)
	{
		token_content(redir_file)->flags &= ~(TOK_CONNECTED);
		iter = redir_file->next;
		while (iter && token_content(iter)->flags & TOK_CONNECTED)
		{
			tmp = iter->next;
			lst_node_remove(l_token, iter, c_token_destroy);
			iter = tmp;
		}
		lst_node_remove(l_token, iter, c_token_destroy);
	}
}

void	ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}

static char	*heredoc_gnl(char **limiter)
{
	char	*read_str;
	char	*here_str;

	signal(SIGINT, ctlc_heredoc);
	remove_ctlc();
	*limiter = str_append_chr(*limiter, '\n');
	if (*limiter == NULL)
		return (NULL);
	here_str = ft_strdup("");
	if (here_str == NULL)
		return (NULL);
	write(1, "> ", 2);
	read_str = minishell_get_next_line(STDIN_FILENO);
	while (read_str && ft_strncmp(read_str, *limiter, ft_strlen(*limiter) + 1))
	{
		here_str = str_append_str(here_str, read_str);
		if (here_str == NULL)
			break ;
		free(read_str);
		write(1, "> ", 2);
		read_str = minishell_get_next_line(STDIN_FILENO);
	}
	free(read_str);
	return (here_str);
}

static int	heredoc_processing(t_list *redir_file, char **limiter)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (print_errno_error("dup", NULL));
	free(token_content(redir_file)->str);
	token_content(redir_file)->str = heredoc_gnl(limiter);
	if (errno == EBADF)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (ERROR);
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (token_content(redir_file)->str == NULL)
		return (just_print_error(NULL, NULL, strerror(ENOMEM)));
	return (0);
}

int	parser_heredoc(t_list *l_token)
{
	t_list	*redir_file;
	char	*limiter;

	if (l_token && redir_type(token_content(l_token)->str) == REDIR_HEREDOC)
	{
		redir_file = l_token->next;
		limiter = token_to_str(redir_file);
		if (limiter == NULL)
			return (print_errno_error("malloc", NULL));
		if (heredoc_processing(redir_file, &limiter) == ERROR)
		{
			free(limiter);
			return (ERROR);
		}
		free(limiter);
		token_content(redir_file)->flags |= TOK_HEREDOC;
		heredoc_merge(redir_file, &l_token);
	}
	return (0);
}
