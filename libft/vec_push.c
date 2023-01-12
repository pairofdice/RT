/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:03:31 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/12 20:05:52 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

//	takes in a vector and a pointer to an element to be pushed to the
//	end of the vector.

// int	vec_push(t_vec *vec, void *elem)
// {
// 	size_t	new_len;
// 	size_t	new_alloc_size;
// 	void	*new_memory;

// 	if (!vec || !elem)
// 		return (-1);
// 	new_len = vec->len + 1;
// 	if(new_len > vec->alloc_size)
// 	{
// 		new_alloc_size = (vec->alloc_size * 2);
// 		new_memory = malloc(new_alloc_size * vec->elem_size);
// 		if (!new_memory)
// 			return (-1);
// 		new_memory = ft_memcpy(
						// new_memory, 
						// vec->memory, 
						// vec->len * vec->elem_size);
// 		free(vec->memory);
// 		vec->memory = new_memory;
// 		vec->alloc_size = new_alloc_size;
// 	}
// 	vec->memory = ft_memcpy(
	// vec->memory + vec->len * vec->elem_size, 
	// elem, 
	// vec->elem_size);
// 	vec->len = new_len;
// 	return (1);
// }

int	vec_push(t_vec *vec, void *elem)
{
	if (!vec || !elem)
		return (-1);
	if ((vec->len * vec->elem_size) == vec->alloc_size)
		if (vec_resize(vec, vec->len * 2) == -1)
			return (-1);
	ft_memcpy(&vec->memory[vec->len * vec->elem_size], elem, vec->elem_size);
	vec->len++;
	return (1);
}
