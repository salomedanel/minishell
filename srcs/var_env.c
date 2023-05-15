/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:33:41 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/15 17:43:02 by sdanel           ###   ########.fr       */
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

int	varenv_len(t_quotes *quotes, t_data *data, int *i)
{
	int		index;
	char	*tmp;
	int		tmp_i;

	tmp_i = *i;
	index = 0;
	if (quotes->arg[*i] != '$' || quotes->sq_open != 0)
		return (data->count);
	if (quotes->arg[*i] == '$')
	{
		*i = *i + 1;
		while (quotes->arg[*i] != '\0' && quotes->arg[*i] != '"'
			&& quotes->arg[*i] != '\'' && quotes->arg[*i] != '$')
		{
			*i = *i + 1;
			index++;
		}
	}
	tmp = malloc(sizeof(char) * index);
	if (replace_dollar_utils(quotes, &tmp_i, i, data) == NULL)
		return (data->count);
	else
		return (data->count - ft_strlen(tmp) + ft_strlen(ft_getenv(data, tmp
					+ 1)));
}

char	*replace_dollar(t_quotes *quotes, int *i, t_data *data)
{
	int	tmp_i;
	int	j;

	tmp_i = *i;
	j = 0;
	if (quotes->arg[*i] != '$' || quotes->sq_open != 0)
		return (NULL);
	if (quotes->arg[*i] == '$')
	{
		*i = *i + 1;
		while (quotes->arg[*i] != '\0' && quotes->arg[*i] != '"'
			&& quotes->arg[*i] != '\'' && quotes->arg[*i] != '$')
		{
			*i = *i + 1;
			quotes->counter++;
		}
	}
	return (replace_dollar_utils(quotes, &tmp_i, i, data));
}

char	*replace_dollar_utils(t_quotes *quotes, int *tmp_i, int *i,
		t_data *data)
{
	int		j;
	char	*tmp;

	j = 0;
	printf("counter = %d | i = %d | tmp_i = %d\n", quotes->counter, *i, *tmp_i);
	tmp = calloc(sizeof(char), quotes->counter);
	tmp[quotes->counter] = '\0';
	while (*tmp_i < *i)
	{
		tmp[j] = quotes->arg[*tmp_i];
		*tmp_i = *tmp_i + 1;
		j++;
	}
	*i = *i - 1;
	if (ft_getenv(data, tmp + 1) == NULL)
	{
		*i = *i + 1;
		free(tmp);
		return (NULL);
	}
	else
		return (ft_getenv(data, tmp + 1));
}

char	*ft_getenv(t_data *data, char *varname)
{
	int	i;
	int	varname_len;

	i = 0;
	varname_len = ft_strlen(varname);
	while (data->new_env[i] != NULL)
	{
		if (strncmp(varname, data->new_env[i], varname_len) == 0
			&& data->new_env[i][varname_len] == '=')
		{
			return (data->new_env[i] + varname_len + 1);
		}
		i++;
	}
	return (NULL);
}
