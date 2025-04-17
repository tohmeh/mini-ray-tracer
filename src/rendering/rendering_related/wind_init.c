/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:25:09 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/05 16:50:41 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	win_init(t_minirt *minirt_struct)
{
	t_mlx *mlx = malloc(sizeof(t_mlx));
	if (!mlx)
	{
		perror("Failed to allocate memory for mlx");
		exit(EXIT_FAILURE);
	}
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img_ptr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);

	mlx_hook(mlx->mlx_win, 17, 0, close_window, minirt_struct);
	mlx_key_hook(mlx->mlx_win, key_hook, minirt_struct);

	minirt_struct->mlx = mlx;
}
