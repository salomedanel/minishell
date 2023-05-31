/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:23:19 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/31 01:11:15 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

int	get_len_word(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("><|", str[i]))
	{
		i++;
		r++;
	}
	return (r);
}

char	*get_word(char *str)
{
	int		i;
	int		r;
	char	*new;

	new = malloc(get_len_word(str) + 1);
	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("><|", str[i]))
		new[r++] = str[i++];
	new[r] = '\0';
	return (new);
}

int	count_here_docs(t_data *data)
{
	int	i;
	int	count;
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
	int 	nb;
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
	int i;
	int pid;
	t_here	*here;

	i = -1;;
	data->nb_here = count_here_docs(data);
	if (data->nb_here == 0)
		return (free(data->str), 0);
	here = ft_calloc(sizeof(t_here), (data->nb_here));
	// protection
	openhere_doc(data, here);
	data->here = here;
	pid = fork();
	if (pid == 0)
		child_hd(data);
	else if (pid > 0)
	{
		while (++i < data->nb_here)
			close(here[i].fd[1]);
	}
	waitpid(pid, 0, 0);
	i = -1;
	while (++i < data->nb_here)
	{
		close(here[i].fd[0]);
		free(here[i].limiter);
	}
	free(here);
	return (1);
}
