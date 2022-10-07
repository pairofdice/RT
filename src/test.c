// #define NDEBUG // disable asserts
# include <assert.h>

typedef struct s_xyzw
{
	double	x;
	double	y;
	double	z;
	double	w;
} t_xyzw;

typedef t_xyzw t_vector;
typedef t_xyzw t_point;

t_point		new_point(double x, double y, double z)
{
	t_point new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = 1.0;
	return (new);
}

t_vector	new_vector(double x, double y, double z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = 0.0;
	return (new);
}

int	main(void)
{
	t_xyzw p = new_point(4.3, -4.2, 3.1);
	assert(p.x == 4.3);
	assert(p.y == -4.2);
	assert(p.z == 3.1);
	assert(p.w == 1.0);
	t_xyzw v = new_vector(4.3, -4.2, 3.1);
	assert(v.x == 4.3);
	assert(v.y == -4.2);
	assert(v.z == 3.1);
	assert(v.w == 0.0);

}
