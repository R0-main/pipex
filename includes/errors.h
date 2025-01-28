/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:42 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 13:09:51 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdlib.h>
# include "pipex.h"

typedef struct s_command	t_command;

typedef enum e_command_errors
{
	PERMISSION_DENIED,
	NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_OPENING_FILE,
	COMMAND_NOT_FOUND,
}							t_command_errors;

/******************************************************************************/
void						add_error(t_command *command,
								t_command_errors error, char *allias);
void						print_commands_errors(t_pipex_data *data);

#endif
