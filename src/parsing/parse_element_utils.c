/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:20:48 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/06/28 15:42:19 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_lst(t_line *head)
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
static int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
static int	is_line_empty_or_whitespace(const char *s)
{
	int	i = 0;
	while (s[i])
	{
		if (!is_delimiter(s[i]))
			return (0);
		i++;
	}
	return (1);
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
		if (!is_line_empty_or_whitespace(line_content))
		{
			if (create_and_link_line(&head, &current, line_content) == -1)
				return (NULL);
		}
		free(line_content);
		line_content = get_next_line(fd);
	}
	return (head);
}
