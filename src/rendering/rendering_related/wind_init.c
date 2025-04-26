/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:25:09 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 17:45:11 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static t_mlx	*allocate_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
	{
		perror("Failed to allocate memory for mlx");
		exit(EXIT_FAILURE);
	}
	return (mlx);
}

static void	initialize_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		perror("Failed to initialize mlx");
		free(mlx);
		exit(EXIT_FAILURE);
	}
}

static void	create_window(t_mlx *mlx, int width, int height)
{
	mlx->mlx_win = mlx_new_window(mlx->mlx, width, height, "miniRT");
	if (!mlx->mlx_win)
	{
		perror("Failed to create window");
		free(mlx);
		exit(EXIT_FAILURE);
	}
}

static void	create_image(t_mlx *mlx, int width, int height)
{
	mlx->img = mlx_new_image(mlx->mlx, width, height);
	if (!mlx->img)
	{
		perror("Failed to create image");
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		free(mlx);
		exit(EXIT_FAILURE);
	}
}

void	win_init(t_minirt *minirt_struct, int total_width)
{
	t_mlx	*mlx;

	mlx = allocate_mlx();
	initialize_mlx(mlx);
	create_window(mlx, total_width, HEIGHT);
	create_image(mlx, total_width, HEIGHT);
	mlx->img_ptr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len,
			&mlx->endian);
	minirt_struct->mlx = mlx;
}
