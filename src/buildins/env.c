/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:12 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/26 19:31:21 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_env *minienv)
{
	while (minienv)
	{
		if (ft_strchr(minienv->key_pair, '='))
		{
			ft_putstr_fd(minienv->key_pair, 1);
			ft_putstr_fd("\n", 1);
		}
		minienv = minienv->next;
	}
	return (0);
}
