/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:52:26 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 11:19:46 by rguigneb         ###   ########.fr       */
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
typedef struct s_pipe
{
	int					read;
	int					write;
}						t_pipe;

typedef struct s_pipex_data
{
	int					argc;
	char const			**argv;
	char const			**envp;
	char				*in_file;
	char				*out_file;
	t_list				*commands_queue;
	int					in_file_fd;
	int					out_file_fd;
	bool				here_doc;
	t_pipe				here_doc_pipe;
}						t_pipex_data;

/*******************************parsing****************************************/
int						get_next_space_char_index(char *str);
int						get_next_char_index(char *str, int c);
bool					char_exist_in(char *str, int c);
bool					not_only_spaces_until_end(char *str);

char					**get_parsed_command(char *argv);

/*******************************commands***************************************/
void					proccess_command_queue(t_pipex_data *data);
void					add_to_commands_queue(t_pipex_data *data, char *argv,
							char **envp);
void					init_commands_pipes(t_pipex_data *data);
void					link_commands_pipes(t_pipex_data *data);

#endif
