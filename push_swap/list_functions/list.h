/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:45:01 by ddurrand          #+#    #+#             */
/*   Updated: 2022/01/25 17:05:24 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

void	sort(int *a, int right, int left);
int		final_sort_list(t_list **a_list, int min);
int		sort_three(t_list **a_list);
int		is_list_sorted(t_list *lst);
void	rev_rotate(t_list **list, char a);
void	rotate(t_list **list, char a);
void	rr(t_list **a_list, t_list **b_list);
void	rrr(t_list **a_list, t_list **b_list);
void	push(t_list **a, t_list **b, char a_or_b);
void	swap(t_list **list, char a_or_b);
int		ft_reach_lstsize(t_list *lst, int size);
t_list	*find_node(t_list *list, int data);
t_list	*make_list(int *a, int len);
t_list	*make_b(t_list **a_list, int *a, int len);
void	sort_with_score(t_list *min, t_list **a, t_list **b);
t_list	*get_min_score(t_list *a_list, t_list *b_list);
void	sort_b_to_a(t_list **a_list, t_list **b_list);
int		maxim(int a, int b);
int		minim(int a, int b);
void	ft_lstclear(t_list **lst);
void	use_i_times_action(void (*f)(t_list **lst, char name), \
t_list **lst, char name, int i);
#endif