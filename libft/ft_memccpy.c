/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:40:35 by jjuntune          #+#    #+#             */
/*   Updated: 2023/01/12 20:03:20 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*uc;
	unsigned char	*dest;

	uc = (unsigned char *)s;
	dest = (unsigned char *)d;
	i = 0;
	while (i < n)
	{
		dest[i] = uc[i];
		if (uc[i] == (unsigned char)c)
			return ((void *)dest);
		i++;
	}
	return (NULL);
}
