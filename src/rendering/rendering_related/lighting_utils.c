/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:49:07 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/26 17:54:54 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	is_sphere_in_shadow(t_ray shadow_ray, float light_distance, t_scene scene)
{
	float		t;
	t_sphere	*sphere;

	sphere = scene.spheres;
	while (sphere)
	{
		t = compute_sphere_intersection(shadow_ray.d, sphere->center,
				shadow_ray.b, sphere->radius);
		if (t > 0 && t < light_distance)
			return (1);
		sphere = sphere->next;
	}
	return (0);
}

int	is_plane_in_shadow(t_ray shadow_ray, float light_distance, t_scene scene)
{
	float	t;
	t_plane	*plane;

	plane = scene.planes;
	while (plane)
	{
		t = compute_plane_intersection(plane->normal, plane->point,
				shadow_ray.d, shadow_ray.b);
		if (t > 0 && t < light_distance)
			return (1);
		plane = plane->next;
	}
	return (0);
}

int	is_cylinder_in_shadow(t_ray shadow_ray, float light_distance, t_scene scene)
{
	float		t;
	t_cylinder	*cylinder;

	cylinder = scene.cylinders;
	while (cylinder)
	{
		t = compute_cylinder_intersection(shadow_ray, *cylinder);
		if (t > 0 && t < light_distance)
			return (1);
		cylinder = cylinder->next;
	}
	return (0);
}

t_ray	create_shadow_ray(t_vector intersection_point, t_vector light_dir)
{
	t_ray	shadow_ray;

	shadow_ray.b = add_vectors(intersection_point,
			multiply_vector_by_scalar(light_dir, 0.001));
	shadow_ray.d = light_dir;
	return (shadow_ray);
}
