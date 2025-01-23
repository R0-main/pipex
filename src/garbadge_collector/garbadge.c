/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbadge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:55:20 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/23 15:38:24 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbadge.h"
#include "libft.h"
#include <stdlib.h>

static t_list	**get_garbage(void)
{
	static t_list	*head = NULL;

	return (&head);
}

void	add_to_garbadge(void *pointer)
{
	t_list	**garbage_head;
	t_list	*lst;

	garbage_head = get_garbage();
	lst = ft_lstnew(pointer);
	if (!lst)
	{
		free(pointer);
		safe_exit();
	}
	ft_lstadd_front(garbage_head, lst);
}

void	*safe_malloc(size_t size)
{
	void	*memory;
	t_list	*lst;
	t_list	**garbage_head;

	garbage_head = get_garbage();
	memory = malloc(size);
	if (!memory)
		safe_exit();
	lst = ft_lstnew(memory);
	if (!lst)
	{
		free(memory);
		safe_exit();
	}
	ft_lstadd_front(garbage_head, lst);
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
		free(lst);
		lst = tmp;
	}
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
