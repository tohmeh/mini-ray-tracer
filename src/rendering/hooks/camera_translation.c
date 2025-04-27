/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:22:45 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 15:34:05 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	move_camera(t_camera *camera, t_vector direction, float distance)
{
	t_vector	movement;

	movement = multiply_vector_by_scalar(direction, distance);
	camera->position = add_vectors(camera->position, movement);
	update_camera_params(camera); // Recompute only when moving

}

t_vector	compute_right_vector(t_vector forward)
{
	t_vector	up;
	t_vector	right;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	right = cross_product(up, forward);
	return (normalize_vector(right));
}

void	handle_movement_key(int key, t_camera *cam, float speed)
{
	t_vector	right;

	if (key == KEY_W)
		move_camera(cam, cam->direction, speed);
	else if (key == KEY_S)
		move_camera(cam, multiply_vector_by_scalar(cam->direction, -1), speed);
	else if (key == KEY_A || key == KEY_D)
	{
		right = compute_right_vector(cam->direction);
		if (key == KEY_A)
			move_camera(cam, multiply_vector_by_scalar(right, -1), speed);
		else
			move_camera(cam, right, speed);
	}
}
