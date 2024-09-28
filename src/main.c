/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:47:37 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/28 11:39:21 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	one_command(char *input, t_env **minienv)
{
	char	**av;
	int		exit_status;
	int		original_fds[2];

	if (*input == 0)
		return (free(input), 0);
	if (!handle_redirects(input, &original_fds[0]))
	{
		restore_original_fds(original_fds);
		free(input);
		return (EXIT_FAILURE);
	}
	av = split_av(input);
	free(input);
	exit_status = 0;
	if (av[0] != NULL)
	{
		if (is_builtin(av[0]))
			exit_status = execute_builtin(av, minienv);
		else
			exit_status = exec_fork_extern(av, *minienv);
	}
	free_array(av);
	restore_original_fds(original_fds);
	return (exit_status);
}

static char	*prompt_input(t_env *minienv)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		builtin_exit(NULL, &minienv);
	if (*input)
		add_history(input);
	return (input);
}

static int	minishell(t_env *minienv)
{
	int		exit_status;
	char	*input;
	char	**commands;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		signal_handler();
		input = free_spaces(prompt_input(minienv));
		if (input_error(input, &exit_status, minienv))
			continue ;
		expand_input(&input, minienv, exit_status);
		if (has_pipe(input) == FALSE)
			exit_status = one_command(input, &minienv);
		else
		{
			commands = split_commands(input);
			free(input);
			exit_status = multiple_commands(commands, &minienv);
			free_array(commands);
		}
	}
	return (0);
}

int	main(void)
{
	extern char	**environ;

	return (minishell(init_minienv(environ)));
}
