/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:01:23 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/22 11:12:27 by sdanel           ###   ########.fr       */
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
		if (data->ast[i] == T_PIPE)
			count++;
	}
	return (count);
}

// void	create_pipes(t_args *args)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < args->cmd_nbr - 1)
// 	{
// 		if (pipe(args->pipe + 2 * i) < 0)
// 		{
// 			free_parent(args);
// 			ft_error("An error has occurred while creating pipe.\n");
// 		}
// 	}
// }

char	**pre_cmd(t_data *data, int	i)
{
	int		j;
	char	**cmd_tab;

	j = 0;
	cmd_tab = malloc(sizeof(char *) * (count_cmd(data) + 1));
	if (!cmd_tab)
		return (NULL);
	while (data->f_arg[i] && data->ast[i] != T_PIPE)
	{
		if (data->ast[i] == T_CMD)
		{
			cmd_tab[j] = ft_strdup(data->f_arg[i]);
			j++;
		}
		i++;
	}
	cmd_tab[count_cmd(data)] = NULL;
	return (cmd_tab);
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