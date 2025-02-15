/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 15:07:25 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_fprintf.h"
#include "garbadge.h"
#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	close_pipes_until_end(t_pipex_data *data, t_command *target)
{
	t_list		*current;
	t_command	*command;

	current = data->commands_queue;
	while (current && current->content != target)
	{
		current = current->next;
	}
	if (current)
		current = current->next;
	while (current && current->content)
	{
		command = (t_command *)current->content;
		if (command->in_pipe.read)
			safe_close(command->in_pipe.read);
		if (command->in_pipe.write)
			safe_close(command->in_pipe.write);
		current = current->next;
	}
	if (data->in_file_fd != -1)
		safe_close(data->in_file_fd);
	if (data->out_file_fd != -1)
		safe_close(data->out_file_fd);
}

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

static void	execute_for_every_paths(t_command *command)
{
	char	*command_name;
	int		i;
	char	**path_env;

	i = 0;
	path_env = ft_split(get_env("PATH", (const char **)command->envp), ':');
	while (path_env && path_env[i])
	{
		command_name = ft_strjoin(get_full_path(path_env[i++]),
				command->argv[0]);
		execve(command_name, (char *const *)command->argv,
			(char *const *)command->envp);
	}
	execve(command->argv[0], (char *const *)command->argv,
		(char *const *)command->envp);
}

void	close_and_dup(t_command *command)
{
	if (command->in_pipe.write)
		safe_close(command->in_pipe.write);
	if (command->in_pipe.read)
		safe_close(command->out_pipe.read);
	dup2(command->in_pipe.read, STDIN_FILENO);
	dup2(command->out_pipe.write, STDOUT_FILENO);
	safe_close(command->in_pipe.read);
	safe_close(command->out_pipe.write);
}

void	exec_command(t_pipex_data *data, t_command *command)
{
	pid_t	fork_id;

	fork_id = fork();
	if (fork_id == -1)
		safe_exit();
	if (fork_id == 0)
	{
		close_and_dup(command);
		close_pipes_until_end(data, command);
		if (command->error == NO_ERROR)
			execute_for_every_paths(command);
		free_garbadge();
		exit(EXIT_FAILURE);
	}
	else
	{
		if (command->in_pipe.write)
			safe_close(command->in_pipe.write);
		if (command->in_pipe.read)
			safe_close(command->in_pipe.read);
		if (command->out_pipe.write)
			safe_close(command->out_pipe.write);
	}
}
// printf("cmd : %s %s | ir : %d , iw : %d | or : %d , ow : %d\n",
// 	command->argv[0], command->argv[1], command->in_pipe.read,
// command->in_pipe.write,
// 	command->out_pipe.read, command->out_pipe.write);
