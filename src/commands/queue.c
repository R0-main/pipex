/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:47:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/29 11:11:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "pipex.h"

void	add_to_commands_queue(t_pipex_data *data, char *argv, char **envp)
{
	t_command	*command;
	t_list		*lst;

	command = (t_command *)safe_malloc(sizeof(t_command));
	command->error = NO_ERROR;
	command->error_allias = NULL;
	lst = ft_lstnew(command);
	if (argv)
		command->argv = get_parsed_command(argv);
	else
		command->argv = NULL;
	command->envp = envp;
	ft_lstadd_back(&data->commands_queue, lst);
}
