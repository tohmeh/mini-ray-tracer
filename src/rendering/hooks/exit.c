/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:01 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 16:04:41 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	handle_exit_key(int key, t_minirt *rt)
{
	if (key == KEY_ESC)
		close_window(rt);
}

int	close_window(t_minirt *minirt_struct)
{
	mlx_destroy_window(minirt_struct->mlx->mlx, minirt_struct->mlx->mlx_win);
	exit(0);
	return (0);
}
