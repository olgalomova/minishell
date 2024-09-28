/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:32:00 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/20 15:44:03 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_env **minienv)
{
	t_env	*line;
	t_env	*next;

	line = *minienv;
	while (line)
	{
		free(line->key_pair);
		next = line->next;
		free(line);
		line = next;
	}
}
