/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:35:39 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/24 18:08:58 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

void	get_cmd_tab(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
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
	while (data->new_env[++i])
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

void	ft_op_error(char *str)
{
	ft_putstr_fd("minishell: An error has occurred while opening ", 2);
	ft_putendl_fd(str, 2);
}

int	open_files(t_data *data)
{
	int	i;
	int	fd;

	i = -1;
	while (data->redir[++i])
	{
		if (data->type[i] == T_REDOUT)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (data->type[i] == T_REDIN)
			fd = open(data->redir[i], O_RDONLY);
		else if (data->type[i] == T_RED_OUT_APPEND)
			fd = open(data->redir[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_op_error(data->redir[i]);
		if (data->type[i] == T_REDOUT || data->type[i] == T_RED_OUT_APPEND)
			dupnclose(fd, STDOUT_FILENO);
		else if (data->type[i] == T_REDIN)
			dupnclose(fd, STDIN_FILENO);
	}
	return (0);
}

