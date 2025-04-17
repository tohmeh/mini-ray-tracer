/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:55:00 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 12:59:18 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	set_ambient(t_scene *scene, t_ambient *ambient)
{
	if (scene->ambient)
	{
		perror("Error: Only one ambient light allowed\n");
		return ;
	}
	scene->ambient = ambient;
}

void	set_camera(t_scene *scene, t_camera *camera)
{
	if (scene->camera)
	{
		perror("Error: Only one camera allowed\n");
		return ;
	}
	scene->camera = camera;
}
