/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:45:03 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/05 21:04:22 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

int close_window(t_minirt *minirt_struct)
{
    mlx_destroy_window(minirt_struct->mlx->mlx, minirt_struct->mlx->mlx_win);
    exit(0);
    return (0);
}
int key_hook(int keycode, t_minirt *minirt_struct) {
    float move_speed = 0.5;
    float rotation_speed = 0.05; // Radians, adjust as needed
    t_camera *cam = minirt_struct->scene->camera;
    
    if (!minirt_struct || !minirt_struct->scene)
    {
        printf("Error: miniRT struct or scene not initialized\n");
        return (0);
    }
    
    if (keycode == KEY_ESC)
        close_window(minirt_struct);
    
    // Movement controls (WASD)
    if (keycode == KEY_W)  // Move forward
        move_camera(cam, cam->direction, move_speed);
    
    if (keycode == KEY_S)  // Move backward
        move_camera(cam, multiply_vector_by_scalar(cam->direction, -1), move_speed);
    
    if (keycode == KEY_A) {  // Move left
        t_vector right = compute_right_vector(cam->direction);
        move_camera(cam, multiply_vector_by_scalar(right, -1), move_speed);
    }

    if (keycode == KEY_D) {  // Move right
        t_vector right = compute_right_vector(cam->direction);
        move_camera(cam, right, move_speed);
    }
    
    // View rotation controls (Arrow keys)
    if (keycode == KEY_LEFT)  // Look left
        rotate_camera_y(cam, rotation_speed);
    
    if (keycode == KEY_RIGHT)  // Look right
        rotate_camera_y(cam, -rotation_speed);
    
    if (keycode == KEY_UP)  // Look up
        rotate_camera_x(cam, -rotation_speed);
    
    if (keycode == KEY_DOWN)  // Look down
        rotate_camera_x(cam, rotation_speed);

    // Re-render scene and update window
    render_scene(*minirt_struct->scene, minirt_struct->mlx);
    mlx_put_image_to_window(minirt_struct->mlx->mlx, minirt_struct->mlx->mlx_win, 
                            minirt_struct->mlx->img, 0, 0);
    
    return (0);
}