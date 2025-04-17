/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:52:39 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/03/29 01:14:55 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void put_pixel(t_mlx *mlx, int x, int y, int color) {
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = mlx->img_ptr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
