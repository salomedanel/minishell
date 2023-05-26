/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:35:37 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/26 11:36:09 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	mini_echo_loop(t_data *data, int i)
{
	while (data->tmp_arg[++i])
	{
		if (data->ast[i] != T_CMD)
			continue ;
		ft_putstr_fd(data->tmp_arg[i], 1);
		if (!data->tmp_arg[i + 1])
			break ;
		write(1, " ", 1);
	}
}

int	check_echo_opt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != '-')
			return (0);
		if (i > 0 && str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	mini_echo(t_data *data)
{
	int	i;
	int	option;

	i = -1;
	option = 1;
	while (data->tmp_arg[++i])
		if (!ft_strcmp(data->tmp_arg[i], "echo"))
			break ;
	if (!data->tmp_arg[i + 1])
		return (write(1, "\n", 1), g_exit_code);
	if (!check_echo_opt(data->tmp_arg[i + 1]))
		mini_echo_loop(data, i);
	else
	{
		while (check_echo_opt(data->tmp_arg[++i]) == 1)
		{
			option = 0;
			if (!data->tmp_arg[i + 1])
				break ;
		}
		mini_echo_loop(data, i - 1);
	}
	return (write(1, "\n", option), g_exit_code);
}