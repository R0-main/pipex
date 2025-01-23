/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbadge.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:18 by rguigneb          #+#    #+#             */
/*   Updated: 2025/01/23 15:19:27 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBADGE_H
# define GARBADGE_H

# include <stddef.h>
/******************************************************************************/

void	*safe_malloc(size_t size);
void	safe_exit(void);
void	free_garbadge(void);
void	safe_free(void *pointer);
void	add_to_garbadge(void *pointer);

#endif
