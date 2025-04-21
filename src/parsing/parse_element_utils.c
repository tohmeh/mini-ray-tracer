/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:20:48 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 21:28:58 by mtohmeh          ###   ########.fr       */
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
			continue ;
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
