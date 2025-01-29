/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:51:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 11:12:17 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"

void	proccess_command_queue(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;
	pid_t		wpid;

	current = data->commands_queue;
	command = (t_command *)data->commands_queue->content;
	init_commands_pipes(data);
	link_commands_pipes(data);
	check_if_commands_exist(data);
	print_commands_errors(data);
	while (current && current->content)
	{
		command = (t_command *)current->content;
		if (command->argv)
			exec_command(data, command);
		current = current->next;
	}
	wpid = 1;
	while (wpid > 0)
	{
		wpid = wait(NULL);
	}
}
