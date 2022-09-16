/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:49:05 by ddurrand          #+#    #+#             */
/*   Updated: 2021/11/14 16:04:36 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
char	*get_next_line(int fd);
char	*ft_strjoin(char *res, char *buf, int *rl);
char	*write_remainder(char *buf);
typedef struct s_list
{
	int				fd;
	char			*rem;
	struct s_list	*next;
}	t_list;
t_list	*ft_lstnew(int fd);
void	ft_lstdel(t_list **start, int fd);
#endif