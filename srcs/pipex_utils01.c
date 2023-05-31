/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:35:39 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/31 16:28:14 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	get_cmd_tab(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (count_sub_cmd(data) == 0)
		return ;
	data->cmd_tab = malloc(sizeof(char *) * (count_sub_cmd(data) + 1));
	if (!data->cmd_tab)
		return ;
	while (data->tmp_arg[++i])
	{
		if (data->ast[i] == T_CMD)
		{
			data->cmd_tab[j] = ft_strdup(data->tmp_arg[i]);
			j++;
		}
	}
	data->cmd_tab[j] = NULL;
	return ;
}

char	**ft_get_path(t_data *data)
{
	int		i;
	char	**path;

	i = -1;
	while (data->new_env && data->new_env[++i])
	{
		if (!ft_strncmp(data->new_env[i], "PATH=", 5))
		{
			path = ft_split(data->new_env[i] + 5, ':');
			return (path);
		}
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = -1;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (path && path[++i])
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

void	get_space(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == 31)
				tab[i][j] = 32;
			j++;
		}
	}
}
