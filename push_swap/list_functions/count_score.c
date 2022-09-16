/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_score.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:10:13 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 14:42:59 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"
#include "list.h"

t_list	*score_first_place(t_list *list, int gap)
{
	t_list	*gap_list;
	t_list	*first;
	int		up;

	up = 0;
	first = list;
	while (list->data != gap)
	{
		up += 1;
		list = list->next;
		if (list == 0)
			return (0);
	}
	gap_list = list;
	gap_list->up = up;
	gap_list->down = 0;
	while (list != 0)
	{
		if (!(list->next == 0 && first == list))
		gap_list->down += 1;
		list = list->next;
	}
	return (gap_list);
}

void	set_nulls(t_list *b_list, int *flag, int *found_place)
{
	*flag = 0;
	*found_place = 0;
	b_list->wait_a_down = 0;
	b_list->wait_a_up = 0;
}

void	score_wait_a(t_list *a_list, t_list *b_list)
{
	int	flag;
	int	found_place;

	set_nulls(b_list, &flag, &found_place);
	if (!a_list || !b_list)
		return ;
	while (a_list != 0)
	{
		if (found_place)
			b_list->wait_a_down += 1;
		else if (a_list->data < b_list->data)
		{
			flag = 1;
			b_list->wait_a_up += 1;
		}
		else if (a_list->data > b_list->data && flag)
		{
			found_place = 1;
			b_list->wait_a_down += 1;
		}
		else if (a_list->data > b_list->data && !flag)
			b_list->wait_a_up += 1;
		a_list = a_list->next;
	}
}

void	total_elem_score(t_list *b)
{
	int	total;
	int	downs;
	int	ups;
	int	mixed;

	if (!b)
		return ;
	downs = maxim(b->down, b->wait_a_down);
	ups = maxim(b->up, b->wait_a_up);
	mixed = minim(b->down, b->up);
	mixed += minim(b->wait_a_up, b->wait_a_down);
	total = minim(downs, ups);
	total = minim(total, mixed);
	if (total == downs)
		b->path = 'd';
	else if (total == ups)
		b->path = 'u';
	else
		b->path = 'm';
	b->score = total;
}

t_list	*get_min_score(t_list *a_list, t_list *b_list)
{
	t_list	*min;
	t_list	*temp;

	temp = b_list;
	min = 0;
	if (!a_list || !b_list)
		return (0);
	while (temp)
	{
		score_first_place(b_list, temp->data);
		score_wait_a(a_list, temp);
		total_elem_score(temp);
		if (!min || min->score > temp->score \
		|| (min->score == temp->score && temp->data > min->data))
			min = temp;
		temp = temp->next;
	}
	return (min);
}
