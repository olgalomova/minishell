/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:46:40 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/28 11:41:30 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_forked_builtin(char **args, t_env **minienv)
{
	int	exit_status;

	exit_status = execute_builtin(args, minienv);
	free_array(args);
	ft_lstclear(minienv);
	rl_clear_history();
	exit(exit_status);
}

void	execute_fork_cmd(char *command, char **commands, t_env **minienv)
{
	char	**av;

	close_extra_fds();
	av = split_av(command);
	free_array(commands);
	if (is_builtin(av[0]))
		execute_forked_builtin(av, minienv);
	else
		execute_external(av, *minienv);
}

void	quit_child(char **commands, t_env **minienv)
{
	rl_clear_history();
	ft_lstclear(minienv);
	free_array(commands);
	close_all_fds();
	exit(EXIT_FAILURE);
}

void	handle_child_redir(char *command, char **commands, t_env **minienv)
{
	char	redirect;

	redirect = *get_rposition(command);
	while (redirect)
	{
		if (redirect == '<')
			if (redirect_input(command) == FAILED)
				quit_child(commands, minienv);
		if (redirect == '>')
			if (redirect_output(command) == FAILED)
				quit_child(commands, minienv);
		if (redirect == 1)
			redirect_heredoc(command);
		redirect = *get_rposition(command);
	}
}
