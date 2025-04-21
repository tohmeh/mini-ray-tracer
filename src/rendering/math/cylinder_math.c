/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakhoury <gakhoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:00:00 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 20:43:46 by gakhoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

float	calculate_A_cylinder(t_vector D)
{
	return ((D.x * D.x) + (D.z * D.z));
}

float	calculate_B_cylinder(t_vector D, t_vector cylinder_center,
		t_vector ray_origin)
{
	return (2 * ((D.x * (ray_origin.x - cylinder_center.x)) + (D.z
				* (ray_origin.z - cylinder_center.z))));
}

float	calculate_C_cylinder(t_vector cylinder_center, t_vector ray_origin,
		float radius)
{
	float	dx;
	float	dz;

	dx = ray_origin.x - cylinder_center.x;
	dz = ray_origin.z - cylinder_center.z;
	return ((dx * dx) + (dz * dz) - (radius * radius));
}
static t_vector	get_cylinder_projection(t_vector v, t_vector axis)
{
	return (subtract_vectors(v, multiply_vector_by_scalar(axis, dot_product(v,
					axis))));
}

static int	solve_quadratic(float A, float B, float C, float *t1, float *t2)
{
	float	discriminant;
	float	sqrt_disc;

	discriminant = B * B - 4 * A * C;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrtf(discriminant);
	*t1 = (-B - sqrt_disc) / (2 * A);
	*t2 = (-B + sqrt_disc) / (2 * A);
	return (1);
}

static float	select_valid_t(float t1, float t2)
{
	if (t1 > 0.0001f)
		return (t1);
	else if (t2 > 0.0001f)
		return (t2);
	return (-1.0f);
}

static int	is_within_cylinder_height(t_vector hit, t_cylinder cyl,
		t_vector axis)
{
	float	dist_along_axis;

	dist_along_axis = dot_product(subtract_vectors(hit, cyl.center), axis);
	return (dist_along_axis >= 0.0f && dist_along_axis <= cyl.height);
}

float	solve_cylinder_quadratic(t_vector rd_proj, t_vector oc_proj,
		float radius)
{
	float	a;
	float	b;
	float	c;
	float	t1;
	float	t2;

	a = dot_product(rd_proj, rd_proj);
	b = 2 * dot_product(rd_proj, oc_proj);
	c = dot_product(oc_proj, oc_proj) - (radius * radius);
	if (!solve_quadratic(a, b, c, &t1, &t2))
		return (-1.0f);
	return (select_valid_t(t1, t2));
}

float	compute_cylinder_intersection(t_ray ray, t_cylinder cyl)
{
	t_vector	ca;
	t_vector	oc;
	float		radius;
	float		t;

	ca = normalize_vector(cyl.axis);
	oc = subtract_vectors(ray.b, cyl.center);
	radius = cyl.diameter * 0.5f;
	t = solve_cylinder_quadratic(get_cylinder_projection(ray.D, ca),
			get_cylinder_projection(oc, ca), radius);
	if (t < 0)
		return (-1.0f);
	if (!is_within_cylinder_height(add_vectors(ray.b,
				multiply_vector_by_scalar(ray.D, t)), cyl, ca))
		return (-1.0f);
	return (t);
}
