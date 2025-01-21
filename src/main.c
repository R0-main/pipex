/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/21 13:12:53 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
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
	int		exec;
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
			printf("%s\n", path);
			free(path);
			free(path_env[i++]);
			exec = execve(command, (char *const *)argv, envp);
			free(command);
		}
		free(path_env);
	}
	else
	{
		wait(NULL);
		printf("Entered in\n");
	}
}

int	main(int argc, char const **argv, char const **envp)
{
	int			fd[2];
	const char	*argt[] = {argv[1], argv[2], NULL};
	int			exec;
	int			fd2;

	// char	*args[4] = {"ls", "-R", "", NULL};
	(void)argc;
	(void)argv;
	if (!envp)
	{
		printf("envp_error");
		return (EXIT_FAILURE);
	}
	fd2 = open("test.txt", O_WRONLY | O_APPEND);
	close(fd2);
	// dup2(fd2, 1);
	// write(1, "fwfq\n\n", 6);
	// exec = execve("/usr/bin/ls", argt, envp);
	// printf("===== fwqfqfqfq %d\n", exec);
	exec_command(argt, envp);
	return ( 0);
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
