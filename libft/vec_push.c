/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:03:31 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/23 13:49:48 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	takes in a vector and a pointer to an element to be pushed to the
//	end of the vector.

int	vec_push(t_vec *vec, void *elem)
{
	if (!vec || !elem || !vec->memory)
		return (-1);
	if ((vec->len * vec->elem_size) == vec->alloc_size)
		if (vec_resize(vec, vec->len * 2) == -1)
			return (-1);
	ft_memcpy(&vec->memory[vec->len * vec->elem_size], elem, vec->elem_size);
	vec->len++;
	return (1);
}
