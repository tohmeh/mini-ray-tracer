/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:25:14 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/06/24 18:41:05 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	key_hook(int keycode, t_minirt *rt)
{
	float		move_speed;
	float		rotation_speed;
	t_camera	*cam;

	move_speed = 0.5f;
	rotation_speed = 0.05f;
	if (!rt || !rt->scene)
	{
		printf("Error: miniRT struct or scene not initialized\n");
		return (0);
	}
	cam = rt->scene->camera;
	handle_exit_key(keycode, rt);
	handle_movement_key(keycode, cam, move_speed);
	handle_camera_rotation_key(keycode, cam, rotation_speed);
	handle_object_rotation_key(keycode, rt);
	handle_translation_key(keycode, rt);
	render_scene(*rt->scene, rt->mlx);
	if (!rt->shouldExit)
	{
		mlx_put_image_to_window(rt->mlx->mlx, rt->mlx->mlx_win, rt->mlx->img,
			CONTROL_PANEL_WIDTH, 0);
		return (0);		
	}
	return (0);
}
