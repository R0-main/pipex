/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:18 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 13:41:21 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "pipex.h"

typedef enum command_errors_e
{
	PERMISSION_DENIED,
	NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_OPENING_FILE,
}						command_errors_t;

typedef struct pipe_s
{
	int					read;
	int					write;
}						pipe_t;

typedef struct command_s
{
	char				**argv;
	char				**envp;
	pipe_t				in_pipe;
	pipe_t				out_pipe;
	command_errors_t	error;
	char				*error_allias;
}						command_t;

/******************************************************************************/
void					exec_command(pipex_data_t *data, command_t *command);
char					**get_parsed_command(char *argv);

#endif
