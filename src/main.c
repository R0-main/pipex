/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/22 14:33:01 by rguigneb         ###   ########.fr       */
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
	while (current)
	{
		if (pipe((int *)(&parent_to_child)) == -1)
			return ;
		if (pipe((int *)(&child_to_parent)) == -1)
			return ;
		// printf("command : %s\n", ((command_t *)current->content)->argv[0]);
		if (first)
		{
			first = false;
			ft_printf("execute with file as input : \n");
			fd = open("file1", O_RDONLY);
			while (read(fd, &c, 1))
				write(parent_to_child.write, &c, 1);
			close(fd);
		}
		close(parent_to_child.write);
		exec_command(current->content, parent_to_child, child_to_parent);
		close(parent_to_child.read);
		close(child_to_parent.write);
		wait(NULL);
		if (pipe((int *)(&parent_to_child)) == -1)
			return ;
		while (read(child_to_parent.read, &c, 1))
		{
			write(parent_to_child.write, &c, 1);
		}
		close(child_to_parent.read);
		close(parent_to_child.write);
		if (pipe((int *)(&child_to_parent)) == -1)
			return ;
		if (current->next && current->next->content)
			exec_command(current->next->content, parent_to_child,
				child_to_parent);
		wait(NULL);
		close(child_to_parent.write);
		close(parent_to_child.read);
		while (read(child_to_parent.read, &c, 1))
		{
			write(1, &c, 1);
		}
		close(child_to_parent.read);
		current = current->next;
	}
}

static void	add_to_commands_queue(pipex_data_t *data, char *argv, char **envp)
{
	command_t	*command;
	t_list		*lst;
	char		*trimmed;

	command = (command_t *)malloc(sizeof(command_t));
	if (!command)
		return ;
	lst = ft_lstnew(command);
	if (!lst)
		return ;
	trimmed = ft_strtrim(argv, "\n\r\t\v ");
	command->argv = ft_split(trimmed, ' ');
	command->envp = envp;
	free(trimmed);
	ft_lstadd_back(&data->commands_queue, lst);
}

int	main(int argc, char const **argv, char const **envp)
{
	int				fd[2];
	int				fd2;
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
	// fd2 = open(data.out_file, O_WRONLY);
	// dup2(fd2, 1);
	while (i < argc - 1)
	{
		add_to_commands_queue(&data, (char *)argv[i], (char **)envp);
		i++;
	}
	proccess_command_queue(&data);
	// handle_commands(data.out_file, data.out_file, argv[2], envp);
	// close(fd2);
	// write(1, "fwfq\n\n", 6);
	// exec = execve("/usr/bin/ls", argt, envp);
	// close(fd2);
	// printf("===== fwqfqfqfq %d\n", exec);
	return (0);
}

// int	main(int argc, char const *argv[])
// {
// 	int	i;
// 	int	y;

// 	i = 0;
// 	if (argc == 2)
// 	{
// 		while (argv[1][i])
// 		{
// 			if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
// 				y = 'A';
// 			else
// 				y = 'a';
// 			if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A'
// 					&& argv[1][i] <= 'Z'))
// 			{
// 				while (y <= argv[1][i])
// 				{
// 					y++;
// 					write(1, &argv[1][i], 1);
// 				}
// 				write(1, "\n", 1);
// 			}
// 			i++;
// 		}
// 	}
// 	else
// 		write(1, "\n", 1);
// 	return (0);
// }
