/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:41:31 by tmichel-          #+#    #+#             */
/*   Updated: 2022/11/20 19:11:37 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextelem;

	if (!del || !lst || !(*lst))
		return ;
	while (lst && *lst)
	{
		nextelem = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nextelem;
	}
}
