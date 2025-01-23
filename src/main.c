/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/23 10:38:23 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// AWK ERROR ?
static void	proccess_command_queue(pipex_data_t *data)
{
	pipe_t	parent_to_child;
	pipe_t	child_to_parent;
	t_list	*current;
	bool	first;
	int		fd;
	int		old_read;
	char	c;

	first = true;
	current = data->commands_queue;
	child_to_parent = (pipe_t){0, 0};
	while (current && current->content)
	{
		if (pipe((int *)(&parent_to_child)) == -1)
			return ;
		if (child_to_parent.read)
		{
			close(child_to_parent.write);
			while (read(child_to_parent.read, &c, 1))
				write(parent_to_child.write, &c, 1);
			close(child_to_parent.read);
		}
		else
		{
			fd = open(data->in_file, O_RDONLY);
			while (read(fd, &c, 1))
				write(parent_to_child.write, &c, 1);
			close(fd);
		}
		if (pipe((int *)(&child_to_parent)) == -1)
			return ;
		close(parent_to_child.write);
		exec_command(current->content, parent_to_child, child_to_parent);
		free_split_until_end(((command_t *)current->content)->argv, 0);
		close(parent_to_child.read);
		close(child_to_parent.write);
		if (!current->next)
		{
			fd = open(data->out_file, O_WRONLY);
			while (read(child_to_parent.read, &c, 1))
				write(1, &c, 1);
			close(fd);
		}
		current = current->next;
	}
	close(child_to_parent.read);
}

static void	add_to_commands_queue(pipex_data_t *data, char *argv, char **envp)
{
	command_t	*command;
	t_list		*lst;

	command = (command_t *)malloc(sizeof(command_t));
	if (!command)
		return ;
	lst = ft_lstnew(command);
	if (!lst)
		return ;

	command->argv = get_parsed_command(argv);
	command->envp = envp;
	ft_lstadd_back(&data->commands_queue, lst);
}

int	main(int argc, char const **argv, char const **envp)
{
	pipex_data_t	data;
	int				i;

	i = 2;
	if (argc < 4)
	{
		printf("argc error");
		return (EXIT_FAILURE);
	}
	if (!envp)
	{
		printf("envp_error");
		return (EXIT_FAILURE);
	}
	data.in_file = argv[1];
	data.out_file = argv[argc - 1];
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.commands_queue = NULL;
	while (i < argc - 1)
	{
		add_to_commands_queue(&data, (char *)argv[i], (char **)envp);
		i++;
	}
	proccess_command_queue(&data);
	ft_lstclear(&data.commands_queue, free);
	return (0);
}
