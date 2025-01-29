/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:47:13 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 10:35:31 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"

static bool	can_execute_command(t_command *command)
{
	char	*command_name;
	int		i;
	char	**path_env;

	i = 0;
	path_env = ft_split(get_env("PATH", (const char **)command->envp), ':');
	while (path_env && path_env[i])
	{
		command_name = ft_strjoin(ft_strjoin(path_env[i++], "/"),
				command->argv[0]);
		if (access(command_name, F_OK) == 0)
			return (true);
	}
	if (access(command->argv[0], F_OK) == 0)
		return (true);
	return (false);
}

void	check_if_commands_exist(t_pipex_data *data)
{
	t_list		*current;
	t_command	*command;

	current = data->commands_queue;
	while (current && current->content)
	{
		command = (t_command *)current->content;
		if (command && command->argv && !can_execute_command(command))
			ft_fprintf(STDERR_FILENO, "%s: command not found\n", command->argv[0]);
		current = current->next;
	}
}
