/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:46:45 by jvizcain          #+#    #+#             */
/*   Updated: 2025/10/13 12:19:10 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_cpy;
	void	*new_content;
	t_list	*new_node;

	if (lst == NULL)
		return (NULL);
	new_content = f(lst->content);
	lst_cpy = ft_lstnew(new_content);
	lst = lst->next;
	while (lst != NULL && lst_cpy != NULL)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&lst_cpy, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_cpy, new_node);
		lst = lst->next;
	}
	if (lst_cpy == NULL)
		del(new_content);
	return (lst_cpy);
}
