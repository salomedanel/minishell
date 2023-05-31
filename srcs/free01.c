/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:45:26 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 16:26:34 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dobby(t_data *data)
{
	freetab(data->f_arg);
}

void	free_child_heredoc(t_data *data)
{
	int	i;

	i = -1;
	freetab(data->f_arg);
	freetab(data->p_arg);
	freetab(data->new_env);
	freetab(data->prev_env);
	while (++i < data->nb_here)
		free(data->here[i].limiter);
	freetab(data->path);
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
