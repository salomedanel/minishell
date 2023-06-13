/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:45:26 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/13 10:41:23 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_heredoc(t_data *data)
{
	int	i;

	i = -1;
	freetab(data->p_arg);
	freetab(data->new_env);
	freetab(data->prev_env);
	while (++i < data->nb_here)
		free(data->here[i].limiter);
	free(data->here);
}

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	pre_free_hd(t_data *data)
{
	int	i;

	i = -1;
	if (data->nb_here)
	{
		while (++i < data->nb_here)
			free(data->here[i].limiter);
		free(data->here);
	}
}
