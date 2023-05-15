/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:33:41 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/13 15:49:45 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->prev_env = malloc(sizeof(char *) * (i + 1));
	data->new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		data->prev_env[i] = ft_strdup(env[i]);
		data->new_env[i] = ft_strdup(env[i]);
		i++;
	}
	data->prev_env[i] = NULL;
	data->new_env[i] = NULL;
}

int	varenv_len(char *arg, t_data *data, int *i, int *sq_open)
{
	int		index;
	char	*tmp;
	int		tmp_i;
	int		new_len;

	tmp_i = *i;
	index = 0;
	new_len = 0;
	 if (arg[*i] != '$' || *sq_open != 0)
        return (data->count);
	if (arg[*i] == '$')
	{
		*i = *i + 1;
		while (arg[*i] != '\0' && arg[*i] != '"' && arg[*i] != '\'' && arg[*i] != '$')
		{
			*i = *i + 1;
			index++;
		}
	}
	tmp = malloc(sizeof(char) * index);
	index = 0;
	while (tmp_i < *i)
	{
		tmp[index] = arg[tmp_i];
		tmp_i++;
		index++;
	}
	*i = *i - 1;
	if (getenv(tmp + 1) == NULL)
	{
		free(tmp);
		return (data->count);
	}
	else
	{
		new_len = data->count - ft_strlen(tmp) + ft_strlen(getenv(tmp + 1));
		free(tmp);
		return (new_len);
	}
	return (data->count);
}

char	*replace_dollar(char *arg, int *i, int *sq_open)
{
	int		index;
	char	*tmp;
	int		tmp_i;

	tmp_i = *i;
	index = 0;
	//printf("i = %d\n", *i);
	if (arg[*i] != '$' || *sq_open != 0)
        return (NULL);
	if (arg[*i] == '$')
	{
		//printf("i = %d\n", *i);
		*i = *i + 1;
		while (arg[*i] != '\0' && arg[*i] != '"' && arg[*i] != '\'' && arg[*i] != '$')
		{
			*i = *i + 1;
			index++;
		}
	}
	tmp = calloc(sizeof(char), index);
	index = 0;
	while (tmp_i < *i)
	{
		tmp[index] = arg[tmp_i];
		tmp_i++;
		index++;
	}
	//printf("tmp = %s\n", tmp);
	*i = *i - 1;
	if (getenv(tmp + 1) == NULL)
	{
		*i = *i + 1;
		printf("i = %d\n", *i);
		free(tmp);
		return ('\0');
	}
	else
		return (getenv(tmp + 1));
	return (NULL);
}
