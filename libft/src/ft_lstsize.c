/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvizcain <jvizcain@students.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:43:09 by jvizcain          #+#    #+#             */
/*   Updated: 2025/12/02 12:31:56 by jvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ptr;

	i = 1;
	ptr = lst;
	if (lst == NULL)
		return (0);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
