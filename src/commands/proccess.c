/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:51:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 14:15:07 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"

void	proccess_command_queue(pipex_data_t *data)
{
	t_list		*current;
	command_t	*command;
	command_t	*prev;
	pid_t		wpid;

	current = data->commands_queue;
	prev = NULL;
	command = (command_t *)data->commands_queue->content;
	init_commands_pipes(data);
	link_commands_pipes(data);
	while (current && current->content)
	{
		command = (command_t *)current->content;
		if (command->argv)
			exec_command(data, command);
		current = current->next;
		prev = command;
	}
	close(data->in_file_fd);
	close(data->out_file_fd);
	wpid = 1;
	while (wpid > 0)
	{
		wpid = wait(NULL);
	}
}
/*
 */
