/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:16:16 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 20:56:24 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_lines(t_line *head)
{
	t_line	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->content);
		free(head);
		head = tmp;
	}
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

t_line	*init_line(const char *content)
{
	t_line	*new_node;

	new_node = malloc(sizeof(t_line));
	if (!new_node)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	if (content)
		new_node->content = ft_strdup(content);
	else
		new_node->content = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_line	*get_all_lines(int fd)
{
	t_line	*head;
	t_line	*current;
	char	*line_content;
	t_line	*new_node;

	head = NULL;
	current = NULL;
	line_content = get_next_line(fd);
	while (line_content != NULL)
	{
		if (line_content != NULL || line_content[0] || '\n')
			new_node = init_line(line_content);
		else
			continue;
		if (!new_node)
		{
			free_lines(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		line_content = get_next_line(fd);
	}
	return (head);
}

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
	return (0);
}
t_scene	parse_elements(char *filename)
{
	int	fd;
	t_line	*head_of_elements;
	t_line	*temp;
	t_scene	scene = init_scene();
	
	fd = open_file(filename);
	head_of_elements = get_all_lines(fd);
	temp = head_of_elements;
	while (temp)
	{
		parse_element(temp->content, &scene);
		temp = temp->next;
	}
	return (scene);
}