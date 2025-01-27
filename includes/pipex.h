/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/27 11:20:58 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "ft_strings.h"
# include "garbadge.h"
# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>

/******************************************************************************/
typedef struct pipex_data_s
{
	int			argc;
	char const	**argv;
	char const	**envp;
	int			in_file;
	int			out_file;
	t_list		*commands_queue;
}				pipex_data_t;

/*******************************parsing****************************************/
int				get_next_space_char_index(char *str);
int				get_next_char_index(char *str, int c);
bool			char_exist_in(char *str, int c);
bool			not_only_spaces_until_end(char *str);

char			**get_parsed_command(char *argv);

/*******************************commands***************************************/
void			proccess_command_queue(pipex_data_t *data);
void			add_to_commands_queue(pipex_data_t *data, char *argv,
					char **envp);
void			init_commands_pipes(pipex_data_t *data);
void			link_commands_pipes(pipex_data_t *data);
void			safe_close(int fd);

#endif
