/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:51:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 09:48:21 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"

void	proccess_command_queue(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;
	t_command	*prev;
	pid_t		wpid;

	current = data->commands_queue;
	prev = NULL;
	command = (t_command *)data->commands_queue->content;
	init_commands_pipes(data);
	link_commands_pipes(data);
	while (current && current->content)
	{
		command = (t_command *)current->content;
		if (command->argv)
			exec_command(data, command);
		current = current->next;
		prev = command;
	}
	wpid = 1;
	while (wpid > 0)
	{
		wpid = wait(NULL);
	}
}
/*
 */
