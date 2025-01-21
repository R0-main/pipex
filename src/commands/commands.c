/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:44 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/21 14:29:20 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_full_path(const char *path)
{
	return (ft_strjoin(path, "/"));
}

void	exec_command(const char **argv, const char **envp)
{
	pid_t	fork_id;
	char	**path_env;
	int		i;
	char	*command;
	char	*path;

	fork_id = fork();
	i = 0;
	if (fork_id == 0)
	{
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
		ft_printf("Command Not Found !\n");
		free(path_env);
	}
	else
		wait(NULL);
}
