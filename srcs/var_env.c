/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:33:41 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/31 12:36:55 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	dup_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->prev_env = malloc(sizeof(char *) * (i + 1));
	data->new_env = malloc(sizeof(char *) * (i + 1));
	if (data->new_env == NULL || data->prev_env == NULL)
		return ;
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
	char	*var;
	int		tmp_i;
	int		len;

	tmp_i = *i;
	data->count = varenv_len_utils00(quotes, i, &data->count);
	varenv_len_utils01(quotes, i);
	var = get_dollvalue(quotes, &tmp_i, i);
	data->tmp = replace_dollar_utils(quotes, &tmp_i, i, data);
	len = (ft_strlen(var) * -1) + ft_strlen(data->tmp);
	free(var);
	if (data->tmp == NULL)
	{
		if (quotes->arg[*i] == '$')
			*i = *i - 1;
		return (data->count);
	}
	else
	{
		if (quotes->tmp != NULL)
			free(quotes->tmp);
		return (data->count + len);
	}
}

char	*replace_dollar(t_quotes *quotes, int *i, t_data *data)
{
	int		tmp_i;
	char	*ex_code;

	tmp_i = *i;
	if (quotes->arg[*i] != '$' || quotes->sq_open != 0)
		return (NULL);
	if (quotes->arg[*i] == '$' && quotes->arg[*i + 1] == '?')
	{
		ex_code = ft_itoa(g_exit_code);
		*i = *i + 1;
		return (ex_code);
	}
	if (quotes->arg[*i] == '$')
	{
		*i = *i + 1;
		while (is_specialchar(quotes->arg[*i]) == 0)
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
	int	j;

	j = 0;
	quotes->tmp = ft_calloc(sizeof(char), quotes->counter + 2);
	if (quotes->tmp == NULL)
		return (NULL);
	while (*tmp_i < *i)
	{
		quotes->tmp[j] = quotes->arg[*tmp_i];
		*tmp_i = *tmp_i + 1;
		j++;
	}
	quotes->tmp[j] = '\0';
	*i = *i - 1;
	if (ft_getenv(data, quotes->tmp + 1) == NULL)
	{
		free(quotes->tmp);
		*i = *i + 1;
		return (NULL);
	}
	else
		return (ft_getenv(data, quotes->tmp + 1));
}

char	*get_dollvalue(t_quotes *quotes, int *tmp_i, int *i)
{
	int		j;
	char	*tmp;
	int		tmp2;

	j = 0;
	tmp2 = *tmp_i;
	tmp = malloc(sizeof(char) * quotes->counter + 2);
	if (tmp == NULL)
		return (NULL);
	while (tmp2 < *i)
	{
		tmp[j] = quotes->arg[tmp2];
		tmp2++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}
