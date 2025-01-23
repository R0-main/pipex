/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:50:39 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/23 14:52:33 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

bool	not_only_spaces_until_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		return (false);
	return (true);
}
