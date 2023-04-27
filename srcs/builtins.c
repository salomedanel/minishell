/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:23:04 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/27 17:14:20 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	is_builtin(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (!ft_strncmp(str, "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(str, "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(str, "pwd", len) && len == 3)
		return (1);
	if (!ft_strncmp(str, "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(str, "unset", len) && len == 5)
		return (1);
	if (!ft_strncmp(str, "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(str, "exit", len) && len == 4)
		return (1);
	return (0);
}

int	exec_builtin(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->ast[i] == T_BUILTIN)
		{
			len = ft_strlen(data->f_arg[i]);
			if (!ft_strncmp(data->f_arg[i], "echo", len) && len == 4)
				return (mini_echo(data));
			if (!ft_strncmp(data->f_arg[i], "cd", len) && len == 2)
				return (mini_cd(data));
			if (!ft_strncmp(data->f_arg[i], "pwd", len) && len == 3)
				return (mini_pwd());
			if (!ft_strncmp(data->f_arg[i], "export", len) && len == 6)
				return (mini_export(data));
			if (!ft_strncmp(data->f_arg[i], "unset", len) && len == 5)
				return (mini_unset(data));
			if (!ft_strncmp(data->f_arg[i], "env", len) && len == 3)
				return (mini_env(data));
			if (!ft_strncmp(data->f_arg[i], "exit", len) && len == 4)
				return (mini_exit(data));
		}
		i++;
	}
	return (g_exit_code);
}

void	mini_echo_loop(t_data *data, int i)
{
	while (data->f_arg[++i])
	{
		ft_putstr_fd(data->f_arg[i], 1);
		if (!data->f_arg[i + 1])
			break ;
		write(1, " ", 1);
	}
}

int	mini_echo(t_data *data)
{
	int	i;
	int	option;

	if (data->ast[1] != T_OPTION)
	{
		option = 1;
		mini_echo_loop(data, 0);
	}
	else
	{
		i = 2;
		while (data->ast[i] == T_OPTION)
			i++;
		option = 0;
		mini_echo_loop(data, i - 1);
	}
	write(1, "\n", option);
	return (g_exit_code);
}

int	mini_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (g_exit_code);
}
