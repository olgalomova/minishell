/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_separate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:17:25 by olomova           #+#    #+#             */
/*   Updated: 2024/09/28 17:17:30 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_error(char *input)
{
	char	*position;

	position = get_rposition(input);
	if (!*position)
		return (FALSE);
	if (position[0] == '<' && position[1] == '<')
		position++;
	else if (position[0] == '>' && position[1] == '>')
		position++;
	position++;
	while (*position == ' ')
		position++;
	if (*position == '\0')
		return (syntax_error("newline"));
	if (*position == '|' || *position == '>' || *position == '<')
		return (unexpected_token(position));
	return (redirect_error(position));
}

int	handle_redirects(char *input, int original_fds[2])
{
	char	redirect;

	original_fds[0] = NO_REDIRECT;
	original_fds[1] = NO_REDIRECT;
	redirect = *(get_rposition(input));
	while (redirect)
	{
		if (redirect == '<' && !handle_io(input, original_fds, STDIN_FILENO))
			return (FAILED);
		else if (redirect == '>'
			&& !handle_io(input, original_fds, STDOUT_FILENO))
			return (FAILED);
		else if (redirect == 1)
		{
			save_original_fd(original_fds, STDIN_FILENO);
			redirect_heredoc(input);
		}
		redirect = *(get_rposition(input));
	}
	return (SUCCESS);
}
