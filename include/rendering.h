/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:35:13 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 19:33:48 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WIN_MNG_H
# define MLX_WIN_MNG_H

# include <stdlib.h>
# include <math.h>
# define WIDTH 800
# define HEIGHT 600
#define CONTROL_PANEL_WIDTH 200

// Forward declare t_minirt here
typedef struct s_minirt t_minirt;

// Vector structure
typedef struct s_vector {
    float x, y, z;
} t_vector;

typedef struct s_ray {
    t_vector b;
    t_vector D;
} t_ray;
// Color structure
typedef struct s_color {
    int r, g, b;
} t_color;


// Sphere structure (Can be multiple, so it's a linked list)
typedef struct s_sphere {
    t_vector center;
    float radius;
    t_color color;
    struct s_sphere *next;
} t_sphere;

// Plane structure (Can be multiple)
typedef struct s_plane {
    t_vector point;
    t_vector normal;
    t_color color;
    struct s_plane *next;
} t_plane;

// Cylinder structure (Can be multiple)
typedef struct s_cylinder {
    t_vector center;
    t_vector axis;
    float diameter;
    float height;
    t_color color;
    struct s_cylinder *next;
} t_cylinder;

// Light structure (Can be multiple)
typedef struct s_light {
    t_vector position;
    float brightness;
    t_color color;
    struct s_light *next;
} t_light;

// Ambient light (only one allowed)
typedef struct s_ambient {
    float ratio;
    t_color color;
} t_ambient;

// Camera (only one allowed)
typedef struct s_camera {
    t_vector position;
    t_vector direction;
    float fov;
} t_camera;
typedef enum OBJECTS_TYPE{
	NOTHING,
	SPHERE,
	CYLINDER,
	PLANE,
}	OBJECTS_TYPE;

typedef struct object_info{
	OBJECTS_TYPE type;
	void	*obj;
	t_vector	intersection_point;
	t_vector normal;
}	object_info;
// Main MiniRT struct to hold scene elements
typedef struct s_scene {
    t_ambient *ambient;
    t_camera *camera;
    t_light *lights;
    t_sphere *spheres;
    t_plane *planes;
    t_cylinder *cylinders;
	object_info	*object_hit;
}	t_scene;

// MinilibX window structure
typedef struct s_mlx {
    void *mlx;
    void *mlx_win;
    void *img;
    char *img_ptr; 
    int bpp; 
    int line_len; 
    int endian;
} t_mlx;



void put_pixel(t_mlx *mlx, int x, int y, int color) ;
// Function prototypes
void	win_init(t_minirt *minirt_struct, int total_width);
int 	close_window(t_minirt *minirt_struct);
int 	key_hook(int keycode, t_minirt *minirt_struct);

// Vector operations
t_vector subtract_vectors(t_vector v1, t_vector v2);
t_vector multiply_vector_by_scalar(t_vector v, float scalar);
float dot_product(t_vector v1, t_vector v2);
t_vector cross_product(t_vector v1, t_vector v2);
t_vector add_vectors(t_vector v1, t_vector v2);

// Ray-Sphere intersection calculations
float compute_sphere_intersection(t_vector ray_direction, t_vector sphere_center, t_vector ray_origin, float radius);
float calculate_A_sphere(t_vector D);
float calculate_B_sphere(t_vector D, t_vector sphere_center, t_vector ray_origin);
float calculate_C_sphere(t_vector sphere_center, t_vector ray_origin, float radius);
void render_scene(t_scene scene, t_mlx *mlx);
t_ray generate_ray(t_camera *cam, int i, int j);
t_vector new_vector(float x, float y, float z);
float compute_plane_intersection(t_vector plane_normal, t_vector plane_point, 
	t_vector ray_direction, t_vector ray_origin);
float compute_cylinder_intersection(t_ray ray, t_cylinder cyl);
float	vector_length(t_vector A);
// void	apply_ambient_light(t_scene scene, int *pixel_color);
void apply_ambient_light(t_scene scene, int *pixel_color);
t_vector sphere_normal_vector(t_sphere sphere, t_vector intersection);
t_vector plane_normal_vector(t_plane plane);
float compute_plane_intersection(t_vector plane_normal, t_vector plane_point, 
	t_vector ray_direction, t_vector ray_origin);
t_vector normalize_vector(t_vector v);
t_vector cylinder_normal_vector(t_cylinder cylinder, t_vector intersection);
void apply_ambient_light(t_scene scene, int *pixel_color);
float compute_diffuse_light(t_vector normal, t_vector light_pos, t_vector intersection_point);
int in_shadow(t_vector intersection_point, t_light *light, t_scene scene);
float compute_specular_light(t_vector normal, t_vector light_pos, t_vector intersection_point, t_vector camera_pos, float shininess);
void move_camera(t_camera *cam, t_vector move_dir, float speed);
t_vector compute_right_vector(t_vector direction);
void rotate_camera_y(t_camera *camera, float angle);
void rotate_camera_x(t_camera *camera, float angle);
object_info	object_detector(int i , int j ,t_scene *scene);
int mouse_handler(int button, int x, int y, void *param);

#endif