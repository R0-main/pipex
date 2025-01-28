/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 09:45:56 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "ft_printf.h"
#include "libft.h"
#include "pipex.h"

void	init_pipex_data(int argc, char const **argv, char const **envp,
		t_pipex_data *data)
{
	data->in_file = (char *)argv[1];
	data->out_file = (char *)argv[argc - 1];
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->out_file_fd = -1;
	data->in_file_fd = -1;
	data->commands_queue = NULL;
}

int	main(int argc, char const **argv, char const **envp)
{
	t_pipex_data	data;
	int				i;

	i = 2;
	if (argc < 5)
	{
		ft_printf("argc error");
		return (EXIT_FAILURE);
	}
	if (!envp)
	{
		ft_printf("envp_error");
		return (EXIT_FAILURE);
	}
	init_pipex_data(argc, argv, envp, &data);
	while (i < argc - 1)
		add_to_commands_queue(&data, (char *)argv[i++], (char **)envp);
	proccess_command_queue(&data);
	free_garbadge();
	return (EXIT_SUCCESS);
}
