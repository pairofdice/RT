/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/11/07 17:12:52 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../libft/libft.h"
# include "matrix.h"
# include "tuple.h"
# include "vector.h"
# include <stdlib.h>

//typedef struct s_object
//{
//	t_vec3			loc;
//	t_vec3			coi;
//	t_vec3			up;
//	t_vec3			rot;
//	double			size;
//	double			brightness;
//	int				type;
//	size_t			id;
//	union u_tuple	color;
//	t_matrix		transform;
//
//}					t_object;

typedef struct s_object
{
	t_point			loc;
	t_point			coi;
	t_vector		up;
	t_vector		rot;
	double			size;
	double			brightness;
	int				type;
	size_t			id;
	t_matrix		transform;
	t_tuple			color;
}					t_object;

typedef struct s_abc
{
	double			a;
	double			b;
	double			c;
}					t_abc;

typedef struct s_abcd
{
	double			a;
	double			b;
	double			c;
	double			d;
}					t_abcd;

typedef struct s_intersections
{
	t_vec			vec;
}					t_intersections;

typedef struct s_intersection
{
	double			t;
	t_object		*object;
}					t_intersection;

typedef struct s_ray_m
{
	t_point			orig;
	t_vector		dir;
	t_intersections	xs;
}					t_ray_m;

t_object			sphere_new(void);
double				calc_discriminant(double a, double b, double c);
t_ray_m				ray_new(t_point origin, t_vector dir);
// t_ray_m			ray_new_malloc(t_point origin, t_vector dir);
t_ray_m				ray_new_no_malloc(t_point origin, t_vector dir);
void				ray_free(t_ray_m *ray);

int					phere_intersect(t_ray_m *ray, t_object *s);
t_ray_m				ray_transform(t_ray_m *source, t_matrix *transform);
void				intersection_record(t_ray_m *ray,
						double t1,
						double t2,
						t_object *s);
int					intersect_sphere(t_ray_m *inc_ray, t_object *s);
t_intersection		intersection_new(double time, t_object *o);
void				set_transform(t_object *obj, t_matrix *transform);

#endif