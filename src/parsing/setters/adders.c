/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:31:24 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 12:59:37 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	add_light(t_scene *scene, t_light *light)
{
	t_light	*current;

	if (!scene->lights)
	{
		scene->lights = light;
		return ;
	}
	current = scene->lights;
	while (current->next)
		current = current->next;
	current->next = light;
}

void	add_sphere(t_scene *scene, t_sphere *sphere)
{
	t_sphere	*current;

	if (!scene->spheres)
	{
		scene->spheres = sphere;
		return ;
	}
	current = scene->spheres;
	while (current->next)
		current = current->next;
	current->next = sphere;
}

void	add_plane(t_scene *scene, t_plane *plane)
{
	t_plane	*current;

	if (!scene->planes)
	{
		scene->planes = plane;
		return ;
	}
	current = scene->planes;
	while (current->next)
		current = current->next;
	current->next = plane;
}

void	add_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	t_cylinder	*current;

	if (!scene->cylinders)
	{
		scene->cylinders = cylinder;
		return ;
	}
	current = scene->cylinders;
	while (current->next)
		current = current->next;
	current->next = cylinder;
}
