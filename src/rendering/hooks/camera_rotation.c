/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:33:35 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 15:35:11 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	rotate_camera_y(t_camera *camera, float angle)
{
	float	cos_angle;
	float	sin_angle;
	float	original_x;
	float	original_z;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	original_x = camera->direction.x;
	original_z = camera->direction.z;
	camera->direction.x = original_x * cos_angle - original_z * sin_angle;
	camera->direction.z = original_x * sin_angle + original_z * cos_angle;
	camera->direction = normalize_vector(camera->direction);
}

void	rotate_camera_x(t_camera *camera, float angle)
{
	float	cos_angle;
	float	sin_angle;
	float	y;
	float	z;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	y = camera->direction.y;
	z = camera->direction.z;
	camera->direction.y = y * cos_angle - z * sin_angle;
	camera->direction.z = y * sin_angle + z * cos_angle;
	if (camera->direction.y > 0.95)
		camera->direction.y = 0.95;
	if (camera->direction.y < -0.95)
		camera->direction.y = -0.95;
	camera->direction = normalize_vector(camera->direction);
}

void	handle_camera_rotation_key(int key, t_camera *cam, float speed)
{
	if (key == KEY_LEFT)
		rotate_camera_y(cam, speed);
	else if (key == KEY_RIGHT)
		rotate_camera_y(cam, -speed);
	else if (key == KEY_UP)
		rotate_camera_x(cam, -speed);
	else if (key == KEY_DOWN)
		rotate_camera_x(cam, speed);
}
