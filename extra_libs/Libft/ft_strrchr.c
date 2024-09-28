/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermko@student.42prague.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:34:05 by ayermeko          #+#    #+#             */
/*   Updated: 2023/11/18 18:34:07 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*res;

	res = s + ft_strlen(s);
	while (res >= s && *res != (char)c)
		res--;
	if (res >= s)
		return ((char *)res);
	else
		return (NULL);
}
