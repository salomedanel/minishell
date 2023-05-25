/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:32:15 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/25 10:37:51 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    trimquotes_utils(t_quotes *quotes, int *count)
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