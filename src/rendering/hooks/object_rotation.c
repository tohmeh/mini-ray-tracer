/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:35:53 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 16:21:53 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector	rotate_vector(t_vector v, float angle, AXIS axis)
{
	t_vector	result;

	if (axis == X)
	{
		result.x = v.x;
		result.y = v.y * cos(angle) - v.z * sin(angle);
		result.z = v.y * sin(angle) + v.z * cos(angle);
	}
	else if (axis == Y)
	{
		result.x = v.x * cos(angle) + v.z * sin(angle);
		result.y = v.y;
		result.z = -v.x * sin(angle) + v.z * cos(angle);
	}
	else if (axis == Z)
	{
		result.x = v.x * cos(angle) - v.y * sin(angle);
		result.y = v.x * sin(angle) + v.y * cos(angle);
		result.z = v.z;
	}
	return (result);
}

int	rotate_object(t_minirt *minirt, AXIS axe)
{
	t_scene		*scene;
	t_cylinder	*cyl;
	t_plane		*pln;
	float		angle;

	scene = minirt->scene;
	if (!scene->object_hit)
		return (0);
	angle = 0.1f;
	if (scene->object_hit->type == CYLINDER)
	{
		cyl = (t_cylinder *)scene->object_hit->obj;
		cyl->axis = rotate_vector(cyl->axis, angle, axe);
		cyl->axis = normalize_vector(cyl->axis);
	}
	else if (scene->object_hit->type == PLANE)
	{
		pln = (t_plane *)scene->object_hit->obj;
		pln->normal = rotate_vector(pln->normal, angle, axe);
		pln->normal = normalize_vector(pln->normal);
	}
	return (1);
}

void	handle_object_rotation_key(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_J)
		rotate_object(minirt, X);
	else if (keycode == KEY_K)
		rotate_object(minirt, Y);
	else if (keycode == KEY_L)
		rotate_object(minirt, Z);
}
