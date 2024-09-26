/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:54:25 by gsaile            #+#    #+#             */
/*   Updated: 2022/11/28 11:12:52 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_line	*ft_lstmap(t_line *lst, void *(*f)(void *), void (*del)(void *))
{
	t_line	*ret;
	t_line	*current;

	(void)del;
	if (!lst)
		return (NULL);
	current = lst;
	ret = ft_lstnew(f(current->line));
	current = current->next;
	while (current)
	{
		ft_lstadd_back(&ret, ft_lstnew(f(current->line)));
		current = current->next;
	}
	return (ret);
}
