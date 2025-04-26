/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:00:00 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:06:00 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

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
	t_vector	t;
	float		t1;
	float		t2;

	t.x = dot_product(rd_proj, rd_proj);
	t.y = 2 * dot_product(rd_proj, oc_proj);
	t.z = dot_product(oc_proj, oc_proj) - (radius * radius);
	if (!solve_quadratic(t, &t1, &t2))
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
