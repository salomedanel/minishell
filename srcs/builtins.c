/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:23:04 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/25 13:42:13 by tmichel-         ###   ########.fr       */
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

int	exec_builtin(t_data *data, char *builtin)
{
	int	len;

	len = ft_strlen(builtin);
	if (!ft_strncmp(builtin, "echo", len) && len == 4)
		return (mini_echo(data));
	if (!ft_strncmp(builtin, "cd", len) && len == 2)
		return (mini_cd(data));
	if (!ft_strncmp(builtin, "pwd", len) && len == 3)
		return (mini_pwd());
	if (!ft_strncmp(builtin, "export", len) && len == 6)
		return (mini_export(data));
	if (!ft_strncmp(builtin, "unset", len) && len == 5)
		return (mini_unset(data));
	if (!ft_strncmp(builtin, "env", len) && len == 3)
		return (mini_env(data));
	if (!ft_strncmp(builtin, "exit", len) && len == 4)
		return (mini_exit(data));
	return (0);
}

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

int	mini_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (g_exit_code);
}
