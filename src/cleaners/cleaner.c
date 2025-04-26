/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:30:46 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/26 20:00:39 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
}

void	free_minirt(t_minirt *minirt)
{
	if (!minirt)
		return ;
	if (&minirt->scene)
		free_scene(minirt->scene);
	if (&minirt->mlx)
		free_mlx(minirt->mlx);
}

void	free_lines(t_line *head)
{
	t_line	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}
