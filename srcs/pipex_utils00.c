/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:10:50 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/10 13:29:24 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	count_cmd(t_data *data)
{
	int	count;
	int	i;

	count = 1;
	i = -1;
	while (data->f_arg && data->f_arg[++i])
	{
		if (!ft_strcmp(data->f_arg[i], "|"))
			count++;
	}
	return (count);
}

int	count_sub_cmd(t_data *data)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (data->tmp_arg && data->tmp_arg[++i])
	{
		if (data->ast[i] == T_CMD)
			count++;
	}
	return (count);
}

char	*ft_jointab(char **tab, int i, int j)
{
	int		k;
	int		len;
	char	*str;

	k = 0;
	len = 0;
	while (tab && tab[++i])
	{
		len += ft_strlen(tab[i]);
		k++;
	}
	str = (char *)malloc(sizeof(char) * (len + k + 1));
	i = -1;
	k = 0;
	while (tab && tab[++i])
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

void	cmd_not_found(char *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	while (cmd[++i])
		if (cmd[i] == 31)
			cmd[i] = 32;
	if (err_isdir(cmd) == 1)
		return ;
	else if (err_perm(cmd) == 1)
		return ;
	g_exit_code = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	dupnclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}
