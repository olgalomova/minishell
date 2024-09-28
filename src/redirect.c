/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:17:22 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/25 17:05:11 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_original_fds(int original_fds[2])
{
	if (original_fds[0] != NO_REDIRECT)
		redirect_fd(original_fds[0], STDIN_FILENO);
	if (original_fds[1] != NO_REDIRECT)
		redirect_fd(original_fds[1], STDOUT_FILENO);
}

char	*get_rposition(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = skip_quotes(str);
		if (*str == '>' || *str == '<' || *str == 1)
			return (str);
		str++;
	}
	return (str);
}

char	*get_redirect_position(char *str, char redirect_char)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (*str == redirect_char)
			return (str);
		str++;
	}
	return (str);
}

char	*get_spos(char *str, const char *chars_to_find)
{
	while (*str)
	{
		str = skip_quotes(str);
		if (ft_strchr(chars_to_find, *str))
			return (str);
		str++;
	}
	return (NULL);
}

int	unexpected_token(char *input)
{
	if (input[0] == '<' && input[1] == '<')
		return (syntax_error("<<"));
	else if (input[0] == '>' && input[1] == '>')
		return (syntax_error(">>"));
	input[1] = '\0';
	return (syntax_error(input));
}
