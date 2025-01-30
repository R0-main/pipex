/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:05:25 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/30 10:43:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_fprintf.h"
#include "get_next_line.h"
#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <string.h>

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
	data->error_code = 0;
	data->here_doc = false;
}

static void	handle_here_doc(char const **argv, t_pipex_data *data)
{
	char	*line;
	size_t	line_len;
	t_pipe	in_pipe;

	if (pipe((int *)(&in_pipe)) == -1)
		safe_exit();
	data->here_doc = true;
	while (true)
	{
		line = get_next_line(1);
		line_len = ft_strlen(line);
		if (line_len > 1 && ft_strncmp(line, argv[2], line_len - 1) == 0)
			break ;
		write(in_pipe.write, line, line_len);
	}
	free_garbadge();
	data->here_doc_pipe = in_pipe;
}

void	parse_commands(int argc, char const **argv, char const **envp,
		t_pipex_data *data)
{
	int	i;

	i = 2;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		handle_here_doc(argv, data);
		i++;
	}
	while (i < argc - 1)
		add_to_commands_queue(data, (char *)argv[i++], (char **)envp);
	proccess_command_queue(data);
}

int	main(int argc, char const **argv, char const **envp)
{
	t_pipex_data	data;
	int				i;

	if (argc < 5)
		return (print_error("pipex: arguments: invalid number of arguments\n"),
			EXIT_FAILURE);
	i = 0;
	while (argv[++i])
		if (!argv[i] || !argv[i][0])
			return (
				print_error("pipex: arguments: on of the arguments is NULL\n"),
				EXIT_FAILURE);
	if (!envp)
		return (print_error("pipex: environement: invalid environement\n"),
			EXIT_FAILURE);
	init_pipex_data(argc, argv, envp, &data);
	if (get_env("PATH", envp) != NULL)
		parse_commands(argc, argv, envp, &data);
	free_garbadge();
	return (data.error_code);
}
