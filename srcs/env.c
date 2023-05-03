/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:38:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/02 23:10:40 by tmichel-         ###   ########.fr       */
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
	data->new_env = calloc(i + j, sizeof(char *));
	if (!data->new_env)
		return (g_exit_code = 1);
	dup_tab(data->prev_env, data->new_env);
	j = 0;
	while (data->f_arg[++j])
	{
		if (export_exist(data, data->f_arg[j]) && ft_strchr(data->f_arg[j], 61))
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
	int k;
	int	len;

	i = var_to_unset(data);
	freetab(data->new_env);
	data->new_env = malloc(sizeof(char *) * i);
	if (!data->new_env)
		return (g_exit_code = 1);
	j = -1;
	while (data->new_env[++j])
	{
		k = 0;
		while (data->f_arg[++k])
		{
			len = ft_strlen(data->f_arg[k]);
			printf("len = %d\n", len);
			printf("cmp is %d\n", ft_strncmp(data->prev_env[j], data->f_arg[k], len));
			if (ft_strncmp(data->prev_env[j], data->f_arg[k], len) != 0)
				data->new_env[j] = ft_strdup(data->prev_env[j]);
		}
	}
	printf("j = %d\n", j);
	data->new_env[j] = NULL;
	freetab(data->prev_env);
	data->prev_env = malloc(sizeof(char *) * j);
	dup_tab(data->new_env, data->prev_env);
	return (g_exit_code);
}
