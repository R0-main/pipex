/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:51:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 15:22:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

static void	wait_all_commands_executions(t_pipex_data *data)
{
	pid_t	wpid;
	int		status;

	wpid = 1;
	status = 0;
	while (wpid > 0)
	{
		wpid = wait(&status);
		if (wpid > 0 && WIFEXITED(status) && data->error_code != 127)
			data->error_code = WEXITSTATUS(status);
	}
}

void	proccess_command_queue(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;

	current = data->commands_queue;
	if (!current || !current->content)
		return ;
	command = (t_command *)current->content;
	if (!command)
		return ;
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
	wait_all_commands_executions(data);
}
