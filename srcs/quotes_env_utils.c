/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:32:15 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/29 14:55:30 by sdanel           ###   ########.fr       */
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

int	is_specialchar(char c)
{
	if (c == '$' || c == '\'' || c == '"' || c == '\0' || c == '[' || c == ']' || c == '{' || c == '}' || c == '%')
		return (1);
	return (0);
}

int	is_spechar(char c)
{
	if (c == '&')
		return (1);
	if (c >= 40 && c <= 42)
		return (1);
	return (0);
}