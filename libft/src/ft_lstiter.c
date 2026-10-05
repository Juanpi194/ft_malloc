/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:46:16 by jvizcain          #+#    #+#             */
/*   Updated: 2025/10/10 12:31:59 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (f == NULL)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		f(ptr->content);
		ptr = ptr->next;
	}
}
