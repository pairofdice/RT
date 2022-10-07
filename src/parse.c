/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:09:56 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 20:11:47 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static int	sf_is_valid_float(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0' && ft_isdigit(*str))
	{
		str++;
	}
	if (*str != '.')
		return (0);
	str++;
	if (!ft_isdigit(*str))
		return (0);
	str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atof(char *str, double *result)
{
	int		fraction;
	size_t	fraction_len;
	double	neg;

	neg = 1.0;
	*result = 0.0;
	if (!str || !sf_is_valid_float(str))
		return (0);
	if (*str == '-')
		neg = -1.0;
	*result = ft_abs(ft_atoi(str));
	str = ft_strchr(str, '.');
	str++;
	fraction = ft_abs(ft_atoi(str));
	fraction_len = ft_strlen(str);
	*result += (fraction / pow(10, fraction_len));
	*result *= neg;
	return (1);
}

static int	sf_check_triple_length(char **strs)
{
	int	c;

	c = 0;
	while (strs[c] != 0)
		c++;
	if (c != 3)
		return (0);
	return (1);
}

t_point	read_triple(char **strs)
{
	t_point	p;

	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;
	if (!sf_check_triple_length(++strs))
		return (p);
	ft_atof(strs[0], &p.x);
	ft_atof(strs[1], &p.y);
	ft_atof(strs[2], &p.z);
	return (p);
}

void	check_type(char **str, t_context *ctx)
{
	ctx->parse_state = PROCESSING;
	++str;
	if (*str)
	{
		if (ft_strncmp(*str, "light", 5) == 0)
			ctx->obj.type = LIGHT;
		else if (ft_strncmp(*str, "cone", 4) == 0)
			ctx->obj.type = CONE;
		else if (ft_strncmp(*str, "plane", 5) == 0)
			ctx->obj.type = PLANE;
		else if (ft_strncmp(*str, "cylinder", 8) == 0)
			ctx->obj.type = CYLINDER;
		else if (ft_strncmp(*str, "sphere", 6) == 0)
			ctx->obj.type = SPHERE;
		else if (ft_strncmp(*str, "camera", 6) == 0)
			ctx->obj.type = CAMERA;
	}
}
