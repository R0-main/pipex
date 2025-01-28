/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:26:50 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/28 09:44:57 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "env.h"
#include "ft_strings.h"
#include "garbadge.h"
#include "libft.h"
#include "pipex.h"
#include <stdio.h>

static void	handle_first(t_list **head, char *argv, int *i)
{
	t_list	*lst;
	char	*str;

	str = ft_substr(argv, 0, get_next_space_char_index(argv));
	lst = ft_lstnew(str);
	if (!lst)
		safe_exit();
	ft_lstadd_back(head, lst);
	*i += get_next_space_char_index(argv);
}

static void	handle_quote(t_list **head, char *argv, int *i)
{
	int		next_index;
	int		next_space_after_last_quote;
	char	*str;
	t_list	*lst;

	next_index = get_next_char_index(argv + *i + 1, '\'') + 1;
	if (
		!ft_isspace(argv[*i + next_index + 1])
		&& argv[*i + next_index + 1] != 0
	)
	{
		next_space_after_last_quote = get_next_space_char_index(argv + *i
				+ next_index);
		str = ft_substr(argv, *i, next_index + next_space_after_last_quote);
		lst = ft_lstnew(str);
		*i += next_index + next_space_after_last_quote - 1;
	}
	else
	{
		lst = ft_lstnew(ft_substr(argv, *i + 1, next_index - 1));
		*i += next_index;
	}
	if (!lst)
		safe_exit();
	ft_lstadd_back(head, lst);
}

static void	handle_spaces(t_list **head, char *argv, int *i)
{
	t_list	*lst;
	char	*str;

	while (ft_isspace(argv[*i + 1]))
		(*i)++;
	if (char_exist_in(argv + *i, '\'') && get_next_char_index(argv + *i,
			'\'') <= get_next_space_char_index(argv + *i + 1))
		return ;
	if (!not_only_spaces_until_end(argv + *i + 1))
	{
		str = ft_substr(argv, *i + 1, get_next_space_char_index(argv + *i + 1));
		lst = ft_lstnew(str);
		if (!lst)
			safe_exit();
		ft_lstadd_back(head, lst);
		*i += get_next_space_char_index(argv + *i + 1);
	}
}

static char	**tranfrom_list_to_array(t_list *head)
{
	t_list	*tmp;
	char	**final;
	int		args_count;

	args_count = 0;
	final = (char **)safe_malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	while (head)
	{
		final[args_count++] = head->content;
		tmp = head;
		head = head->next;
	}
	final[args_count] = NULL;
	return (final);
}

char	**get_parsed_command(char *argv)
{
	t_list	*head;
	int		i;

	i = -1;
	head = NULL;
	while (argv[++i] && !not_only_spaces_until_end(argv + i))
	{
		if (!head)
			handle_first(&head, argv, &i);
		if (ft_isspace(argv[i]))
			handle_spaces(&head, argv, &i);
		else if (argv[i] == '\'')
			handle_quote(&head, argv, &i);
	}
	return (tranfrom_list_to_array(head));
}
