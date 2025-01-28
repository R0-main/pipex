/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 16:39:52 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "ft_printf.h"
#include "get_next_line.h"
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
	data->here_doc = false;
}

static void	handle_here_doc(int argc, char const **argv, char const **envp,
		t_pipex_data *data)
{
	char	*line;
	t_pipe	in_pipe;
	int		i;

	if (pipe((int *)(&in_pipe)) == -1)
		safe_exit();
	printf("heredoc PIPE : %d %d\n", in_pipe.read, in_pipe.write);
	data->here_doc = true;
	while (true)
	{
		line = get_next_line(1);
		write(in_pipe.write, line, ft_strlen(line));
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
	}
	free_garbadge();
	close(in_pipe.write);
	data->here_doc_pipe = in_pipe;
}

int	main(int argc, char const **argv, char const **envp)
{
	t_pipex_data	data;
	int				i;

	i = 2;
	if (argc < 5)
	{
		ft_printf("argc error\n");
		return (EXIT_FAILURE);
	}
	if (!envp)
	{
		ft_printf("envp_error\n");
		return (EXIT_FAILURE);
	}
	init_pipex_data(argc, argv, envp, &data);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		handle_here_doc(argc, argv, envp, &data);
		i++;
	}
	while (i < argc - 1)
		add_to_commands_queue(&data, (char *)argv[i++], (char **)envp);
	proccess_command_queue(&data);
	free_garbadge();
	return (EXIT_SUCCESS);
}
