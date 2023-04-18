/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:14:50 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/18 13:31:36 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_finalcheck(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->arg[i])
	{
		if (data->arg[i][0] == '"' && data->arg[i][ft_strlen(data->arg[i])
			- 1] == '\'')
		{
			quote_err2(data, QUOTE_ERR, '"');
			return (1);
		}
		if (data->arg[i][0] == '\'' && data->arg[i][ft_strlen(data->arg[i])
			- 1] == '"')
		{
			quote_err2(data, QUOTE_ERR, '\'');
			return (1);
		}
		i++;
	}
	return (0);
}

char	**trim_quotes(char **arg)
{
	int	i;
	char *squote;
	char *dquote;

	i = 0;
	squote = ft_strdup("'");
	dquote = ft_strdup("\"");
	while (arg[i])
	{
		if (arg[i][0] == '"')
			ft_strtrim(arg[i], dquote);
		if (arg[i][0] == '\'')
			ft_strtrim(arg[i], squote);
		i++;
	}
	return (arg);
}
