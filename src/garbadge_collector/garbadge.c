/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbadge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:55:20 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/24 09:30:56 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbadge.h"
#include "libft.h"
#include <stdlib.h>

t_list	**get_garbage(void)
{
	static t_list	*head = NULL;

	return (&head);
}

void	add_to_garbadge(void *pointer)
{
	t_list	**garbage_head;
	t_list	*lst;

	garbage_head = get_garbage();
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
	{
		free(pointer);
		safe_exit();
	}
	lst->content = pointer;
	lst->next = NULL;
	ft_lstadd_front(garbage_head, lst);
}

void	*safe_malloc(size_t size)
{
	void	*memory;
	t_list	*lst;

	memory = malloc(size);
	if (!memory)
		safe_exit();
	add_to_garbadge(memory);
	return (memory);
}

void	free_garbadge(void)
{
	t_list	*tmp;
	t_list	*lst;
	t_list	**garbage_head;

	garbage_head = get_garbage();
	if (!garbage_head || !*garbage_head)
		return ;
	lst = *garbage_head;
	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = tmp;
	}
}

void	reset_garbadge(void)
{
	t_list	**garbage_head;

	garbage_head = get_garbage();
	if (!garbage_head || !*garbage_head)
		return ;
	*garbage_head = NULL;
}

void	safe_free(void *pointer)
{
	t_list	*tmp;
	t_list	*lst;
	t_list	*prev;
	t_list	**garbage_head;

	garbage_head = get_garbage();
	if (!garbage_head || !*garbage_head)
		return ;
	lst = *garbage_head;
	prev = NULL;
	while (lst)
	{
		if (lst->content == pointer)
		{
			if (prev)
				prev->next = lst->next;
			free(lst);
			break ;
		}
		prev = lst;
		lst = lst->next;
	}
	free(pointer);
}

void	safe_exit(void)
{
	free_garbadge();
	exit(1);
}
