/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:50:14 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 10:59:23 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"

static pipe_t	get_out_pipe(pipex_data_t *data, t_list *current)
{
	pipe_t	out_pipe;

	if (!current->next)
	{
		out_pipe.read = -1;
		out_pipe.write = open(data->out_file, O_WRONLY);
		if (out_pipe.write == -1)
			ft_printf("ERROR at out_pipe");
	}
	else
	{
		if (pipe((int *)(&out_pipe)) == -1)
			safe_exit();
	}
	return (out_pipe);
}

static pipe_t	get_in_pipe(pipex_data_t *data, bool *first)
{
	pipe_t	in_pipe;

	if (*first)
	{
		*first = false;
		in_pipe.read = -1;
		in_pipe.read = open(data->in_file, O_RDONLY);
		if (in_pipe.read == -1)
			ft_printf("ERROR at inpipe");
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
	t_list	*current;
	pipe_t	in_pipe;
	pipe_t	out_pipe;
	bool	first;

	first = true;
	current = data->commands_queue;
	while (current && current->content)
	{
		in_pipe = get_in_pipe(data, &first);
		out_pipe = get_out_pipe(data, current);
		((command_t *)current->content)->in_pipe = in_pipe;
		((command_t *)current->content)->out_pipe = out_pipe;
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
			close(command->in_pipe.write);
			close(command->in_pipe.read);
			command->in_pipe = prev->out_pipe;
		}
		prev = command;
		current = current->next;
	}
}
