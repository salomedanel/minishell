/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env_utils00.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:32:15 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 12:32:09 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

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
		if (ft_isdigit(varname[0]) == 1)
		{
			varname = varname + 1;
			varname_len = varname_len - 1;
		}
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

int	varenv_len_utils00(t_quotes *quotes, int *i, int *count)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(g_exit_code);
	len = ft_strlen(tmp);
	free(tmp);
	if (quotes->arg[*i] != '$' || quotes->sq_open != 0)
		return (*count);
	if (quotes->arg[*i] == '$' && *i != 0 && quotes->arg[*i - 1] == '?'
		&& !quotes->arg[*i + 1])
		return (len + 2);
	if (quotes->arg[*i] == '$' && quotes->arg[*i + 1] == '?')
		return (*count + len);
	return (*count);
}

void	varenv_len_utils01(t_quotes *quotes, int *i)
{
	if (quotes->arg[*i] == '$')
	{
		*i = *i + 1;
		while (is_specialchar(quotes->arg[*i]) == 0)
		{
			*i = *i + 1;
			quotes->counter++;
		}
	}
	return ;
}
