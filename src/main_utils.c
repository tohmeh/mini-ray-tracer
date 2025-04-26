/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:04:29 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:26:51 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	program_init(t_minirt *minirt, char *filename)
{
	t_scene	*scene;
	int		total_width;

	scene = malloc(sizeof(t_scene));
	total_width = WIDTH + CONTROL_PANEL_WIDTH;
	win_init(minirt, total_width);
	*scene = parse_elements(filename);
	if (!scene->camera || !scene->ambient)
	{
		printf("Invalid scene setup.\n");
		return (0);
	}
	scene->object_hit = NULL;
	minirt->scene = scene;
	render_scene(*minirt->scene, minirt->mlx);
	return (1);
}

void	setup_hooks(t_minirt minirt)
{
	mlx_mouse_hook(minirt.mlx->mlx_win, mouse_handler, &minirt);
	mlx_key_hook(minirt.mlx->mlx_win, key_hook, &minirt);
	mlx_hook(minirt.mlx->mlx_win, 17, 0, close_window, &minirt);
}
