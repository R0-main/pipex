/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/21 15:58:35 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEXX_H
# define PIPEXX_H

/******************************************************************************/
typedef struct pipex_data_s
{
	int			argc;
	char const	**argv;
	char const	**envp;
	const char	*in_file;
	const char	*out_file;
}				pipex_data_t;

#endif
