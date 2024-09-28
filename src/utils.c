/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayermeko <ayermeko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:22:27 by ayermeko          #+#    #+#             */
/*   Updated: 2024/09/28 11:51:37 by ayermeko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirect_heredoc(char *command)
{
	int		tmp_file_fd;

	tmp_file_fd = open("/tmp/minishell_hd", O_RDONLY);
	if (tmp_file_fd == -1)
	{
		print_perror_msg("open", "/tmp/minishell_hd");
		return ;
	}
	redirect_fd(tmp_file_fd, STDIN_FILENO);
	delete_char(get_redirect_position(command, 1), 1);
}

char	*create_keypair(char *name, char *value)
{
	char	*key_pair;
	int		key_pair_size;
	int		i;

	key_pair_size = ft_strlen(name) + ft_strlen(value) + 2;
	key_pair = malloc(key_pair_size * sizeof(char));
	i = 0;
	while (*name)
		key_pair[i++] = *name++;
	key_pair[i++] = '=';
	while (*value)
		key_pair[i++] = *value++;
	key_pair[i] = '\0';
	return (key_pair);
}

void	minienv_update(char *name, char *value, t_env *minienv)
{
	t_env	*aux;
	char	*new_pair;

	aux = minienv_node(name, minienv);
	if (!aux)
	{
		new_pair = create_keypair(name, value);
		minienv_add(new_pair, &minienv);
		free(new_pair);
		return ;
	}
	free(aux->key_pair);
	aux->key_pair = create_keypair(name, value);
}

int	is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	is_path(char *command)
{
	if (*command == '.')
		command++;
	if (*command == '.')
		command++;
	if (*command == '/')
		return (TRUE);
	return (FALSE);
}
