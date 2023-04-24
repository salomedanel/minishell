/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:38:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/24 18:27:27 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	mini_env(t_data *data)
{
	int	i;

	i = -1;
	if (!data->new_env[0])
		return (g_exit_code = 1);
	while (data->new_env[++i])
		ft_putendl_fd(data->new_env[i], 1);
	return (g_exit_code);
}

int	mini_export(char **envp, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->new_env[i])
	{
		free(data->new_env[i]);
		i++;
	}
	free(data->new_env);
	while (data->f_arg[j])
		j++;
	data->new_env = malloc(sizeof(char *) * (i + j));
	if (!data->new_env)
		return (g_exit_code = 1);
	dup_env(data, envp);
	j = 0;
	while (data->f_arg[++j])
	{
		if (ft_strchr(data->f_arg[j], '='))
			data->new_env[i++] = ft_strdup(data->arg[j]);
	}
	data->new_env[i] = NULL;
	return (g_exit_code);
}

void	freetab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	var_to_unset(t_data *data)
{
	int	j;
	int	i;

	i = 0;
	j = -1;
	while (data->new_env[i])
		i++;
	while (data->f_arg[++j])
	{
		if (ft_strchr(data->f_arg[j], '='))
		{
			g_exit_code = 1;
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(data->f_arg[j], 2);
			ft_putendl_fd(": invalid parameter name", 2);
			i--;
		}
	}
	return (i);
}

int	mini_unset(char **envp, t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = var_to_unset(data);
	freetab(data->new_env);
	data->new_env = malloc(sizeof(char *) * i);
	if (!data->new_env)
		return (g_exit_code = 1);
	j = -1;
	while (data->new_env[++j])
	{
		len = ft_strlen(data->arg[j]);
		if (!ft_strncmp(data->new_env[j], data->f_arg[j], len))
			j++;
		data->new_env[j] = ft_strdup(envp[j]);
	}
	data->new_env[j] = NULL;
	return (g_exit_code);
}
