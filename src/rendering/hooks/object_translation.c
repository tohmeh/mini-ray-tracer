/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:54:37 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:59:03 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

t_vector	get_translation_delta(t_directions direction, float move_step)
{
	t_vector	delta;

	delta.x = 0;
	delta.y = 0;
	delta.z = 0;
	if (direction == UP)
		delta.z = move_step;
	else if (direction == DOWN)
		delta.z = -move_step;
	else if (direction == LEFT)
		delta.x = -move_step;
	else if (direction == RIGHT)
		delta.x = move_step;
	return (delta);
}

static void	translate_object_by_type(t_object_info *obj, t_vector delta)
{
	if (obj->type == SPHERE)
		((t_sphere *)obj->obj)->center
			= add_vectors(((t_sphere *)obj->obj)->center,
				delta);
	else if (obj->type == CYLINDER)
		((t_cylinder *)obj->obj)->center
			= add_vectors(((t_cylinder *)obj->obj)->center,
				delta);
	else if (obj->type == PLANE)
		((t_plane *)obj->obj)->point = add_vectors(((t_plane *)obj->obj)->point,
				delta);
}

int	translate_object(t_minirt *minirt, t_directions direction)
{
	t_scene		*scene;
	t_vector	delta;
	float		move_step;

	scene = minirt->scene;
	move_step = 0.2f;
	if (!scene->object_hit)
		return (0);
	delta = get_translation_delta(direction, move_step);
	translate_object_by_type(scene->object_hit, delta);
	return (1);
}

void	handle_translation_key(int key, t_minirt *rt)
{
	if (key == KEY_T)
		translate_object(rt, UP);
	else if (key == KEY_G)
		translate_object(rt, DOWN);
	else if (key == KEY_F)
		translate_object(rt, LEFT);
	else if (key == KEY_H)
		translate_object(rt, RIGHT);
}
