/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:29:24 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 16:32:42 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	outfile_error(t_data *data, char *str)
{
	ft_putstr_fd("minishell: An error has occurred while opening: ", 2);
	ft_putendl_fd(str, 2);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	g_exit_code = 1;
	return (1);
}

int	infile_error(t_data *data, char *str)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putendl_fd(str, 2);
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	g_exit_code = 1;
	return (1);
}

int	last_redir(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data->type[++i])
		if (data->type[i] == 1 || data->type[i] == 4)
			count++;
	return (count);
}

int	get_pipe(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_here)
	{
		if (!ft_strcmp(str, data->here[i].limiter))
			return (data->here[i].fd[0]);
	}
	return (-1);
}

int	*create_matrix(t_data *data)
{
	int	i;
	int	j;
	int	*matrix;

	i = -1;
	j = -1;
	matrix = malloc(sizeof(int) * (data->nb_here));
	while (++i < count_redir(*data))
	{
		if (data->type[i] == T_HERE_DOC)
			matrix[++j] = i;
	}
	return (matrix);
}