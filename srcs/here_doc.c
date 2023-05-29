/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:23:19 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/29 19:21:35 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	count_here_docs(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data->type[++i])
		if (data->type[i] == 3)
			count++;
	return (count);
}

int	open_here_doc(t_data *data)
{
	int	i;
	int	index;

	i = -1;
	index = 0;
	while (data->redir[++i])
	{
		if (data->type[i] == 3)
		{
			index++;
			if (index == count_here_docs(data))
			{
				if (here_doc(data->redir[i]) == 0)
					return (0);
			}
		}
	}
	return (1);
}

int	here_doc(char *limiter)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (1);
	len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, len) && len == ft_strlen(line) - 1)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	get_next_line(1, 1);
	close(fd);
	fd = open(".tmp", O_RDONLY);
	if (fd == -1)
		return (1);
	dupnclose(fd, STDIN_FILENO);
	unlink(".tmp");
	return (0);
}
