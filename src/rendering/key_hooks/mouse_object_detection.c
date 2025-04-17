/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_object_detection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:09:46 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/03/30 21:34:05 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	object_detector(int i , int j ,t_scene *scene)
{
	t_ray ray_generated = generate_ray(&(scene->camera), i , j);
	
	//the main idea is the generate rays , this rays if they hit an object we know what object the did hit then we make it bigger or smaller. 
}