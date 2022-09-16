/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 18:36:19 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/20 13:47:56 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	make_act(char *act, t_list **a, t_list **b)
{
	if (!ft_strncmp("rr\n", act, 3))
		rr(a, b);
	else if (!ft_strncmp("rrr\n", act, 4))
		rrr(a, b);
	else if (!ft_strncmp("ra\n", act, 3))
		rotate(a);
	else if (!ft_strncmp("rra\n", act, 4))
		rev_rotate(a);
	else if (!ft_strncmp("rb\n", act, 3))
		rotate(b);
	else if (!ft_strncmp("rrb\n", act, 4))
		rev_rotate(b);
	else if (!ft_strncmp("pa\n", act, 3))
		push(b, a);
	else if (!ft_strncmp("pb\n", act, 3))
		push(a, b);
	else if (!ft_strncmp("sa\n", act, 3))
		swap(a);
	else if (!ft_strncmp("sb\n", act, 3))
		swap(b);
	else if (!ft_strncmp("ss\n", act, 3))
		ss(a, b);
	else
		return (-1);
	return (1);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_a_b(t_list *a_list, t_list *b_list)
{
	if (b_list != NULL)
		return (-1);
	while (a_list != NULL)
	{
		if (a_list->next != NULL)
		{
			if (a_list->data > a_list->next->data)
				return (-1);
		}
		a_list = a_list->next;
	}
	return (1);
}

int	list(int *a, int size)
{
	t_list	*a_list;
	t_list	*b_list;
	int		check;

	a_list = make_list(a, size);
	b_list = NULL;
	if (take_actions(&a_list, &b_list) < 0)
	{
		ft_lstclear(&a_list);
		return (-1);
	}
	check = check_a_b(a_list, b_list);
	ft_lstclear(&a_list);
	if (b_list != NULL)
		ft_lstclear(&b_list);
	if (check < 0)
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
	return (1);
}
