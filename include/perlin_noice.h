/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noice.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:17:33 by jjuntune          #+#    #+#             */
/*   Updated: 2022/12/20 15:06:15 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_NOICE_H
# define PERLIN_NOICE_H

# include "rt.h"
# include "vector.h"

typedef struct s_perlin
{
	float	x;
	float	y;
	float	z;
	int		is_data_writen;
	int		p[512];
	int		x_i;
	int		y_i;
	int		z_i;
	double	u;
	double	v;
	double	w;
	int		a;
	int		aa;
	int		ab;
	int		b;
	int		ba;
	int		bb;
}				t_perlin;

double	perlin_noice(t_tuple point, t_perlin *perlin);
void		load_perlin_data(t_perlin *perlin);
double	grad(int hash, double x, double y, double z);
double	lerp(double t, double a, double b);
double	fade(double t);
#endif