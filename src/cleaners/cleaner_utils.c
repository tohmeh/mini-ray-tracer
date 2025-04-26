/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:31:40 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 19:31:55 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_spheres(t_sphere *sphere)
{
	t_sphere	*tmp;

	while (sphere)
	{
		tmp = sphere;
		sphere = sphere->next;
		free(tmp);
	}
}

void	free_planes(t_plane *plane)
{
	t_plane	*tmp;

	while (plane)
	{
		tmp = plane;
		plane = plane->next;
		free(tmp);
	}
}

void	free_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*tmp;

	while (cylinder)
	{
		tmp = cylinder;
		cylinder = cylinder->next;
		free(tmp);
	}
}

void	free_lights(t_light *light)
{
	t_light	*tmp;

	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->lights)
		free_lights(scene->lights);
	if (scene->spheres)
		free_spheres(scene->spheres);
	if (scene->planes)
		free_planes(scene->planes);
	if (scene->cylinders)
		free_cylinders(scene->cylinders);
	if (scene->object_hit)
		free(scene->object_hit);
}
