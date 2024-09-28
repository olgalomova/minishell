/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:38:26 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/26 19:20:19 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_env *lst)
{
	t_env	*new;
	int		cnt;

	new = lst;
	cnt = 0;
	while (new)
	{
		cnt++;
		new = new->next;
	}
	return (cnt);
}
