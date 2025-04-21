/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_object_detection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:09:46 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 20:38:45 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

object_info	object_detector(int i , int j ,t_scene *scene)
{
	t_ray ray = generate_ray(scene->camera, i, j);
	t_vector intersection_point;
	object_info	obj;
	float closest_t = INFINITY;
	
	t_sphere *sphere = scene->spheres;
	while (sphere)
	{
		float t_sphere = compute_sphere_intersection(ray.D, sphere->center, ray.b, sphere->radius);
		if (t_sphere > 0 && t_sphere < closest_t)
		{
			closest_t = t_sphere;
			obj.intersection_point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D, t_sphere));
			obj.obj = sphere;
			obj.type = SPHERE;
		}
		sphere = sphere->next;
	}
	
	t_plane *plane = scene->planes;
	while (plane)
	{
		float t_plane = compute_plane_intersection(plane->normal, plane->point, ray.D, ray.b);
		if (t_plane > 0 && t_plane < closest_t)
		{
			closest_t = t_plane;
			obj.intersection_point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D, t_plane));
			obj.normal = plane_normal_vector(*plane);
			obj.type = PLANE;
			obj.obj = plane;
		}
		plane = plane->next;
	}
	
	// Process all cylinders in the linked list
	t_cylinder *cylinder = scene->cylinders;
	while (cylinder)
	{
		// Note: convert diameter to radius by dividing by 2
		float t_cylinder = compute_cylinder_intersection(ray, *cylinder);
		if (t_cylinder > 0 && t_cylinder < closest_t)
		{
			closest_t = t_cylinder;
			obj.intersection_point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D, t_cylinder));
			obj.obj = cylinder;
			obj.normal = cylinder_normal_vector(*cylinder, intersection_point);
			obj.type = CYLINDER;
		}
		cylinder = cylinder->next;
	}
	
	return obj;
}