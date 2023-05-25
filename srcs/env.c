/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:38:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/24 18:13:19 by tmichel-         ###   ########.fr       */
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

	j = count_var_to_exp(data);
	if (j == 1)
		return (g_exit_code = 1);
	i = freetab(data->new_env);
	if (i == 0)
		return (g_exit_code = 1);
	data->new_env = ft_calloc(i + j, sizeof(char *));
	if (!data->new_env)
		return (g_exit_code = 1);
	dup_tab(data->prev_env, data->new_env);
	j = 0;
	while (data->cmd_tab[++j])
		if (export_exist(data, data->cmd_tab[j]) && ft_strchr(data->cmd_tab[j], 61))
			data->new_env[i++] = ft_strdup(data->cmd_tab[j]);
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

	i = var_to_unset(data);
	if (i == 1)
		return (g_exit_code = 1);
	freetab(data->new_env);
	data->new_env = ft_calloc(i + 1, sizeof(char *));
	if (!data->new_env)
		return (g_exit_code = 1);
	i = 0;
	j = -1;
	while (data->prev_env[++j])
	{
		if (check_unset(data->tmp_arg, data->prev_env[j]) == 0)
			data->new_env[i++] = ft_strdup(data->prev_env[j]);
	}
	data->new_env[i] = NULL;
	freetab(data->prev_env);
	data->prev_env = malloc(sizeof(char *) * i);
	dup_tab(data->new_env, data->prev_env);
	return (g_exit_code);
}
