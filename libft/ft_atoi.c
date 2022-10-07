/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 20:41:20 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/07 18:17:41 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	pos;
	int	result;

	result = 0;
	pos = 1;
	while (*str && ft_iswhitespace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			pos *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * pos);
}
