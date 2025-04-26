/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:18:15 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:59:03 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	handle_object_detection(int x, int y, t_scene *scene)
{
	t_object_info	hit;

	hit = object_detector(x, y, scene);
	if (scene->object_hit)
		free(scene->object_hit);
	scene->object_hit = malloc(sizeof(t_object_info));
	scene->object_hit->intersection_point = hit.intersection_point;
	scene->object_hit->normal = hit.normal;
	scene->object_hit->obj = hit.obj;
	scene->object_hit->type = hit.type;
}

static void	resize_sphere(t_sphere *sphere, float delta)
{
	sphere->radius += delta;
	if (sphere->radius < 0.1f)
		sphere->radius = 0.1f;
}

static void	resize_cylinder(t_cylinder *cylinder, float delta)
{
	cylinder->diameter += delta;
	cylinder->height += delta;
	if (cylinder->diameter < 0.1f)
		cylinder->diameter = 0.1f;
	if (cylinder->height < 0.1f)
		cylinder->height = 0.1f;
}

void	resize_object(t_scene *scene, float delta)
{
	if (!scene->object_hit)
		return ;
	if (scene->object_hit->type == SPHERE)
		resize_sphere((t_sphere *)scene->object_hit->obj, delta);
	else if (scene->object_hit->type == CYLINDER)
		resize_cylinder((t_cylinder *)scene->object_hit->obj, delta);
}
