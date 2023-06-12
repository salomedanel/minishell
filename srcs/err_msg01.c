/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:58:53 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/12 12:19:50 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	err_unset_opt(char *var)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putchar_fd(var[0], 2);
	ft_putchar_fd(var[1], 2);
	ft_putstr_fd("': invalid option\n", 2);
	g_exit_code = 2;
}

void	err_unset_id(char *var)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
}

int	err_isdir(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[0] != '.' && cmd[++i])
	{
		if (cmd[i] == '/')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			g_exit_code = 126;
			return (1);
		}
	}
	return (0);
}

int	err_perm(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[0] == '.' && cmd[++i])
	{
		if (cmd[i] == '/')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			g_exit_code = 126;
			return (1);
		}
	}
	return (0);
}
