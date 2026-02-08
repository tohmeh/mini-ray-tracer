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

int	key_press(int keycode, t_minirt *rt)
{
	if (!rt || !rt->scene)
		return (0);
	handle_exit_key(keycode, rt);
	if (keycode == KEY_W)
		rt->keys.w = 1;
	else if (keycode == KEY_S)
		rt->keys.s = 1;
	else if (keycode == KEY_A)
		rt->keys.a = 1;
	else if (keycode == KEY_D)
		rt->keys.d = 1;
	else if (keycode == KEY_UP)
		rt->keys.up = 1;
	else if (keycode == KEY_DOWN)
		rt->keys.down = 1;
	else if (keycode == KEY_LEFT)
		rt->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		rt->keys.right = 1;
	else
	{
		handle_object_rotation_key(keycode, rt);
		handle_translation_key(keycode, rt);
		rt->keys.needs_render = 1;
	}
	return (0);
}

int	key_release(int keycode, t_minirt *rt)
{
	if (!rt)
		return (0);
	if (keycode == KEY_W)
		rt->keys.w = 0;
	else if (keycode == KEY_S)
		rt->keys.s = 0;
	else if (keycode == KEY_A)
		rt->keys.a = 0;
	else if (keycode == KEY_D)
		rt->keys.d = 0;
	else if (keycode == KEY_UP)
		rt->keys.up = 0;
	else if (keycode == KEY_DOWN)
		rt->keys.down = 0;
	else if (keycode == KEY_LEFT)
		rt->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		rt->keys.right = 0;
	return (0);
}

void	process_movement_keys(t_minirt *rt, t_camera *cam)
{
	float	move_speed;
	float	rotation_speed;

	move_speed = 0.15f;
	rotation_speed = 0.02f;
	if (rt->keys.w)
		move_camera(cam, cam->direction, move_speed);
	if (rt->keys.s)
		move_camera(cam, multiply_vector_by_scalar(cam->direction, -1), move_speed);
	if (rt->keys.a || rt->keys.d)
	{
		t_vector right = compute_right_vector(cam->direction);
		if (rt->keys.a)
			move_camera(cam, multiply_vector_by_scalar(right, -1), move_speed);
		if (rt->keys.d)
			move_camera(cam, right, move_speed);
	}
	if (rt->keys.left)
		rotate_camera_y(cam, rotation_speed);
	if (rt->keys.right)
		rotate_camera_y(cam, -rotation_speed);
	if (rt->keys.up)
		rotate_camera_x(cam, -rotation_speed);
	if (rt->keys.down)
		rotate_camera_x(cam, rotation_speed);
}

int	loop_hook(t_minirt *rt)
{
	int	any_key_pressed;

	if (!rt || !rt->scene || rt->shouldExit)
		return (0);
	any_key_pressed = rt->keys.w || rt->keys.s || rt->keys.a || rt->keys.d
		|| rt->keys.up || rt->keys.down || rt->keys.left || rt->keys.right;
	if (any_key_pressed)
	{
		process_movement_keys(rt, rt->scene->camera);
		update_camera_params(rt->scene->camera);
		rt->keys.needs_render = 1;
	}
	if (rt->keys.needs_render)
	{
		render_scene(*rt->scene, rt->mlx);
		mlx_put_image_to_window(rt->mlx->mlx, rt->mlx->mlx_win,
			rt->mlx->img, CONTROL_PANEL_WIDTH, 0);
		rt->keys.needs_render = 0;
	}
	return (0);
}
