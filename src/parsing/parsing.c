/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:26:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/23 12:22:18 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "libft.h"
#include "strings.h"
#include <stdbool.h>
#include <stdio.h>

int	split_len(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		i++;
	return (i);
}

int	get_args_count_with_char_delimiter(char *argv, char c)
{
	char	**quote_args;
	char	**double_quote_args;
	int		i;
	int		total;

	i = -1;
	total = 0;
	quote_args = ft_split(argv, c);
	while (quote_args[++i])
	{
		if (c == ' ' && (ft_strchr(quote_args[i], '\'')
					|| ft_strchr(quote_args[i], '"')))
			continue ;
		if (i % 2 != 0)
			total++;
	}
	return (total);
}

int	get_next_space_char_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

int	get_next_char_index(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

bool	char_exist_in(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == c)
			return (true);
	return (false);
}

bool	not_only_this_char_until_end(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i++] != c)
		return (false);
	return (true);
}

bool	not_only_spaces_until_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		return (false);
	return (true);
}

bool	closing_brackets_is_followed_by_space(char *str)
{
	int	i;

	i = 0;
	if (ft_isspace(get_next_char_index(str + 1, '\'') + 1))
		return (false);
	return (true);
}

int	get_args_count(char *argv)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	total += get_args_count_with_char_delimiter(argv, ' ');
	total += get_args_count_with_char_delimiter(argv, '\'');
	total += get_args_count_with_char_delimiter(argv, '"');
	return (total);
}

typedef struct string_token_s
{
	bool			finished;
	bool			started;
	int				start;
}					string_token_t;

typedef struct parsing_flags_s
{
	string_token_t	command;
	string_token_t	quote;
	string_token_t	double_quote;
	string_token_t	space;
}					parsing_flags_t;

char	**get_parsed_command(char *argv)
{
	char			**final;
	char			*trimmed;
	int				i;
	int				args_count;
	parsing_flags_t	flags;
	int				d;
	int				next_index;
	int				space;
	int				next_space_after_last_quote;

	i = -1;
	final = malloc(10000);
	args_count = 1;
	ft_memset(&flags, 0, sizeof(parsing_flags_t));
	// set final to null
	while (argv[++i])
	{
		// printf("%s\n", argv + i);
		if (flags.command.finished == false)
		{
			final[0] = ft_substr(argv, 0, get_next_space_char_index(argv));
			i += get_next_space_char_index(argv);
			flags.command.finished = true;
		}
		if (ft_isspace(argv[i]))
		{
			while (ft_isspace(argv[i + 1]))
				i++;
			if (char_exist_in(argv + i, '\'') && get_next_char_index(argv + i,
					'\'') <= get_next_space_char_index(argv + i + 1))
				continue ;
			if (!not_only_spaces_until_end(argv + i + 1))
			{
				final[args_count++] = ft_substr(argv, i + 1,
						get_next_space_char_index(argv + i + 1));
				i += get_next_space_char_index(argv + i + 1);
			}
		}
		else if (argv[i] == '\'')
		{
			next_index = get_next_char_index(argv + i + 1, '\'') + 1;
			if (!ft_isspace(argv[i + next_index + 1]) && argv[i + next_index + 1] != 0)
			{
				next_space_after_last_quote = get_next_space_char_index(argv + i
						+ next_index);
				final[args_count++] = ft_substr(argv, i, next_index
						+ next_space_after_last_quote);
				i += next_index + next_space_after_last_quote - 1;
			}
			else
			{
				final[args_count++] = ft_substr(argv, i + 1, next_index - 1);
				i += next_index;
			}
		}
		else if (argv[i] == '"')
		{
			if (!not_only_this_char_until_end(argv + i + 1, '"'))
			{
				final[args_count++] = ft_substr(argv, i + 1,
						get_next_char_index(argv + i + 1, '"'));
				i += get_next_char_index(argv + i + 1, '"');
			}
		}
	}
	final[args_count] = NULL;
	d = 0;
	// while (final[d])
	// {
	// 	printf("args : %s|\n", final[d]);
	// 	d++;
	// }
	return (final);
}
