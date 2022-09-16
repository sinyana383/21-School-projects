/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:42:35 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:54:40 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"
#include "executor.h"

char	**g_env;

void	free_strs(char ***strs)
{
	int	i;

	i = -1;
	while ((*strs)[++i])
		free((*strs)[i]);
	free(*strs);
	strs = NULL;
}

int	init_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		++i;
	g_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!g_env)
		return (print_errno_error("malloc", NULL));
	i = -1;
	while (envp[++i])
	{
		g_env[i] = ft_strdup(envp[i]);
		if (!g_env[i])
		{
			free_strs(&g_env);
			return (print_errno_error("malloc", NULL));
		}
	}
	return (1);
}

char	*get_input(void)
{
	char	*input;

	signal(SIGINT, ctlc_handler);
	input = readline("minishell$> ");
	if (!input)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (input && *input)
		add_history(input);
	return (input);
}

int	lexer_parser_executor(char *input)
{
	t_list	*l_token;
	t_cmd	*cmd;

	signal(SIGINT, SIG_IGN);
	errno = 0;
	cmd = NULL;
	l_token = lexer(input);
	free(input);
	if (l_token)
		cmd = parser(&l_token);
	if (l_token)
		ft_lstclear(&l_token, c_token_destroy);
	if (cmd)
		executor(cmd);
	if (cmd)
		ft_lstclear_cmd(&cmd, cmd_destroy);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	g_env = NULL;
	signal(SIGQUIT, SIG_IGN);
	if (init_env(envp) < 0)
		exit (1);
	input = get_input();
	while (input)
	{
		lexer_parser_executor(input);
		input = get_input();
	}
	rl_clear_history();
	exit (*get_status_adress());
}
