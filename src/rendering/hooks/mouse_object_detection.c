/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_object_detection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:09:46 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 19:09:11 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static void	detect_sphere(t_ray ray, t_scene *scene, t_object_info *obj,
		float *closest_t)
{
	t_sphere	*sphere;
	float		t_sphere;

	sphere = scene->spheres;
	while (sphere)
	{
		t_sphere = compute_sphere_intersection(ray.d, sphere->center, ray.b,
				sphere->radius);
		if (t_sphere > 0 && t_sphere < *closest_t)
		{
			*closest_t = t_sphere;
			obj->intersection_point = add_vectors(ray.b,
					multiply_vector_by_scalar(ray.d, t_sphere));
			obj->obj = sphere;
			obj->type = SPHERE;
		}
		sphere = sphere->next;
	}
}

static void	detect_plane(t_ray ray, t_scene *scene, t_object_info *obj,
		float *closest_t)
{
	t_plane	*plane;
	float	t_plane;

	plane = scene->planes;
	while (plane)
	{
		t_plane = compute_plane_intersection(plane->normal, plane->point, ray.d,
				ray.b);
		if (t_plane > 0 && t_plane < *closest_t)
		{
			*closest_t = t_plane;
			obj->intersection_point = add_vectors(ray.b,
					multiply_vector_by_scalar(ray.d, t_plane));
			obj->normal = plane_normal_vector(*plane);
			obj->obj = plane;
			obj->type = PLANE;
		}
		plane = plane->next;
	}
}

static void	detect_cylinder(t_ray ray, t_scene *scene, t_object_info *obj,
		float *closest_t)
{
	t_cylinder	*cylinder;
	float		t_cylinder;

	cylinder = scene->cylinders;
	while (cylinder)
	{
		t_cylinder = compute_cylinder_intersection(ray, *cylinder);
		if (t_cylinder > 0 && t_cylinder < *closest_t)
		{
			*closest_t = t_cylinder;
			obj->intersection_point = add_vectors(ray.b,
					multiply_vector_by_scalar(ray.d, t_cylinder));
			obj->normal = cylinder_normal_vector(*cylinder,
					obj->intersection_point);
			obj->obj = cylinder;
			obj->type = CYLINDER;
		}
		cylinder = cylinder->next;
	}
}

t_object_info	object_detector(int i, int j, t_scene *scene)
{
	t_ray			ray;
	t_object_info	obj;
	float			closest_t;

	ray = generate_ray(scene->camera, i, j);
	closest_t = INFINITY;
	detect_sphere(ray, scene, &obj, &closest_t);
	detect_plane(ray, scene, &obj, &closest_t);
	detect_cylinder(ray, scene, &obj, &closest_t);
	return (obj);
}
