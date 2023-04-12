/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:11:08 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/12 15:38:41 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_divide(double x, int j)
{
	while (j > 0)
	{
		x /= 10;
		j--;
	}
	return (x);
}

static int	ft_define_decimal(const char *nptr)
{
	int	i;
	int	j;

	i = ft_strlen(nptr);
	j = 0;
	while (i > 0)
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			j++;
		if (nptr[i] == '.')
			break ;
		i--;
	}
	return (j);
}

double	ft_atof(const char *nptr)
{
	double	res;
	int		sign;
	int		i;

	res = 0.0;
	sign = 1;
	i = ft_define_decimal(nptr);
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while ((*nptr >= '0' && *nptr <= '9') || *nptr == '.')
	{
		if (*nptr == '.')
			nptr++;
		else
			res = res * 10.0 + (*nptr++ - '0');
	}
	return (res = ft_divide(res * sign, i), res);
}

// int main (int ac, char **av)
// {
// 	int	i;

// 	i = 0;
// 	while (av[i])
// 	{
// 		printf("%f\n", ft_atof(av[i]));
// 		i++;
// 	}
// 	return (1);
// }