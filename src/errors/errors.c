/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:39:23 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 09:59:09 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "commands.h"

void	add_error(t_command *command, t_command_errors error, char *allias)
{
	command->error = error;
	command->error_allias = allias;
}
