/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/22 12:36:40 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

void	exec_command(command_t *command, pipe_t pipes)
{
	pid_t	fork_id;
	char	**path_env;
	int		i;
	char	*command_name;
	char	*path;
	char	c;

	i = 0;
	fork_id = fork();
	if (fork_id == 0)
	{
		printf("read : %d | write %d\n", pipes.read, pipes.write);
		dup2(pipes.read, STDIN_FILENO);
		dup2(STDOUT_FILENO, pipes.write);
		close(pipes.write);
		close(pipes.read);
		path_env = ft_split(get_env("PATH", (const char **)command->envp), ':');
		while (path_env[i])
		{
			path = get_full_path(path_env[i]);
			command_name = ft_strjoin(path, command->argv[0]);
			free(path);
			free(path_env[i++]);
			execve(command_name, (char *const *)command->argv,
				(char *const *)command->envp);
			free(command_name);
		}
		free(path_env);
	}
}
