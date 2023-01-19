/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:03:52 by jsaarine          #+#    #+#             */
/*   Updated: 2023/01/19 16:27:40 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	appends vector src to dst
*/
int	vec_append(t_vec *dst, t_vec *src)
{
	size_t			space_needed;
	unsigned char	*memory;

	memory = (unsigned char *)dst->memory;
	if (!dst || !src || !src->memory)
		return (-1);
	if (!dst->memory)
		vec_new(dst, 1, 1);
	space_needed = dst->len * dst->elem_size + src->len * src->elem_size;
	if (dst->alloc_size < space_needed)
	{
		if (vec_resize(dst, space_needed * 2) == -1)
			return (-1);
	}
	ft_memcpy(
		&memory[dst->len * dst->elem_size],
		src->memory,
		src->len * 1);
	dst->len += src->len;
	vec_free(src);
	return (1);
}
