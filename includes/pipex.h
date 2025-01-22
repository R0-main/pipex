/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/22 10:53:24 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/******************************************************************************/
typedef struct pipex_data_s
{
	int			argc;
	char const	**argv;
	char const	**envp;
	const char	*in_file;
	const char	*out_file;
	t_list		*commands_queue;
}				pipex_data_t;

#endif
