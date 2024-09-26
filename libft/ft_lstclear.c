/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:53:51 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/28 11:05:57 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_line **lst, void (*del)(void *))
{
	t_line	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		del((*lst)->line);
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	lst = NULL;
}
