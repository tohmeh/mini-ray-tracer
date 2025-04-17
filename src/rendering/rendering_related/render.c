/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:08:40 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/05 21:43:29 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"


void render_scene(t_scene scene, t_mlx *mlx)
{
    t_vector intersection_point;
    int i = 0;
    while (i < WIDTH)
    {
        int j = 0;
        while (j < HEIGHT)
        {
            t_ray ray = generate_ray(scene.camera, i, j);
            int pixel_color = 0xAAAAAA;
            float closest_t = INFINITY;
            t_vector normal;
            
            t_sphere *sphere = scene.spheres;
            while (sphere)
            {
                float t_sphere = compute_sphere_intersection(ray.D, sphere->center, ray.b, sphere->radius);
                if (t_sphere > 0 && t_sphere < closest_t)
                {
                    closest_t = t_sphere;
                    intersection_point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D, t_sphere));
                    normal = sphere_normal_vector(*sphere, intersection_point);
                    // Convert t_color to int color
                    pixel_color = (sphere->color.r << 16) | (sphere->color.g << 8) | sphere->color.b;
                }
                sphere = sphere->next;
            }
            
            // Process all planes in the linked list
            t_plane *plane = scene.planes;
            while (plane)
            {
                float t_plane = compute_plane_intersection(plane->normal, plane->point, ray.D, ray.b);
                if (t_plane > 0 && t_plane < closest_t)
                {
                    closest_t = t_plane;
                    intersection_point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D, t_plane));
                    normal = plane_normal_vector(*plane);
                    // Convert t_color to int color
                    pixel_color = (plane->color.r << 16) | (plane->color.g << 8) | plane->color.b;
                }
                plane = plane->next;
            }
            
            // Process all cylinders in the linked list
            t_cylinder *cylinder = scene.cylinders;
            while (cylinder)
            {
                // Note: convert diameter to radius by dividing by 2
                float t_cylinder = compute_cylinder_intersection(ray, *cylinder);
                if (t_cylinder > 0 && t_cylinder < closest_t)
                {
                    closest_t = t_cylinder;
                    intersection_point = add_vectors(ray.b, multiply_vector_by_scalar(ray.D, t_cylinder));
                    normal = cylinder_normal_vector(*cylinder, intersection_point);
                    // Convert t_color to int color
                    pixel_color = (cylinder->color.r << 16) | (cylinder->color.g << 8) | cylinder->color.b;
                }
                cylinder = cylinder->next;
            }
            
            if (closest_t < INFINITY)
            {
                float ambient_factor = scene.ambient->ratio;
                int ambient_r = (int)(((pixel_color >> 16) & 0xFF) * ambient_factor);
                int ambient_g = (int)(((pixel_color >> 8) & 0xFF) * ambient_factor);
                int ambient_b = (int)((pixel_color & 0xFF) * ambient_factor);
                
                int final_r = ambient_r;
                int final_g = ambient_g;
                int final_b = ambient_b;
                
                t_light *light = scene.lights;
                if (light)
                {
                    if (!in_shadow(intersection_point, light, scene))
                    {
                        float diffuse = compute_diffuse_light(normal, light->position, intersection_point);
                        float specular = compute_specular_light(normal, light->position, intersection_point, scene.camera->position, 16.0f);
                        
                        float light_distance = vector_length(subtract_vectors(light->position, intersection_point));
                        float attenuation = 1.0 / (1.0 + 0.01 * light_distance + 0.001 * light_distance * light_distance);
                        
                        int diffuse_r = (int)(((pixel_color >> 16) & 0xFF) * diffuse * light->brightness * attenuation);
                        int diffuse_g = (int)(((pixel_color >> 8) & 0xFF) * diffuse * light->brightness * attenuation);
                        int diffuse_b = (int)((pixel_color & 0xFF) * diffuse * light->brightness * attenuation);
                        
                        int spec_intensity = (int)(240.0f * specular * light->brightness * attenuation);
                        
                        final_r += diffuse_r + spec_intensity;
                        final_g += diffuse_g + spec_intensity;
                        final_b += diffuse_b + spec_intensity;
                    }
                }
                final_r = final_r > 255 ? 255 : final_r;
                final_g = final_g > 255 ? 255 : final_g;
                final_b = final_b > 255 ? 255 : final_b;
                
                pixel_color = (final_r << 16) | (final_g << 8) | final_b;
            }
            
            put_pixel(mlx, i, j, pixel_color);
            j++;
        }
        i++;
    }
}
