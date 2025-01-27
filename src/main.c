/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 10:44:11 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_printf.h"
#include "garbadge.h"
#include "get_next_line.h"
#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	init_commands_pipes(pipex_data_t *data)
{
	t_list	*current;
	pipe_t	in_pipe;
	pipe_t	out_pipe;
	bool	first;

	first = true;
	current = data->commands_queue;
	while (current && current->content)
	{
		if (first)
		{
			first = false;
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
		((command_t *)current->content)->in_pipe = in_pipe;
		((command_t *)current->content)->out_pipe = out_pipe;
		current = current->next;
	}
}

static void	link_commands_pipes(pipex_data_t *data)
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

static void	close_all_pipes(pipex_data_t *data)
{
	t_list		*current;
	command_t	*command;

	current = data->commands_queue;
	while (current && current->content && current->next)
	{
		command = (command_t *)current->content;
		close(command->in_pipe.read);
		if (command->in_pipe.write != 1)
			close(command->in_pipe.write);
		current = current->next;
	}
}

static void	proccess_command_queue(pipex_data_t *data)
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
		exec_command(command);
		current = current->next;
		prev = command;
	}
	wpid = 1;
	while (wpid > 0)
	{
		wpid = wait(NULL);
	}
}

static void	add_to_commands_queue(pipex_data_t *data, char *argv, char **envp)
{
	command_t	*command;
	t_list		*lst;

	command = (command_t *)safe_malloc(sizeof(command_t));
	lst = ft_lstnew(command);
	command->argv = get_parsed_command(argv);
	command->envp = envp;
	ft_lstadd_back(&data->commands_queue, lst);
}

void	free_command(command_t *command)
{
	if (!command || !command->argv)
		return ;
	if (command->argv)
		free_split_until_end(command->argv, 0);
	free(command);
}

int	main(int argc, char const **argv, char const **envp)
{
	pipex_data_t	data;
	int				i;

	i = 2;
	if (argc < 4)
	{
		ft_printf("argc error");
		return (EXIT_FAILURE);
	}
	if (!envp)
	{
		ft_printf("envp_error");
		return (EXIT_FAILURE);
	}
	data.in_file = argv[1];
	data.out_file = argv[argc - 1];
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.commands_queue = NULL;
	// if (!access(data.in_file, F_OK))
	// 	data.in_file = NULL;
	while (i < argc - 1)
		add_to_commands_queue(&data, (char *)argv[i++], (char **)envp);
	proccess_command_queue(&data);
	free_garbadge();
	return (0);
}
