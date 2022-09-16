/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:10:27 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:53:05 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct info
{
	int		i;
	int		status;
	int		pid;
	int		fd[2];
}	t_info;

int			executor(t_cmd	*cmds);

int			set_program_path(char **env, char *program, char **path);
//PATH_FINDER UTILS=========================
char		*m_strnstr(const char *haystack, const char *needle, int len);
char		*ft_strjoin_path(char const *s1, char const *s2);
char		**alloc_strs(char const *s, char c, int *size);

//PIPE_FUN
int			close_pipe(int pipes[2][2], int i, int last);
void		init_pipe(int pipes[2][2]);
void		pipes_prepare_fd(int fd[2], int pipes[2][2], int i, int last);

//FROM_LIBFT
int			m_strncmp(char *s1, char *s2, int n);
int			lst_remove_next(t_list	*list);
char		**my_ft_split(char const *s, char c);

int			connect_all(t_cmd *cmd);

int			open_all_dollars(t_cmd *cmds);
//OPEN_TOKEN
char		*ft_strjoin_val(char *dst, const char *src, int len_src);
int			open_env_val(char **val, char *str, int *i);

//EXECUTION
int			execute_cmds(t_cmd *cmd, int pipes[2][2]);
int			files_prepare_fd(t_list *redirs, int fd[2]);
void		close_fd(int fd[2]);
int			one_cmd_exe(t_cmd *cmd);
int			execve_cmd(t_cmd *cmd, int i, int pipes[2][2]);

//TEMP
t_cmd		*convert_list_to_cmd(t_list *lst_cmd);

int			check_and_exe_builtin(t_cmd *cmd, int pipes[2][2], int i);
//BUILT-IN UTILS
t_c_token	*con_token(t_list *lst);
int			build_prepare(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i);
int			build_finish(int fd_save[2]);

int			change_or_add_var(char *var, char *val, int is_add, char *name);
int			check_for_syntax(char *var, char *builtin);

//BUILT-IN DOERS
int			built_cd(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i);
int			built_export(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i);
int			built_unset(t_cmd *cmd, int fd_save[2], int pipes[2][2], int i);
int			built_exit(t_cmd *cmd);
int			only_exit(t_cmd *cmd, char *status);

//EXIT CODE
int			*get_status_adress(void);
void		set_status(int new_status);
int			open_exit(t_cmd *cmd);

//ERROR
int			print_errno_error(char *str1, char *str2);
int			just_print_error(char *str1, char *str2, char *error_massage);

void		free_strs(char ***strs);
void		ctlc_handler(int sig);

#endif
