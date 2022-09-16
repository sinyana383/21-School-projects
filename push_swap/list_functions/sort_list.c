/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:10:13 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 17:11:08 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "list.h"

int	sort_three(t_list **a_list)
{
	if (ft_reach_lstsize(*a_list, 3) != 3)
		return (-1);
	if (!is_list_sorted(*a_list))
		swap(a_list, 'a');
	return (1);
}

void	sort_b_to_a(t_list **a_list, t_list **b_list)
{
	t_list	*min;

	while (ft_reach_lstsize(*b_list, 0) != 0)
	{
		min = get_min_score(*a_list, *b_list);
		sort_with_score(min, a_list, b_list);
	}
}

int	final_sort_list(t_list **a_list, int min)
{
	t_list	*min_list;
	int		i;

	i = -1;
	min_list = score_first_place(*a_list, min);
	if (!min_list)
		return (0);
	if ((min_list)->down < (min_list)->up)
		use_i_times_action(rev_rotate, a_list, 'a', (min_list)->down);
	else
		use_i_times_action(rotate, a_list, 'a', (min_list)->up);
	return (1);
}

int	is_list_sorted(t_list *lst)
{
	t_list	*first;
	t_list	*prev;
	int		c_gap;

	if (!lst || !lst->next)
		return (1);
	first = lst;
	c_gap = 0;
	prev = lst;
	while (lst->next)
	{
		lst = lst->next;
		if (prev->data > lst->data)
		{
			++c_gap;
			if (c_gap > 1)
				return (0);
		}
		prev = lst;
	}
	if (prev->data > first->data && c_gap > 0)
		return (0);
	return (1);
}

void	use_i_times_action(void (*f)(t_list **lst, char name), \
t_list **lst, char name, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		f(lst, name);
}
