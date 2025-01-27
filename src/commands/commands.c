/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 14:15:56 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_printf.h"
#include "garbadge.h"
#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

void	exec_command(pipex_data_t *data, command_t *command)
{
	pid_t	fork_id;
	char	**path_env;
	int		i;
	char	*command_name;
	int		c;

	i = 0;
	fork_id = fork();
	if (fork_id == 0)
	{
		reset_garbadge();
		close(command->in_pipe.write);
		close(command->out_pipe.read);
		if (command->error == PERMISSION_DENIED)
		{
			ft_printf("pipex: %s: Permission denied\n", command->error_allias);
			close(command->in_pipe.read);
			close(command->out_pipe.write);
			exit(EXIT_FAILURE);
		}
		else if (command->error == NO_SUCH_FILE_OR_DIRECTORY)
		{
			ft_printf("pipex: %s: No such file or directory\n", command->error_allias);
			close(command->in_pipe.read);
			close(command->out_pipe.write);
			exit(EXIT_FAILURE);
		}
		else if (command->error == ERROR_OPENING_FILE)
		{
			ft_printf("pipex: %s: Error occured at file opening !\n", command->error_allias);
			close(command->in_pipe.read);
			close(command->out_pipe.write);
			exit(EXIT_FAILURE);
		}
		dup2(command->in_pipe.read, STDIN_FILENO);
		dup2(command->out_pipe.write, STDOUT_FILENO);
		close(command->in_pipe.read);
		close(command->out_pipe.write);
		close(data->in_file_fd);
		close(data->out_file_fd);
		path_env = ft_split(get_env("PATH", (const char **)command->envp), ':');
		while (path_env && path_env[i])
		{
			command_name = ft_strjoin(get_full_path(path_env[i++]),
					command->argv[0]);
			execve(command_name, (char *const *)command->argv,
				(char *const *)command->envp);
		}
		// free_garbadge();
		exit(EXIT_FAILURE);
	}
	else
	{
		close(command->in_pipe.write);
		close(command->in_pipe.read);
		close(command->out_pipe.write);
	}
}
// printf("cmd : %s %s | ir : %d , iw : %d | or : %d , ow : %d\n",
// 	command->argv[0], command->argv[1], command->in_pipe.read,
// command->in_pipe.write,
// 	command->out_pipe.read, command->out_pipe.write);
