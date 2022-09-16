/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_with_score.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:19:16 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 16:28:04 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "list.h"

void	downs_act(t_list **a, t_list **b, t_list *min)
{
	int		diff;
	char	temp;
	int		i;

	diff = maxim(min->down, min->wait_a_down) - \
	minim(min->down, min->wait_a_down);
	temp = 'a' + (min->down > min->wait_a_down);
	i = -1;
	while (++i < minim(min->down, min->wait_a_down))
		rrr(a, b);
	if (temp == 'a')
		use_i_times_action(rev_rotate, a, 'a', diff);
	else
		use_i_times_action(rev_rotate, b, 'b', diff);
}

void	ups_act(t_list **a, t_list **b, t_list *min)
{
	int		diff;
	char	temp;
	int		i;

	diff = maxim(min->up, min->wait_a_up) - \
	minim(min->up, min->wait_a_up);
	temp = 'a' + (min->up > min->wait_a_up);
	i = -1;
	while (++i < minim(min->up, min->wait_a_up))
		rr(a, b);
	if (temp == 'a')
		use_i_times_action(rotate, a, 'a', diff);
	else
		use_i_times_action(rotate, b, 'b', diff);
}

void	sort_with_score(t_list *min, t_list **a, t_list **b)
{
	int		i;

	i = -1;
	if (min->path == 'd')
		downs_act(a, b, min);
	else if (min->path == 'u')
		ups_act(a, b, min);
	else if (min->path == 'm')
	{
		if (min->up < min->down)
		{
			use_i_times_action(rotate, b, 'b', min->up);
		}
		else
			use_i_times_action(rev_rotate, b, 'b', min->down);
		if (min->wait_a_up < min->wait_a_down)
			use_i_times_action(rotate, a, 'a', min->wait_a_up);
		else
			use_i_times_action(rev_rotate, a, 'a', min->wait_a_down);
	}
	push(b, a, 'a');
}
