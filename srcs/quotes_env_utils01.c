/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env_utils01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:23:52 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 12:26:12 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_cases_doll00(t_quotes *quotes, t_data *data, int *i, int *j)
{
	if (quotes->arg[*i] == '$' && quotes->arg[*i + 1] == '\0'
		&& ft_strlen(quotes->arg) == 1)
	{
		data->f_arg[quotes->index][*j] = quotes->arg[*i];
		*j = *j + 1;
		return (0);
	}
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

void	special_cases_doll02(t_quotes *quotes, int *i, char *var)
{
	if (var != NULL)
	{
		if (ft_strlen(quotes->arg) > 1 && quotes->arg[*i] != '?')
			free(quotes->tmp);
	}
	if (*i != 0 && quotes->arg[*i - 1] == '$' && quotes->arg[*i] == '?')
		free(var);
}
