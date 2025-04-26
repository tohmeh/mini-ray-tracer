/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:20:48 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 14:56:10 by mtohmeh          ###   ########.fr       */
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

static int	create_and_link_line(t_line **head, t_line **current,
		char *line_content)
{
	t_line	*new_node;

	if (!line_content || (!line_content[0] && line_content[0] != '\n'))
		return (0);
	new_node = init_line(line_content);
	if (!new_node)
	{
		free_lines(*head);
		return (-1);
	}
	if (!*head)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
	return (0);
}

t_line	*get_all_lines(int fd)
{
	t_line	*head;
	t_line	*current;
	char	*line_content;

	head = NULL;
	current = NULL;
	line_content = get_next_line(fd);
	while (line_content)
	{
		if (create_and_link_line(&head, &current, line_content) == -1)
			return (NULL);
		free(line_content);
		line_content = get_next_line(fd);
	}
	return (head);
}
