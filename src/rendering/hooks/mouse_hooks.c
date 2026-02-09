/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:25:43 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 16:26:35 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	mouse_handler(int button, int x, int y, void *param)
{
	t_minirt	*minirt;
	t_scene		*scene;
	float		delta;

	minirt = (t_minirt *)param;
	scene = minirt->scene;
	if (button == 1)
		handle_object_detection(x, y, scene);
	else if (button == 4 || button == 5)
	{
		if (button == 4)
			delta = 0.1f;
		else
			delta = -0.1;
		resize_object(scene, delta);
		render_scene(*scene, minirt->mlx);
		mlx_put_image_to_window(minirt->mlx->mlx, minirt->mlx->mlx_win,
			minirt->mlx->img, 0, 0);
	}
	return (0);
}
