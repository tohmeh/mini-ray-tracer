/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakhoury <gakhoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:18:16 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/21 21:34:48 by gakhoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static void	check_sphere_intersection(t_ray ray, t_sphere *sphere,
		float *closest_t, t_hit_info *hit)
{
	float	t_sphere;

	while (sphere)
	{
		t_sphere = compute_sphere_intersection(ray.D, sphere->center, ray.b,
				sphere->radius);
		if (t_sphere > 0 && t_sphere < *closest_t)
		{
			*closest_t = t_sphere;
			hit->point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D,
						t_sphere));
			hit->normal = sphere_normal_vector(*sphere, hit->point);
			hit->color = sphere->color;
		}
		sphere = sphere->next;
	}
}

/* Calculate intersection with a plane and update closest hit if needed */
static void	check_plane_intersection(t_ray ray, t_plane *plane,
		float *closest_t, t_hit_info *hit)
{
	float	t_plane;

	while (plane)
	{
		t_plane = compute_plane_intersection(plane->normal, plane->point, ray.D,
				ray.b);
		if (t_plane > 0 && t_plane < *closest_t)
		{
			*closest_t = t_plane;
			hit->point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D,
						t_plane));
			hit->normal = plane_normal_vector(*plane);
			hit->color = plane->color;
		}
		plane = plane->next;
	}
}

/* Calculate intersection with a cylinder and update closest hit if needed */
static void	check_cylinder_intersection(t_ray ray, t_cylinder *cylinder,
		float *closest_t, t_hit_info *hit)
{
	float	t_cylinder;

	while (cylinder)
	{
		t_cylinder = compute_cylinder_intersection(ray, *cylinder);
		if (t_cylinder > 0 && t_cylinder < *closest_t)
		{
			*closest_t = t_cylinder;
			hit->point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D,
						t_cylinder));
			hit->normal = cylinder_normal_vector(*cylinder, hit->point);
			hit->color = cylinder->color;
		}
		cylinder = cylinder->next;
	}
}

/* Find closest intersection with any object in the scene */
int	find_closest_intersection(t_ray ray, t_scene scene,
		float *closest_t, t_hit_info *hit)
{
	*closest_t = INFINITY;
	check_sphere_intersection(ray, scene.spheres, closest_t, hit);
	check_plane_intersection(ray, scene.planes, closest_t, hit);
	check_cylinder_intersection(ray, scene.cylinders, closest_t, hit);
	return (*closest_t < INFINITY);
}
