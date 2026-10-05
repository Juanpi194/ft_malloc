/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:36:03 by juanp             #+#    #+#             */
/*   Updated: 2026/03/08 18:46:16 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlnbr_base_fd(unsigned long n, char const *base, int fd)
{
	size_t const	base_len = ft_strlen(base);
	char			c_num_base;

	if (n >= base_len)
		ft_putlnbr_base_fd(n / base_len, base, fd);
	c_num_base = base[n % base_len];
	write(fd, &c_num_base, 1);
}
