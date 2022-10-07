/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:37:24 by jsaarine          #+#    #+#             */
/*   Updated: 2022/10/03 14:27:56 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_color;
typedef t_vec3	t_point;

typedef struct s_ray
{
	t_point	orig;
	t_vec3	dir;
}	t_ray;

typedef struct s_abc
{
	double	a;
	double	b;
	double	c;
}	t_abc;

unsigned int	rgb_to_int(unsigned int r,
					unsigned int g,
					unsigned int b);
t_vec3			vec3_add(t_vec3 i,
					t_vec3 j);
double			vec3_mag(t_vec3 i);
t_vec3			vec3_scalar_mult(t_vec3 u,
					double x);
t_vec3			vec3_cross(t_vec3 u,
					t_vec3 v);
t_vec3			vec3_unit(t_vec3 u);
t_vec3			vec3_sub(t_vec3 u,
					t_vec3 v);
t_vec3			vec3_neg(t_vec3 u);
double			vec3_dot(t_vec3 u,
					t_vec3 v);
double			vec3_sqr(t_vec3 u);
t_vec3			vec3_ray_at(t_ray u,
					double x);
t_vec3			vec3_reflect(t_vec3 incoming,
					t_ray normal);
double			quadratic(t_abc abc,
					double b2_4ac);
double			calc_b2_4ac(t_abc abc);

#endif
