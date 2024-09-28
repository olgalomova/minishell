/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:27:34 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/28 11:27:36 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirect_fd(int fd_to_redirect, int fd_location)
{
	dup2(fd_to_redirect, fd_location);
	close(fd_to_redirect);
}

void	save_original_fd(int original_fds[2], int fd_index)
{
	if (original_fds[fd_index] == NO_REDIRECT)
		original_fds[fd_index] = dup(fd_index);
}

int	redirect_input(char *input)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;

	input_redirect = get_spos(input, "<");
	if (!*input_redirect)
		return (SUCCESS);
	file_name = get_delimiter(input_redirect);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("filename - input is not accessible.", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (SUCCESS);
}

int	redirect_output(char *command)
{
	char	*output_redirect;
	char	*file_name;
	int		fd;
	int		open_flags;

	output_redirect = get_spos(command, ">");
	if (!*output_redirect)
		return (SUCCESS);
	if (output_redirect[1] == '>')
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	file_name = get_delimiter(output_redirect);
	fd = open(file_name, open_flags, 0644);
	if (fd == -1)
	{
		print_perror_msg("filename - output is not accessible.", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDOUT_FILENO);
	free(file_name);
	return (SUCCESS);
}

int	handle_io(char *command, int original_fds[2], int fd_type)
{
	save_original_fd(original_fds, fd_type);
	if (fd_type == STDOUT_FILENO && redirect_output(command) == FAILED)
	{
		redirect_fd(original_fds[fd_type], fd_type);
		return (FAILED);
	}
	else if (fd_type == STDIN_FILENO && redirect_input(command) == FAILED)
	{
		redirect_fd(original_fds[fd_type], fd_type);
		return (FAILED);
	}
	return (SUCCESS);
}
