/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:08:26 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 16:27:26 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char *stash)
{
	char	*buf;
	int		read_return;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_return = 1;
	while (!ft_strchr_gnl(stash, '\n') && read_return)
	{
		read_return = read(fd, buf, BUFFER_SIZE);
		if (read_return == -1)
		{
			free (buf);
			return (NULL);
		}
		*(buf + read_return) = '\0';
		stash = ft_strjoin_gnl(stash, buf);
		if (!stash)
		{
			free (buf);
			return (NULL);
		}
	}
	free (buf);
	return (stash);
}

char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!*(stash + 0))
		return (NULL);
	while (*(stash + i) && *(stash + i) != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (*(stash + i) && *(stash + i) != '\n')
	{
		*(line + i) = *(stash + i);
		i++;
	}
	if (*(stash + i) == '\n')
	{
		*(line + i) = '\n';
		i++;
	}
	*(line + i) = '\0';
	return (line);
}

char	*ft_get_rol(char *stash)
{
	char	*nextstash;
	int		i;
	int		j;

	i = 0;
	while (*(stash + i) && *(stash + i) != '\n')
		i++;
	if (!*(stash + i))
	{
		free (stash);
		return (NULL);
	}
	nextstash = malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
	if (!nextstash)
	{
		free (stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (*(stash + i))
		*(nextstash + j++) = *(stash + i++);
	*(nextstash + j) = '\0';
	free (stash);
	return (nextstash);
}

char	*get_next_line(int fd, int boolean)
{
	char		*line;
	static char	*stash[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (boolean)
		return (free(stash[0]), free(line), NULL);
	stash[fd] = ft_read(fd, stash[fd]);
	if (!stash[fd])
	{
		free(stash[fd]);
		return (NULL);
	}
	line = ft_get_line(stash[fd]);
	stash[fd] = ft_get_rol(stash[fd]);
	return (line);
}
