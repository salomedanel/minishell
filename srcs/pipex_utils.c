/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:01:23 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/23 16:09:48 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	dupnclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int	count_cmd(t_data *data)
{
	int	count;
	int	i;

	count = 1;
	i = -1;
	while (data->f_arg[++i])
	{
		if (!ft_strcmp(data->f_arg[i],"|"))
			count++;
	}
	return (count);
}

char	*ft_jointab(char **tab)
{
    int		i;
    int		j;
	int		k;
    int		len;
    char	*str;

    i = -1;
    j = 0;
	k = 0;
    len = 0;
    while (tab[++i])
	{
        len += ft_strlen(tab[i]);
		k++;
	}
    str = (char *)malloc(sizeof(char) * (len + k));
    i = -1;
	k = 0;
    while (tab[++i])
    {
        j = -1;
        while (tab[i][++j])
            str[k++] = tab[i][j];
		if (tab[i + 1])
			str[k++] = ' ';
    }
    str[k] = '\0';
    return (str);
}


char	*get_cmd_tab(t_data *data)
{
	int		i;
	int		j;
	char	*cmd;

	i = -1;
	j = 0;
	freetab(data->cmd_tab);
	data->cmd_tab = malloc(sizeof(char *) * (count_cmd(data) + 1));
	if (!data->cmd_tab)
		return (NULL);
	while (data->f_arg[++i])
	{
		if (data->ast[i] == T_CMD)
		{
			data->cmd_tab[j] = ft_strdup(data->f_arg[i]);
			j++;
		}
	}
	data->cmd_tab[j] = NULL;
	cmd = ft_jointab(data->cmd_tab);
	return (cmd);
}

char	**ft_get_path(t_data *data)
{
	int		i;
	char	**path;

	i = -1;
	while (data->new_env[++i])
	{
		if (!ft_strncmp(data->new_env[i], "PATH=", 5))
		{
			path = ft_split(data->new_env[i] + 5, ':');
			return (path);
		}
	}
	return (NULL);
	// si NULL penser message erreur -> unset PATH
}

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char 	*tmp;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}