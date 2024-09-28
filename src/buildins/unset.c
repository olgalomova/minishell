/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:40:20 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/26 19:31:03 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_from_minienv(char *varname, t_env **m)
{
	t_env	**prev_next;

	prev_next = m;
	while (*prev_next)
	{
		if (ft_strncmp((*prev_next)->key_pair, varname, ft_strlen(varname)) == 0
			&& (*prev_next)->key_pair[ft_strlen(varname)] == '=')
			return (m_del_node(prev_next));
		prev_next = &(*prev_next)->next;
	}
}

int	unset(char **av, t_env **minienv)
{
	char	*varname;
	int		exit_status;

	av++;
	exit_status = EXIT_SUCCESS;
	if (!*av)
		return (0);
	while (*av)
	{
		varname = *av;
		if (!is_valid_varname(varname))
		{
			print_varname_error_msg("unset", varname);
			exit_status = EXIT_FAILURE;
		}
		else
			remove_from_minienv(varname, minienv);
		av++;
	}
	return (exit_status);
}
