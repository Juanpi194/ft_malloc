/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanp <juanp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:53:25 by juanp             #+#    #+#             */
/*   Updated: 2025/12/04 18:03:11 by juanp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_args(char **args)
{
	size_t	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], DEFAULT_FD);
		write(DEFAULT_FD, "\n", 1);
		i++;
	}
}
