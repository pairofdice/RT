/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:49:20 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 20:13:14 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"

double	calc_b2_4ac(t_abc abc)
{
	return (abc.b * abc.b - 4 * abc.a * abc.c);
}

double	quadratic(t_abc abc, double b2_4ac)
{
	double	result_m;
	double	result_p;
	double	denominator;

	if (b2_4ac < 0)
		return (INFINITY);
	denominator = -abc.b - sqrt(b2_4ac);
	result_m = denominator / (2 * abc.a);
	denominator = -abc.b + sqrt(b2_4ac);
	result_p = denominator / (2 * abc.a);
	if (result_p < result_m && result_p >= 0.0)
		return (result_p);
	if (result_m >= 0.0)
		return (result_m);
	return (INFINITY);
}
