/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:41:36 by ddurrand          #+#    #+#             */
/*   Updated: 2022/02/13 14:11:26 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_pipe
{
	int		pipefd[2];
	int		files[2];
	int		id[2];
	char	*program_path;
	char	**argums;
}	t_pipe;
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
char	*ft_strjoin_path(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
void	print_prog_error(char *str);
void	perror_error(char *str);
char	*get_program_path(char **env, char *program);
void	free_strs(char **strs);
char	**alloc_strs(char const *s, char c, int *size);
#endif