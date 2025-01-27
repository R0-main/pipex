/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 09:02:44 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_strings.h"
# include <stdbool.h>



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

/*******************************parsing****************************************/
int				get_next_space_char_index(char *str);
int				get_next_char_index(char *str, int c);
bool			char_exist_in(char *str, int c);
bool			not_only_spaces_until_end(char *str);

char			**get_parsed_command(char *argv);

#endif
