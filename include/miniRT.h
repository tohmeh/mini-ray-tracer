/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:10:37 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/19 17:24:28 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "rendering.h"
#include "parsing.h"
#include <stdio.h>
#include <math.h>
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include <fcntl.h>
#include "../LIBFT/include/LIBFT.h"
typedef struct s_minirt{
	t_mlx *mlx;
	t_scene *scene;
}	t_minirt;

#endif