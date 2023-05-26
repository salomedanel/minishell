/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:23:04 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/26 11:47:07 by tmichel-         ###   ########.fr       */
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

int	unforkable_builtins(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (!ft_strncmp(str, "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(str, "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(str, "unset", len) && len == 5)
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


