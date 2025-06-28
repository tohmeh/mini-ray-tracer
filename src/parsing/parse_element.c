/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:16:16 by gakhoury          #+#    #+#             */
/*   Updated: 2025/06/28 15:54:24 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static t_scene	init_scene(void)
{
	t_scene	scene;

	scene.cylinders = NULL;
	scene.lights = NULL;
	scene.planes = NULL;
	scene.spheres = NULL;
	scene.ambient = NULL;
	scene.camera = NULL;
	return (scene);
}

int	parse_element(char *line, t_scene *scene)
{
	char	**line_parts;

	line_parts = ft_split_by_ws(line);
	if (parts_size(line_parts) == 0)
		return (0);
	if (strncmp(line_parts[0], "A", 1) == 0)
		set_ambient(scene, parse_ambient(line_parts));
	else if (strncmp(line_parts[0], "C", 1) == 0)
		set_camera(scene, parse_camera(line_parts));
	else if (strncmp(line_parts[0], "L", 1) == 0)
		add_light(scene, parse_light(line_parts));
	else if (ft_strncmp(line_parts[0], "sp", 2) == 0)
		add_sphere(scene, parse_sphere(line_parts));
	else if (strncmp(line_parts[0], "pl", 2) == 0)
		add_plane(scene, parse_plane(line_parts));
	else if (strncmp(line_parts[0], "cy", 2) == 0)
		add_cylinder(scene, parse_cylinder(line_parts));
	else
	{
		perror("invalid object");
		free_scene(scene);
		free_split(line_parts);
		exit(0);
	}
	free_split(line_parts);
	return (0);
}

t_scene	parse_elements(char *filename)
{
	int		fd;
	t_line	*head_of_elements;
	t_line	*temp;
	t_scene	scene;

	scene = init_scene();
	fd = open_file(filename);
	head_of_elements = get_all_lines(fd);
	temp = head_of_elements;
	while (temp)
	{
		parse_element(temp->content, &scene);
		temp = temp->next;
	}
	free_lines(head_of_elements);
	return (scene);
}
