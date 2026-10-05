/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:45:42 by jvizcain          #+#    #+#             */
/*   Updated: 2025/10/10 18:33:16 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr1;
	t_list	*ptr2;

	if (lst == NULL || del == NULL)
		return ;
	ptr2 = *lst;
	while (ptr2 != NULL)
	{
		ptr1 = ptr2;
		ptr2 = ptr2->next;
		ft_lstdelone(ptr1, del);
	}
	*lst = NULL;
}
