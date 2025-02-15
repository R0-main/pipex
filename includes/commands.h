/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:18 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 13:11:24 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "errors.h"
# include "pipex.h"

typedef struct s_command
{
	char				**argv;
	char				**envp;
	t_pipe				in_pipe;
	t_pipe				out_pipe;
	t_command_errors	error;
	char				*error_allias;
}						t_command;

/******************************************************************************/
void					exec_command(t_pipex_data *data, t_command *command);
void					check_if_commands_exist(t_pipex_data *data);
char					**get_parsed_command(char *argv);

void					close_pipes_until_end(t_pipex_data *data,
							t_command *target);
#endif
