/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermko@student.42prague.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:38:11 by ayermeko          #+#    #+#             */
/*   Updated: 2023/11/18 18:38:12 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*altdest;
	const unsigned char	*altsrc;

	altdest = (unsigned char *)dest;
	altsrc = (const unsigned char *)src;
	while (n)
	{
		*altdest = *altsrc;
		altdest++;
		altsrc++;
		n--;
	}
	return (dest);
}
