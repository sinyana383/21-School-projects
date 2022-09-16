/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:51:46 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/13 17:53:54 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

int	remove_ctlc(void)
{
	struct termios	termios_p;

	if (tcgetattr(STDOUT_FILENO, &termios_p))
		return (print_errno_error("tcgetattr", NULL));
	termios_p.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &termios_p))
		return (print_errno_error("tcsetattr", NULL));
	return (1);
}

void	ctlc_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		remove_ctlc();
	}
}
