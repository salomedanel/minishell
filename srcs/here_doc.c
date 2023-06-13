/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:23:19 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/13 11:38:36 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

t_here	*openhere_doc(t_data *data, t_here *here)
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
	return (here);
}

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	data = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nb_here)
		{
			close(data->here[i].fd[1]);
			close(data->here[i].fd[0]);
		}
		free_child_heredoc(data);
		exit(130);
	}
}

char	*openfileshd(t_here *here)
{
	char	*s;

	while (1)
	{
		s = readline("heredoc> ");
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
	signal(SIGINT, &exit_hd);
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
	pre_free_hd(data);
	data->nb_here = count_here_docs(data);
	if (data->nb_here == 0)
		return (free(data->str), 0);
	here = ft_calloc(sizeof(t_here), (data->nb_here));
	here = openhere_doc(data, here);
	signal(SIGINT, SIG_IGN);
	data->here = here;
	pid = fork();
	if (pid == 0)
		child_hd(data);
	else if (pid > 0)
	{
		while (++i < data->nb_here)
			close(data->here[i].fd[1]);
	}
	signal(SIGINT, &ctrlc);
	waitpid(pid, 0, 0);
	return (1);
}
