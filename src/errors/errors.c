/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:39:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 13:14:38 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "errors.h"

static void	handle_errors(t_command *command)
{
	if (command->error == NO_ERROR)
		return ;
	if (command->error == PERMISSION_DENIED)
	{
		ft_fprintf(STDERR_FILENO, "pipex: %s: Permission denied\n",
			command->error_allias);
	}
	else if (command->error == NO_SUCH_FILE_OR_DIRECTORY)
	{
		ft_fprintf(STDERR_FILENO, "pipex: %s: No such file or directory\n",
			command->error_allias);
	}
	else if (command->error == ERROR_OPENING_FILE)
	{
		ft_fprintf(STDERR_FILENO, "pipex: %s: Error occured at file opening\n",
			command->error_allias);
	}
}

void	add_error(t_command *command, t_command_errors error, char *allias)
{
	command->error = error;
	command->error_allias = allias;
}

void	print_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
}

void	print_commands_errors(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;

	current = data->commands_queue;
	command = NULL;
	while (current && current->content)
	{
		command = (t_command *)current->content;
		handle_errors(command);
		current = current->next;
	}
}
