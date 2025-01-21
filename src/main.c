/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/21 14:55:58 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char const **argv, char const **envp)
{
	int			fd[2];
	const char	**argt = {&argv[1], &argv[2], NULL};
	int			exec;
	int			fd2;
	char		*in_file;
	char		*out_file;
	char		*line;

	// char	*args[4] = {"ls", "-R", "", NULL};
	// if (argc < 4)
	// {
	// 	printf("argc error");
	// 	return (EXIT_FAILURE);
	// }
	if (!envp)
	{
		printf("envp_error");
		return (EXIT_FAILURE);
	}
	in_file = argv[1];
	out_file = argv[argc - 1];
	// fd2 = open("test.txt", O_WRONLY | O_APPEND);
	// close(fd2);
	// dup2(fd2, 1);
	// write(1, "fwfq\n\n", 6);
	// exec = execve("/usr/bin/ls", argt, envp);
	// printf("===== fwqfqfqfq %d\n", exec);
	line = malloc(1);
	while (line)
	{
		ft_printf("minishell : ");
		line = get_next_line(1);
		// exec_command(ft_split(ft_strtrim(line, "\n"), ' '), envp);
	}
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
