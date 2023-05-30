/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:32:15 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/29 22:44:05 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trimquotes_utils(t_quotes *quotes, int *count)
{
	int	dq;
	int	sq;

	dq = -1;
	sq = -1;
	while (quotes->arg[++dq])
		if (quotes->arg[dq] == '"')
			break ;
	while (quotes->arg[++sq])
		if (quotes->arg[sq] == '\'')
			break ;
	if (dq < sq)
		return (*count = count_char(quotes->arg, '"'));
	else
		return (*count = count_char(quotes->arg, '\''));
	return (*count);
}

char	*ft_getenv(t_data *data, char *varname)
{
	int	i;
	int	varname_len;

	i = 0;
	if (varname[0] == '\0')
		return (NULL);
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

int	norm_trimquotes(t_quotes *quotes, int *i)
{
	if (quotes->arg[*i] == '"' && quotes->dq_open == 0)
	{
		quotes->dq_open = 1;
		*i = *i + 1;
	}
	else if (quotes->arg[*i] == '\'' && quotes->sq_open == 0)
	{
		quotes->sq_open = 1;
		*i = *i + 1;
	}
	return (*i);
}

int	special_cases_doll00(t_quotes *quotes, t_data *data, int *i, int *j)
{
	if ((quotes->arg[*i] == '$' && quotes->sq_open == 1)
		|| (quotes->arg[*i] == '$' && quotes->dq_open == 1 && quotes->arg[*i
				+ 1] == '"'))
	{
		data->f_arg[quotes->index][*j] = quotes->arg[*i];
		*j = *j + 1;
		return (0);
	}
	if ((quotes->arg[*i] == '$' && (quotes->arg[*i + 1] == '=' || quotes->arg[*i
					+ 1] == ':' || quotes->arg[*i + 1] == 31)))
	{
		data->f_arg[quotes->index][*j] = quotes->arg[*i];
		*j = *j + 1;
		return (0);
	}
	if (quotes->arg[*i] == '$' && quotes->arg[*i + 1] == '\'')
		return (0);
	return (1);
}

int	special_cases_doll01(t_quotes *quotes, t_data *data, int *i, int *j)
{
	if (quotes->arg[*i] == '?' && quotes->arg[*i + 1] == '$' && quotes->arg[*i
			+ 2] == '\0')
	{
		data->f_arg[quotes->index][*j] = quotes->arg[*i + 1];
		*j = *j + 1;
		return (0);
	}
	return (1);
}
