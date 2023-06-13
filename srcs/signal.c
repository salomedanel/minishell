/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:41:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/12 22:06:17 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	g_exit_code = 130;
// 	ft_putstr_fd("\n", 2);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void	ft_ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
	}
}

// void	antislash(int sig)
// {
// 	if (sig == SIGQUIT)
// 	{
// 		//ft_putendl_fd("Quit (core dumped)", 2);
// 		exit(131);
// 	}
// 	if (sig == SIGINT)
// 		exit(130);
// }

void	handle_sig_cmd(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		signal(SIGINT, ctrlc);
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)\n", 2);
		g_exit_code = 131;
	}
}

void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
