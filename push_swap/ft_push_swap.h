/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:28:30 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 11:35:40 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(const char *str, int *a, int ai);
void	sort(int *a, int right, int left);
typedef struct s_list
{
	int				data;
	int				up;
	int				down;
	int				wait_a_up;
	int				wait_a_down;
	int				score;
	char			path;
	struct s_list	*next;
}	t_list;
int		work_with_list(int *a, int len);
t_list	*score_first_place(t_list *list, int gap);
#endif