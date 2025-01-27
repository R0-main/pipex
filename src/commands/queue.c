/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:47:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 13:46:38 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"

void	add_to_commands_queue(pipex_data_t *data, char *argv, char **envp)
{
	command_t	*command;
	t_list		*lst;

	command = (command_t *)safe_malloc(sizeof(command_t));
	command->error = -1;
	lst = ft_lstnew(command);
	if (argv)
		command->argv = get_parsed_command(argv);
	else
		command->argv = NULL;
	command->envp = envp;
	ft_lstadd_back(&data->commands_queue, lst);
}
