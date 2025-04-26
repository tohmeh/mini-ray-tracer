/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:13:56 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:56:30 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static void	put_camera_controls_utils(t_mlx *mlx, int *y_pos, int color)
{
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20,
		*y_pos, color, "Camera Rotation:");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "UP - Look up");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "DOWN - Look down");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "LEFT - Look left");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "RIGHT - Look right");
	*y_pos += 30;
}

static void	put_camera_controls(t_mlx *mlx, int *y_pos, int color)
{
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20,
		*y_pos, color, "Camera Movement:");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "W - Move forward");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "S - Move backward");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "A - Move left");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "d - Move right");
	*y_pos += 30;
}

static void	put_object_controls(t_mlx *mlx, int *y_pos, int color)
{
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20,
		*y_pos, color, "Object Selection:");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "Left Click - Select");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "Scroll - Resize");
	*y_pos += 30;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20,
		*y_pos, color, "Object Translation:");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "T - Move forward");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "G - Move backward");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "F - Move left");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "H - Move right");
	*y_pos += 30;
}

static void	put_rotation_exit(t_mlx *mlx, int *y_pos, int color)
{
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20,
		*y_pos, color, "Object Rotation:");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "J - Rotate X axis");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "K - Rotate Y axis");
	*y_pos += 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 30,
		*y_pos, color, "L - Rotate Z axis");
	*y_pos += 30;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20,
		*y_pos, color, "ESC - Exit");
}

void	draw_instruction_panel(t_mlx *mlx)
{
	int	y_pos;
	int	text_color;

	text_color = 0xFFFFFF;
	y_pos = 20;
	mlx_string_put(mlx->mlx, mlx->mlx_win, 20, y_pos, text_color, "CONTROLS:");
	y_pos += 30;
	put_camera_controls(mlx, &y_pos, text_color);
	put_camera_controls_utils(mlx, &y_pos, text_color);
	put_object_controls(mlx, &y_pos, text_color);
	put_rotation_exit(mlx, &y_pos, text_color);
}
