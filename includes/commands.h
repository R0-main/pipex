/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:18 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 11:21:44 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "pipex.h"

typedef struct pipe_s
{
	int		read;
	int		write;
}			pipe_t;

typedef struct command_s
{
	char	**argv;
	char	**envp;
	pipe_t	in_pipe;
	pipe_t	out_pipe;
}			command_t;

/******************************************************************************/
void		exec_command(pipex_data_t *data, command_t *command);
char		**get_parsed_command(char *argv);

#endif
