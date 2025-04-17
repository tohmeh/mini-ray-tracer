/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:35:20 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/05 21:42:58 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void apply_ambient_light(t_scene scene, int *pixel_color)
{
    float ambient_intensity = scene.ambient->ratio;
    t_color ambient_color = scene.ambient->color;
    
    int obj_r = (*pixel_color >> 16) & 0xFF;
    int obj_g = (*pixel_color >> 8) & 0xFF;
    int obj_b =  *pixel_color & 0xFF;
    
    int amb_r = (ambient_color.r >> 16) & 0xFF;
    int amb_g = (ambient_color.g >> 8) & 0xFF;
    int amb_b = ambient_color.b & 0xFF;
    
    int final_r = (obj_r * ambient_intensity) + (amb_r * (1 - ambient_intensity));
    int final_g = (obj_g * ambient_intensity) + (amb_g * (1 - ambient_intensity));
    int final_b = (obj_b * ambient_intensity) + (amb_b * (1 - ambient_intensity));
    
    final_r = (final_r > 255) ? 255 : final_r;
    final_g = (final_g > 255) ? 255 : final_g;
    final_b = (final_b > 255) ? 255 : final_b;
    
    *pixel_color = (final_r << 16) | (final_g << 8) | final_b;
}

float compute_diffuse_light(t_vector normal, t_vector light_pos, t_vector intersection_point)
{
    t_vector light_dir = subtract_vectors(light_pos, intersection_point);
    light_dir = normalize_vector(light_dir);

    float intensity = dot_product(normal, light_dir);
    if (intensity < 0) 
        intensity = 0;

    return intensity;
}
float compute_specular_light(t_vector normal, t_vector light_pos, t_vector intersection_point, t_vector camera_pos, float shininess)
{
    t_vector light_dir = normalize_vector(subtract_vectors(light_pos, intersection_point));
    t_vector view_dir = normalize_vector(subtract_vectors(camera_pos, intersection_point));

    t_vector reflect_dir = subtract_vectors(multiply_vector_by_scalar(normal, 2.0f * dot_product(normal, light_dir)), light_dir);
    float spec = powf(fmax(dot_product(reflect_dir, view_dir), 0.0), shininess);

    return spec;
}
int in_shadow(t_vector intersection_point, t_light *light, t_scene scene)
{
    t_vector light_dir = normalize_vector(subtract_vectors(light->position, intersection_point));
    float light_distance = vector_length(subtract_vectors(light->position, intersection_point));

    // Create shadow ray with small offset to avoid self-shadowing
    t_ray shadow_ray;
    shadow_ray.b = add_vectors(intersection_point, multiply_vector_by_scalar(light_dir, 0.001));
    shadow_ray.D = light_dir; // Already normalized
    
    // Check spheres
    for (t_sphere *sphere = scene.spheres; sphere; sphere = sphere->next)
    {
        float t = compute_sphere_intersection(shadow_ray.D, sphere->center, shadow_ray.b, sphere->radius);
        if (t > 0 && t < light_distance)
            return 1;
    }
    
    // Check planes
    for (t_plane *plane = scene.planes; plane; plane = plane->next)
    {
        float t = compute_plane_intersection(plane->normal, plane->point, shadow_ray.D, shadow_ray.b);
        if (t > 0 && t < light_distance)
            return 1;
    }
    
    // Check cylinders
    for (t_cylinder *cylinder = scene.cylinders; cylinder; cylinder = cylinder->next)
    {
        float t = compute_cylinder_intersection(shadow_ray , *cylinder);
        if (t > 0 && t < light_distance)
            return 1;
    }
    
    return 0;
}