/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:11:47 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/22 16:22:35 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char    *ft_jointab(char **tab)
// {
//     int        i;
//     int        j;
//     int        k;
//     int        len;
//     char    *str;

//     i = -1;
//     j = 0;
//     k = 0;
//     len = 0;
//     while (tab[++i])
//     {
//         len += ft_strlen(tab[i]);
//         k++;
//     }
//     str = (char *)malloc(sizeof(char) * (len + k));
//     i = -1;
//     k = 0;
//     while (tab[++i])
//     {
//         j = -1;
//         while (tab[i][++j])
//             str[k++] = tab[i][j];
//         if (tab[i + 1])
//             str[k++] = ' ';
//     }
//     str[k] = '\0';
//     return (str);
// }

// char	*ft_jointab(char **tab, t_data *data)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		len;
// 	char	*str;

// 	i = -1;
// 	j = 0;
// 	k = 0;
// 	len = 0;
// 	while (tab[++i])
// 	{
// 		len += ft_strlen(tab[i]);
// 		k++;
// 	}
// 	str = (char *)malloc(sizeof(char) * (len + k));
// 	i = -1;
// 	k = 0;
// 	while (tab[++i])
// 	{
// 		j = -1;
// 		// if (data->ast[i + 1] == 0)
// 		// 	str[k++] = ' ';
// 		while (tab[i][++j])
// 			str[k++] = tab[i][j];
// 	}
// 	str[k] = '\0';
// 	return (str);
// }

void	ft_strcpy_pipe(char *dest, char *src, int start)
{
	int	i;

	i = 0;
	if (src == NULL)
		return ;
	printf("start = %d\n", start);
	while (src[start] && i < ft_strlen(src) - 1)
	{
		dest[i] = src[start];
		i++;
		start++;
	}
	//dest[i] = '\0';
	return ;
}

char	**split_pipe(t_data *data)
{
    char *str;
	int	i;
	int	count;

	i = 0;
	count = 0;
	data->count_cmd = count_cmd(data);
    str = ft_jointab(data->f_arg);
    printf("%s\n", str);
	data->tmp_arg = ft_split(str, '|');
	while (data->tmp_arg[count])
		count++;
	data->p_arg = malloc(sizeof(char *) * (count + 1));
	while (data->tmp_arg[i])
	{
		if (i == 0)
		{
			data->p_arg[i] = malloc(sizeof(char) * (ft_strlen(data->tmp_arg[i]) - 1));
			ft_strcpy_pipe(data->p_arg[i], data->tmp_arg[i], 0);
			i++;
		}
		else if (i == count - 1)
		{
			data->p_arg[i] = malloc(sizeof(char) * (ft_strlen(data->tmp_arg[i]) - 1));
			ft_strcpy_pipe(data->p_arg[i], data->tmp_arg[i], 1);
			i++;
		}
		else
		{
			data->p_arg[i] = malloc(sizeof(char) * (ft_strlen(data->tmp_arg[i]) - 2));
			ft_strcpy_pipe(data->p_arg[i], data->tmp_arg[i], 1);
			i++;
		}
	}
	print_arg(data->p_arg);
	free(str);
	return (data->p_arg);
}