/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:15 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/26 19:31:14 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_exit(char **av, t_env **minienv)
{
	int	exit_status;

	rl_clear_history();
	ft_lstclear(minienv);
	ft_putstr_fd("exit\n", 1);
	check_av_error(av);
	close_all_fds();
	exit_status = ft_atoll(av[1]);
	free_array(av);
	exit(exit_status);
}
