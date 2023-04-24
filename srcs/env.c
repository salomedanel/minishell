/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:38:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/24 15:25:19 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

// void	mini_getenv(char **envp, t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (envp[++i])
// 		data->env[i] = ft_strdup(envp[i]);
// }

int	mini_env(t_data *data)
{
	int	i;

	i = -1;
	// TBC GESTION D'ERREUR SI ENV VIDE
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
	while (data->arg[j])
		j++;
	data->new_env = malloc(sizeof(char *) * (i + j));
	if (!data->new_env)
	// TBC GESTION D'ERREUR SI MALLOC FAIL
		return (g_exit_code = 1);
	dup_env(data, envp);
	j = 0;
	while (data->arg[++j])
	{
		if (ft_strchr(data->arg[j], '='))
			data->new_env[i++] = ft_strdup(data->arg[j]);
	}
	return (g_exit_code);
}

// int mini_unset(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = 0;
// 	if (!data->arg[1])
// 	{
// 		ft_putendl_fd("unset: not enough arguments", 2);
// 		return (g_exit_code = 1);
// 	}
// 	while (data->arg[++j])
// 	{
// 		while (data->env[++i])
// 		{
// 			if (!ft_strncmp(data->env[i], data->arg[j], ft_strlen(data->arg[j])))
// 			{
// 				if (ft_strchr(data->arg[j], '='))
// 				{
// 					ft_putstr_fd("unset: ", 2);
// 					ft_putstr_fd(data->arg[j], 2);
// 					ft_putendl_fd(": invalid parameter name", 2);
// 					return (g_exit_code = 1);
// 				}
// 				free(data->env[i]);
// 			}
// 		}
// 		i = -1;
// 	}
// 	return (g_exit_code);
// }

// int	mini_unset(char **envp, t_data *data)
// {
// 	int	i;
// 	int j;

// 	i = -1;
// 	j = -1;
// 	while (envp[i])
// 		i++;
// 	while (data->new_env[++j])
// 		free(data->new_env[j]);
// 	free(data->new_env);
// 	j = 0;
// 	while (data->arg)
// 	//recreer l environnement en skippant les var a suppr, pour le realloc, faire un malloc de i - nb de var a suppr
// }