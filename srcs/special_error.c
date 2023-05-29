/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:59:29 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/29 14:24:21 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	err_onlyspace(t_data *data)
{
	int	i;

	i = 0;
	while (data->clean_prompt[i] == 32)
	{
		if (i == (ft_strlen(data->clean_prompt) - 1))
			return (0);
		i++;
	}
	return (1);
}
