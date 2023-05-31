/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:23:19 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/31 16:48:53 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	count_here_docs(t_data *data)
{
	int		i;
	int		count;
	char	*str;

	str = data->str;
	i = -1;
	count = 0;
	while (1)
	{
		str = ft_strnstr(str, "<<", ft_strlen(str));
		if (str)
			count++;
		else
			break ;
		str += 2;
	}
	return (count);
}

void	openhere_doc(t_data *data, t_here *here)
{
	int		nb;
	char	*str;

	nb = 0;
	str = data->str;
	while (1)
	{
		str = ft_strnstr(str, "<<", ft_strlen(str));
		if (str)
		{
			here[nb].limiter = get_word(str + 2);
			pipe(here[nb++].fd);
		}
		else
			break ;
		str += 2;
	}
	free(data->str);
}

char	*openfileshd(t_here *here)
{
	char	*s;

	while (1)
	{
		s = readline("here_doc>");
		if (!s || !ft_strcmp(s, here->limiter))
			break ;
		ft_putendl_fd(s, here->fd[1]);
		free(s);
	}
	close(here->fd[1]);
	close(here->fd[0]);
	return (NULL);
}

void	child_hd(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_here)
		openfileshd(&data->here[i]);
	free_child_heredoc(data);
	exit(1);
}

int	here_doc(t_data *data)
{
	int		i;
	int		pid;
	t_here	*here;

	i = -1;
	data->nb_here = count_here_docs(data);
	if (data->nb_here == 0)
		return (free(data->str), 0);
	here = ft_calloc(sizeof(t_here), (data->nb_here));
	openhere_doc(data, here);
	data->here = here;
	pid = fork();
	if (pid == 0)
		child_hd(data);
	else if (pid > 0)
	{
		while (++i < data->nb_here)
		{
			close(data->here[i].fd[1]);
			close(data->here[i].fd[0]);
		}
	}
	waitpid(pid, 0, 0);
	return (1);
}
