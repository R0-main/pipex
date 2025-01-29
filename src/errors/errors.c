/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:39:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 08:47:01 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "errors.h"

static void	handle_errors(t_pipex_data *data, t_command *command)
{
	if (command->error == -1)
		return ;
	if (command->error == PERMISSION_DENIED)
	{
		ft_printf("pipex: %s: Permission denied\n", command->error_allias);
	}
	else if (command->error == NO_SUCH_FILE_OR_DIRECTORY)
	{
		ft_printf("pipex: %s: No such file or directory\n",
			command->error_allias);
	}
	else if (command->error == ERROR_OPENING_FILE)
	{
		ft_printf("pipex: %s: Error occured at file opening\n",
			command->error_allias);
	}
	if (command->error == COMMAND_NOT_FOUND)
	{
		ft_printf("%s: command not found\n", command->error_allias);
	}
}

void	add_error(t_command *command, t_command_errors error, char *allias)
{
	command->error = error;
	command->error_allias = allias;
}

void	print_commands_errors(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;

	current = data->commands_queue;
	while (current && current->content)
	{
		command = (t_command *)current->content;
		handle_errors(data, command);
		current = current->next;
	}
}
