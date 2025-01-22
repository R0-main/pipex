/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/22 09:47:43 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	handle_commands(const char *in_file, const char *out_file,
		char const *arg, char const **envp)
{
	char	**command;
	int		fd;
	char	*trim;
	if (pipe(fd) == -1)
		ft_printf("ERROR at Pipe in exec_command");
	trim = ft_strtrim(arg, "\n\r\t\v ");
	command = ft_split(trim, ' ');
	free(trim);
	exec_command((const char **)command, envp);
	free_split_until_end(command, 0);
}

int	main(int argc, char const **argv, char const **envp)
{
	int				fd[2];
	int				fd2;
	pipex_data_t	data;
	int				i;

	i = 1;
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
	// fd2 = open(data.out_file, O_WRONLY);
	// dup2(fd2, 1);
	// while (i < argc - 3)
	// {
	// 	if (i == 1)
	// 		handle_commands(data.in_file, data.out_file, argv[i], envp);
	// 	else
	// 		handle_commands(data.out_file, data.out_file, argv[i], envp);
	// 	i++;
	// }
	handle_commands(data.out_file, data.out_file, argv[2], envp);
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
