/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:05:20 by danelsalome       #+#    #+#             */
/*   Updated: 2023/04/24 16:56:40 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		data->new_env[i] = ft_strdup(env[i]);
		i++;
	}
	data->new_env[i] = '\0';
}

int	len_varenv(char *varenv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (varenv[i] != '=')
		i++;
	while (varenv[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	strncmp_dollar(char *env, char *arg)
{
	int	i;
	int	j;
	int	count_char;

	i = 0;
	j = 0;
	count_char = 0;
	while (env[i] != '=')
	{
		count_char++;
		i++;
	}
	i = 0;
	while (arg[i] == '"')
		i++;
	while (arg[i + 1] == env[j])
	{
		if (i == count_char - 1)
			return (0);
		i++;
		j++;
	}
	return (-1);
}

int	check_varenv(t_data *data, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->new_env[i])
	{
		while (data->new_env[i][j])
		{
			if (data->new_env[i][j] == '=')
			{
				if (strncmp_dollar(data->new_env[i], arg) == 0)
					return (len_varenv(data->new_env[i]) - 1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	replace_dollar(char *arg, t_data *data, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->new_env[i])
	{
		while (data->new_env[i][j])
		{
			if (data->new_env[i][j] == '=')
			{
				if (strncmp_dollar(data->new_env[i], arg) == 0)
				{
					ft_strcpy(data->f_arg[index], data->new_env[i], j + 1);
					return ;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}
