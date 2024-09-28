/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermko@student.42prague.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:37:26 by ayermeko          #+#    #+#             */
/*   Updated: 2023/11/18 18:37:28 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*res;

	res = s;
	while (*res)
	{
		if (*res == (char)c)
			return ((char *)res);
		res++;
	}
	if (c == '\0')
		return ((char *)res);
	return (NULL);
}
