/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:50:14 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 08:46:44 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"
#include <fcntl.h>

static t_pipe	get_out_pipe(t_pipex_data *data, t_command *command,
		t_list *current)
{
	t_pipe	out_pipe;
	int		options;

	options = O_WRONLY | O_CREAT;
	if (data->here_doc)
		options = options | O_APPEND;
	if (!current->next)
	{
		out_pipe.read = 0;
		out_pipe.write = 0;
		if (access(data->out_file, F_OK) == 0
			&& access(data->out_file, W_OK) == -1)
			add_error(command, PERMISSION_DENIED, data->out_file);
		else
		{
			data->out_file_fd = open(data->out_file, options, 0666);
			if (data->out_file_fd == -1)
				add_error(command, ERROR_OPENING_FILE, data->out_file);
			out_pipe.write = data->out_file_fd;
		}
	}
	else if (pipe((int *)(&out_pipe)) == -1)
		safe_exit();
	return (out_pipe);
}

static t_pipe	get_in_pipe(t_pipex_data *data, t_command *command, bool *first)
{
	t_pipe	in_pipe;

	if (*first)
	{
		*first = false;
		in_pipe.write = 0;
		in_pipe.read = 0;
		if (access(data->in_file, F_OK) == -1)
			add_error(command, NO_SUCH_FILE_OR_DIRECTORY, data->in_file);
		else if (access(data->in_file, R_OK) == -1)
			add_error(command, PERMISSION_DENIED, data->in_file);
		else
		{
			data->in_file_fd = open(data->in_file, O_RDONLY);
			if (data->in_file_fd == -1)
				add_error(command, ERROR_OPENING_FILE, data->out_file);
			in_pipe.read = data->in_file_fd;
		}
	}
	else
	{
		if (pipe((int *)(&in_pipe)) == -1)
			safe_exit();
	}
	return (in_pipe);
}

void	init_commands_pipes(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;
	t_pipe		in_pipe;
	t_pipe		out_pipe;
	bool		first;

	first = true;
	current = data->commands_queue;
	while (current && current->content)
	{
		command = (t_command *)current->content;
		if (first && data->here_doc)
		{
			first = false;
			command->in_pipe = data->here_doc_pipe;
		}
		else
		{
			in_pipe = get_in_pipe(data, command, &first);
			command->in_pipe = in_pipe;
		}
		out_pipe = get_out_pipe(data, command, current);
		command->out_pipe = out_pipe;
		current = current->next;
	}
}

void	link_commands_pipes(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;
	t_command	*prev;

	current = data->commands_queue;
	prev = NULL;
	while (current && current->content)
	{
		command = (t_command *)current->content;
		if (prev)
		{
			close(command->in_pipe.write);
			close(command->in_pipe.read);
			command->in_pipe = prev->out_pipe;
		}
		prev = command;
		current = current->next;
	}
}
