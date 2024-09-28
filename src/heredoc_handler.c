/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:58:43 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/28 11:42:39 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	delimiter_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == ' ' || s[i] == '>' || s[i] == '<' || s[i] == '|'))
	{
		if (s[i] == '\'')
		{
			delete_char(&s[i], 1);
			while (s[i] && s[i] != '\'')
				i++;
			delete_char(&s[i], 1);
		}
		else if (s[i] == '"')
		{
			delete_char(&s[i], 1);
			while (s[i] && s[i] != '"')
				i++;
			delete_char(&s[i], 1);
		}
		else
			i++;
	}
	return (i);
}

char	*get_delimiter(char *delim_pos)
{
	int		len;
	char	*delimiter;

	delete_char(delim_pos, 1);
	if (*delim_pos == '>')
		delete_char(delim_pos, 1);
	while (*delim_pos == ' ')
		delete_char(delim_pos, 1);
	len = delimiter_len(delim_pos);
	delimiter = ft_substr(delim_pos, 0, len);
	delete_char(delim_pos, len);
	return (delimiter);
}

char	*get_heredoc_pos(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = skip_quotes(str);
		if (*str == '<' && *(str + 1) == '<')
			return (str);
		str++;
	}
	return (NULL);
}

int	exec_heredoc(char *delimiter, int *exit_status, t_env *minienv, char *input)
{
	int	child_pid;

	child_pid = fork();
	define_heredoc_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork - exec_heredoc", delimiter);
	else if (child_pid == 0)
	{
		free(input);
		read_heredoc(exit_status, minienv, delimiter);
	}
	else
	{
		*exit_status = wait_for_child(child_pid, TRUE);
		signal_handler();
		if (*exit_status != EXIT_SUCCESS)
			return (FAILED);
	}
	return (SUCCESS);
}

int	heredoc_handler(char *input, int *exit_status, t_env *minienv)
{
	char	*delimiter;
	char	*heredoc_pos;

	heredoc_pos = get_heredoc_pos(input);
	if (!heredoc_pos)
		return (SUCCESS);
	*heredoc_pos = 1;
	heredoc_pos++;
	delimiter = get_delimiter(heredoc_pos);
	if (!exec_heredoc(delimiter, exit_status, minienv, input))
	{
		free(delimiter);
		return (FAILED);
	}
	free(delimiter);
	return (heredoc_handler(input, exit_status, minienv));
}
