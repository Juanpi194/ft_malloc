/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanp <juanp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:33:37 by juanp             #+#    #+#             */
/*   Updated: 2025/12/05 20:34:10 by juanp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putulnbr_fd(unsigned long n, int fd)
{
	char	c_num;

	if (n > 9)
		ft_putulnbr_fd(n / 10, fd);
	c_num = n % 10 + '0';
	write(fd, &c_num, 1);
}
