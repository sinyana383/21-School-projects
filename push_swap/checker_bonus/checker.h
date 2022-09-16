/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:04:10 by ddurrand          #+#    #+#             */
/*   Updated: 2022/06/20 13:48:05 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				data;
	struct s_list	*next;
}	t_list;
char	**ft_split(char const *s, char c);
int		ft_atoi(char *str, int *a, int ia);
int		check_arg_and_a(int argc, char **argv, int **a);
int		list(int *a, int size);
t_list	*make_list(int *a, int len);
void	ft_lstclear(t_list **lst);
t_list	*ft_lstnew(int data);
void	rrr(t_list **a_list, t_list **b_list);
void	rr(t_list **a_list, t_list **b_list);
void	rev_rotate(t_list **list);
void	rotate(t_list **list);
void	push(t_list **a, t_list **b);
void	swap(t_list **list);
void	ss(t_list **a, t_list **b);
int		take_actions(t_list **a, t_list **b);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		make_act(char *act, t_list **a, t_list **b);
#endif
