/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:25:09 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 22:12:11 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void win_init(t_minirt *minirt_struct, int total_width)
{
    t_mlx *mlx = malloc(sizeof(t_mlx));
    if (!mlx)
    {
        perror("Failed to allocate memory for mlx");
        exit(EXIT_FAILURE);
    }
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
    {
        perror("Failed to initialize mlx");
        free(mlx);
        exit(EXIT_FAILURE);
    }
    
    mlx->mlx_win = mlx_new_window(mlx->mlx, total_width, HEIGHT, "miniRT");
    if (!mlx->mlx_win)
    {
        perror("Failed to create window");
        free(mlx);
        exit(EXIT_FAILURE);
    }
    
    // Create image with total width to include control panel
    mlx->img = mlx_new_image(mlx->mlx, total_width, HEIGHT);
    if (!mlx->img)
    {
        perror("Failed to create image");
        mlx_destroy_window(mlx->mlx, mlx->mlx_win);
        free(mlx);
        exit(EXIT_FAILURE);
    }
    
    mlx->img_ptr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
    minirt_struct->mlx = mlx;
}