/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salekyne <salekyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:42:51 by salekyne          #+#    #+#             */
/*   Updated: 2022/09/13 18:04:59 by salekyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "lexer.h"

# define CMD		1
# define CMD_PIPE	8

t_cmd		*cmd_create(int type);

void		cmd_destroy(t_cmd *cmd);
int			cmd_type_token(t_list *token);
void		ft_lstclear_cmd(t_cmd **lst, void (del)(t_cmd *));

#endif
