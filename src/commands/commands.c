/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/24 14:06:34 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_printf.h"
#include "garbadge.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

void	exec_command(command_t *command)
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
		dup2(command->in_pipe.read, STDIN_FILENO);
		dup2(command->out_pipe.write, STDOUT_FILENO);
		close(command->out_pipe.read);
		close(command->in_pipe.write);
		close(command->in_pipe.read);
		close(command->out_pipe.write);
		path_env = ft_split(get_env("PATH", (const char **)command->envp), ':');
		while (path_env && path_env[i])
		{
			command_name = ft_strjoin(get_full_path(path_env[i++]),
					command->argv[0]);
			execve(command_name, (char *const *)command->argv,
				(char *const *)command->envp);
		}
		free_garbadge();
		exit(EXIT_FAILURE);
	}
}
