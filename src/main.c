/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 12:43:54 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "ft_printf.h"
#include "libft.h"
#include "pipex.h"

int	main(int argc, char const **argv, char const **envp)
{
	pipex_data_t	data;
	int				i;
	bool			failed;

	i = 2;
	failed = false;
	if (argc < 4)
	{
		ft_printf("argc error");
		return (EXIT_FAILURE);
	}
	if (!envp)
	{
		ft_printf("envp_error");
		return (EXIT_FAILURE);
	}

	data.in_file = argv[1];
	data.out_file = argv[argc - 1];

	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.commands_queue = NULL;

	while (i < argc - 1)
		add_to_commands_queue(&data, (char *)argv[i++], (char **)envp);
	proccess_command_queue(&data);
	free_garbadge();
	return (0);
}
