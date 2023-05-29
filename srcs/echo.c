/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:35:37 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/29 18:41:48 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	mini_echo_loop(t_data *data, int i)
{
	int	j;

	while (data->tmp_arg[++i])
	{
		if (data->ast[i] != T_CMD)
			continue ;
		j = -1;
		while (data->tmp_arg[i][++j])
			if (data->tmp_arg[i][j] == 31)
				data->tmp_arg[i][j] = 32;
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
		return (write(1, "\n", 1), 0);
	if (!check_echo_opt(data->tmp_arg[i + 1]))
		mini_echo_loop(data, i);
	else
	{
		while (check_echo_opt(data->tmp_arg[++i]) == 1)
			if (!data->tmp_arg[i + 1])
				break ;
		option = 0;
		if (data->tmp_arg[i] && !check_echo_opt(data->tmp_arg[i]))
			mini_echo_loop(data, i - 1);
	}
	return (write(1, "\n", option), 0);
}
