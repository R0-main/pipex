/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:51:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 12:25:57 by rguigneb         ###   ########.fr       */
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
	wpid = 1;
	while (wpid > 0)
	{
		wpid = wait(NULL);
	}
	close(prev->out_pipe.write);
}
/*
	if (access(argv[1], R_OK) == -1)
	{
		data.in_file_failed = true;
		ft_printf("piex: %s: Permission denied\n", argv[1]);
	}
	else
	{
		data.in_file = open(argv[1], O_RDONLY);
		if (data.in_file == -1)
			ft_printf("piex: %s: No such file or diretory\n", argv[1]);
	}

	if (access(argv[argc - 1], W_OK) == -1)
	{
		data.out_file_failed = true;
		ft_printf("piex: %s: Permission denied\n", argv[argc - 1]);
	}
	else
	{
		data.out_file = open(argv[argc - 1], O_WRONLY);
		if (data.out_file == -1)
			ft_printf("piex: %s: No such file or diretory\n", argv[argc - 1]);
	}*/
