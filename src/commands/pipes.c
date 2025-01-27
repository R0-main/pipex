/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:50:14 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 15:04:48 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"
#include <fcntl.h>

static pipe_t	get_out_pipe(pipex_data_t *data, command_t *command,
		t_list *current)
{
	pipe_t	out_pipe;

	if (!current->next)
	{
		out_pipe.read = 0;
		out_pipe.write = 0;
		if (access(data->out_file, F_OK) == 0 && access(data->out_file, W_OK) ==
			-1)
		{
			command->error = PERMISSION_DENIED;
			command->error_allias = data->out_file;
		}
		else
		{
			data->out_file_fd = open(data->out_file, O_WRONLY | O_CREAT, 0666);
			if (data->out_file_fd == -1)
			{
				command->error = ERROR_OPENING_FILE;
				command->error_allias = data->out_file;
			}
			out_pipe.write = dup(data->out_file_fd);
			close(data->out_file_fd);
		}
	}
	else
	{
		if (pipe((int *)(&out_pipe)) == -1)
			safe_exit();
	}
	return (out_pipe);
}

static pipe_t	get_in_pipe(pipex_data_t *data, command_t *command, bool *first)
{
	pipe_t	in_pipe;

	if (*first)
	{
		*first = false;
		in_pipe.write = 0;
		in_pipe.read = 0;
		if (access(data->in_file, F_OK) == -1)
		{
			command->error = NO_SUCH_FILE_OR_DIRECTORY;
			command->error_allias = data->in_file;
		}
		else if (access(data->in_file, R_OK) == -1)
		{
			command->error = PERMISSION_DENIED;
			command->error_allias = data->in_file;
		}
		else
		{
			data->in_file_fd = open(data->in_file, O_RDONLY);
			if (data->in_file_fd == -1)
			{
				command->error = ERROR_OPENING_FILE;
				command->error_allias = data->out_file;
			}
			in_pipe.read = dup(data->in_file_fd);
			close(data->in_file_fd);
		}
	}
	else
	{
		if (pipe((int *)(&in_pipe)) == -1)
			safe_exit();
	}
	return (in_pipe);
}

void	init_commands_pipes(pipex_data_t *data)
{
	t_list		*current;
	command_t	*command;
	pipe_t		in_pipe;
	pipe_t		out_pipe;
	bool		first;

	first = true;
	current = data->commands_queue;
	while (current && current->content)
	{
		command = (command_t *)current->content;
		in_pipe = get_in_pipe(data, command, &first);
		out_pipe = get_out_pipe(data, command, current);
		command->in_pipe = in_pipe;
		command->out_pipe = out_pipe;
		current = current->next;
	}
}

void	link_commands_pipes(pipex_data_t *data)
{
	t_list		*current;
	command_t	*command;
	command_t	*prev;

	current = data->commands_queue;
	prev = NULL;
	while (current && current->content)
	{
		command = (command_t *)current->content;
		if (prev)
		{
			safe_close(command->in_pipe.write);
			safe_close(command->in_pipe.read);
			command->in_pipe = prev->out_pipe;
		}
		prev = command;
		current = current->next;
	}
}

void	safe_close(int fd)
{
	if (fd && fd != -1)
		close(fd);
}
