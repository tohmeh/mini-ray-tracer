/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:05:35 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/05 21:10:33 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void move_camera(t_camera *camera, t_vector direction, float distance)
{
    t_vector movement = multiply_vector_by_scalar(direction, distance);
    camera->position = add_vectors(camera->position, movement);
}
t_vector compute_right_vector(t_vector forward)
{
    t_vector up = {0, 1, 0};  // World up vector
    t_vector right = cross_product(up, forward);
    return normalize_vector(right);
}
void rotate_camera_y(t_camera *camera, float angle)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    
    float original_x = camera->direction.x;
    float original_z = camera->direction.z;
    
    camera->direction.x = original_x * cos_angle - original_z * sin_angle;
    camera->direction.z = original_x * sin_angle + original_z * cos_angle;
    
    camera->direction = normalize_vector(camera->direction);
}

void rotate_camera_x(t_camera *camera, float angle)
{   
    // Get the right vector (perpendicular to direction and world up)
    // t_vector right = compute_right_vector(camera->direction);
    
    // Create a rotation matrix around this right vector
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    
    float y = camera->direction.y;
    float z = camera->direction.z;
    
    // Rotate the direction vector around the right axis
    camera->direction.y = y * cos_angle - z * sin_angle;
    camera->direction.z = y * sin_angle + z * cos_angle;
    
    // Apply clamping to prevent looking too far up/down
    if (camera->direction.y > 0.95) camera->direction.y = 0.95;
    if (camera->direction.y < -0.95) camera->direction.y = -0.95;
    
    // Ensure the direction vector remains normalized
    camera->direction = normalize_vector(camera->direction);
}