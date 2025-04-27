/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:28:21 by gakhoury          #+#    #+#             */
/*   Updated: 2025/04/05 15:56:22 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

int	validate_camera(char **line_parts)
{
	if (parts_size(line_parts) != 4)
		error_exit("camera must have 4 fields");
	if (!validate_id(line_parts[0], "C", 1))
		error_exit("invalid camera Id");
	if (!validate_coordinates(line_parts[1]))
		error_exit("invalid camera coordinates");
	if (!validate_orientation_vector(line_parts[2]))
		error_exit("invalid orientation vector [-1,1]");
	if (!validate_hfield(line_parts[3]))
		error_exit("invalid horizontal field [0,180]");
	return (1);
}
void update_camera_params_full(t_camera *camera)
{
    // Cache FOV calculations
    camera->params.fov_tan_half = tan((camera->fov * M_PI / 180.0) / 2);
    
    // Cache aspect ratio and pixel size
    camera->params.aspect_ratio = (float)WIDTH / (float)HEIGHT;
    camera->params.inv_width = 1.0f / (float)WIDTH;
    camera->params.inv_height = 1.0f / (float)HEIGHT;
    
    // Precalculate pixel deltas
    camera->params.pixel_dx = 2.0f * camera->params.aspect_ratio * camera->params.fov_tan_half * camera->params.inv_width;
    camera->params.pixel_dy = 2.0f * camera->params.fov_tan_half * camera->params.inv_height;
    
    // Update right vector when camera direction changes
    camera->params.right_vector = compute_right_vector(camera->direction);
    
    // Cache up vector (perpendicular to both direction and right)
    camera->params.up_vector = cross_product(camera->direction, camera->params.right_vector);
}

t_camera *init_camera(t_vector position, t_vector direction, float fov)
{
    t_camera *camera;
    
    camera = malloc(sizeof(t_camera));
    if (!camera)
        return (NULL);
        
    camera->position = position;
    camera->direction = direction;
    camera->fov = fov;
    
    // Initialize all cached parameters at once
    update_camera_params_full(camera);
    
    return (camera);
}

t_camera *parse_camera(char **line_parts)
{
    t_camera *camera;
    t_vector position;
    t_vector direction;
    float    fov;

    if (!validate_camera(line_parts))
        return (0);
    position = get_vector(line_parts[1]);
    direction = get_vector(line_parts[2]);
    direction = normalize_vector(direction); // Ensure normalized direction
    fov = get_float(line_parts[3]);
    camera = init_camera(position, direction, fov);
    return (camera);
}
