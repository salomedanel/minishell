/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:38:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/27 16:39:02 by tmichel-         ###   ########.fr       */
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

int	mini_export(t_data *data)
{
	int	i;
	int	j;

	i = freetab(data->new_env);
	if (i == 0)
		return (g_exit_code = 1);
	j = 0;
	while (data->f_arg[j])
		j++;
	data->new_env = calloc(i + j, sizeof(char *));
	if (!data->new_env)
		return (g_exit_code = 1);
	dup_tab(data->prev_env, data->new_env);
	j = 0;
	while (data->f_arg[++j])
	{
		if (ft_strchr(data->f_arg[j], 61))
			data->new_env[i++] = ft_strdup(data->f_arg[j]);
	}
	data->new_env[i] = NULL;
	freetab(data->prev_env);
	data->prev_env = malloc(sizeof(char *) * i);
	dup_tab(data->new_env, data->prev_env);
	return (g_exit_code);
}

int	mini_unset(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = var_to_unset(data);
	j = freetab(data->new_env);
	data->new_env = malloc(sizeof(char *) * (j - i));
	if (!data->new_env)
		return (g_exit_code = 1);
	j = -1;
	while (data->new_env[++j])
	{
		len = ft_strlen(data->arg[j]);
		if (!ft_strncmp(data->new_env[j], data->f_arg[j], len))
			j++;
		data->new_env[j] = ft_strdup(data->prev_env[j]);
	}
	data->new_env[j] = NULL;
	freetab(data->prev_env);
	data->prev_env = malloc(sizeof(char *) * j);
	dup_tab(data->new_env, data->prev_env);
	return (g_exit_code);
}
