/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 14:37:35 by jsaarine          #+#    #+#             */
/*   Updated: 2022/12/14 17:53:43 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

typedef union u_tuple
{
	struct
	{
		double	x;
		double	y;
		double	z;
		double	w;
	} s_xyzw;
	struct
	{
		double	r;
		double	g;
		double	b;
	} s_rgb;
	double		a[4];
}				t_tuple;

typedef t_tuple	t_vector;
typedef t_tuple	t_point;
typedef t_tuple	t_color;

t_vector		tuple_new(double x, double y, double z, double w);
void			tuple_print(t_tuple t);
int				nearly_equal(double a, double b);
t_tuple			tuple_add(t_tuple u, t_tuple v);
t_tuple			tuple_sub(t_tuple u, t_tuple v);
t_point			point_new(double x, double y, double z);
t_vector		vector_new(double x, double y, double z);
t_tuple			tuple_neg(t_tuple u);
t_tuple			tuple_scalar_mult(t_tuple u, double x);
t_tuple			tuple_scalar_div(t_tuple u, double x);
double			tuple_mag(t_tuple u);
t_tuple			tuple_unit(t_tuple u);
double			vector_dot(t_tuple u, t_tuple v);
t_vector		vector_cross(t_vector u, t_vector v);
t_color			color_new(double r, double g, double b);
unsigned int	color_to_int(t_color color);
t_color			int_to_color(unsigned int rgba);
unsigned int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b);
t_color			color_multiply(t_color a, t_color b);
t_vector		vector_reflect(t_vector v, t_vector n);

#endif
