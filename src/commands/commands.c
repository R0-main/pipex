/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/22 09:47:54 by rguigneb         ###   ########.fr       */
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

void	exec_command(const char **argv, const char **envp, int pipe[2])
{
	pid_t	fork_id;
	char	**path_env;
	int		i;
	char	*command;
	char	*path;
	char	c;


	fork_id = fork();
	i = 0;
	if (fork_id == 0)
	{
		printf("wqfqfqfq\n\n\n\n");
		dup2(pipe[0], STDIN_FILENO);
		dup2(STDOUT_FILENO, pipe[1]);
		close(pipe[0]);
		close(pipe[1]);
		path_env = ft_split(get_env("PATH", envp), ':');
		while (path_env[i])
		{
			path = get_full_path(path_env[i]);
			command = ft_strjoin(path, argv[0]);
			free(path);
			free(path_env[i++]);
			execve(command, (char *const *)argv, (char *const *)envp);
			free(command);
		}
		free(path_env);
	}
	else
	{
		write(pipe[1], "test text\nwhere it has some tex fqfqft\n", 39);
		close(pipe[1]); // Close the write-end to signal EOF
		wait(NULL);
		while (read(pipe[0], &c, 1))
		{
			// write(1, "here : \n", 9);
			write(1, &c, 1);
		}
		close(pipe[0]);
		// write(1, &c, 1);
	}
	close(pipe[1]); // Close the write-end to signal EOF
	close(pipe[0]); // Close the write-end to signal EOF
}
