/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:35:13 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/06/24 19:07:12 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include <math.h>
# include <stdlib.h>
# define WIDTH 500
# define HEIGHT 500

typedef struct s_minirt	t_minirt;

typedef struct s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef struct s_ray
{
	t_vector			b;
	t_vector			d;
}						t_ray;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct s_sphere
{
	t_vector			center;
	float				radius;
	t_color				color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	t_vector			point;
	t_vector			normal;
	t_color				color;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	t_vector			center;
	t_vector			axis;
	float				diameter;
	float				height;
	t_color				color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_light
{
	t_vector			position;
	float				brightness;
	t_color				color;
	struct s_light		*next;
}						t_light;

typedef struct s_ambient
{
	float				ratio;
	t_color				color;
}						t_ambient;

typedef struct s_camera_params
{
    float       fov_tan_half;       // tan(fov / 2)
    t_vector    right_vector;       // Right vector (cached)
    t_vector    up_vector;          // Up vector (cached)
    float       aspect_ratio;       // WIDTH/HEIGHT (cached)
    float       inv_width;          // 1.0/WIDTH (cached)
    float       inv_height;         // 1.0/HEIGHT (cached)
    // For common pixel calculations
    float       pixel_dx;           // 2 * aspect_ratio * fov_tan_half / WIDTH
    float       pixel_dy;           // 2 * fov_tan_half / HEIGHT
}               t_camera_params;

typedef struct s_camera
{
    t_vector position;
    t_vector direction;
    float fov;
    t_camera_params params; // Cache for the camera parameters
}               t_camera;
typedef enum t_object_type
{
	NOTHING,
	SPHERE,
	CYLINDER,
	PLANE,
}						t_object_type;

typedef struct t_object_info
{
	t_object_type		type;
	void				*obj;
	t_vector			intersection_point;
	t_vector			normal;
}						t_object_info;

typedef struct s_scene
{
	t_ambient			*ambient;
	t_camera			*camera;
	t_light				*lights;
	t_sphere			*spheres;
	t_plane				*planes;
	t_cylinder			*cylinders;
	t_object_info		*object_hit;
}						t_scene;

typedef struct s_mlx
{
	void				*mlx;
	void				*mlx_win;
	void				*img;
	char				*img_ptr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_mlx;

typedef struct s_hit_info
{
	t_vector			point;
	t_vector			normal;
	t_color				color;
}						t_hit_info;
typedef struct s_light_contrib
{
	int					ambient_r;
	int					ambient_g;
	int					ambient_b;
	int					diffuse_r;
	int					diffuse_g;
	int					diffuse_b;
	int					final_r;
	int					final_g;
	int					final_b;
}						t_light_contrib;

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_T 116
# define KEY_F 102
# define KEY_G 103
# define KEY_H 104
# define KEY_R 114
# define KEY_J 106
# define KEY_K 107
# define KEY_L 108

typedef enum e_directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}						t_directions;

typedef enum t_axis
{
	X,
	Y,
	Z
}						t_axis;




void					put_pixel(t_mlx *mlx, int x, int y, int color);
// Function prototypes
void					win_init(t_minirt *minirt_struct, int total_width);
int						close_window(t_minirt *minirt_struct);
int						key_press(int keycode, t_minirt *minirt_struct);
int						key_release(int keycode, t_minirt *minirt_struct);
int						loop_hook(t_minirt *minirt_struct);

// Vector operations
t_vector				subtract_vectors(t_vector v1, t_vector v2);
t_vector				multiply_vector_by_scalar(t_vector v, float scalar);
float					dot_product(t_vector v1, t_vector v2);
t_vector				cross_product(t_vector v1, t_vector v2);
t_vector				add_vectors(t_vector v1, t_vector v2);

// Ray-Sphere intersection calculations
float					compute_sphere_intersection(t_vector ray_direction,
							t_vector sphere_center, t_vector ray_origin,
							float radius);
float					calculate_A_sphere(t_vector d);
float					calculate_B_sphere(t_vector d, t_vector sphere_center,
							t_vector ray_origin);
float					calculate_C_sphere(t_vector sphere_center,
							t_vector ray_origin, float radius);
void					render_scene(t_scene scene, t_mlx *mlx);
t_ray					generate_ray(t_camera *cam, int i, int j);
t_vector				new_vector(float x, float y, float z);
float					compute_plane_intersection(t_vector plane_normal,
							t_vector plane_point, t_vector ray_direction,
							t_vector ray_origin);
float					compute_cylinder_intersection(t_ray ray,
							t_cylinder cyl);
float					vector_length(t_vector A);
// void	apply_ambient_light(t_scene scene, int *pixel_color);
void					apply_ambient_light(t_scene scene, int *pixel_color);
t_vector				sphere_normal_vector(t_sphere sphere,
							t_vector intersection);
t_vector				plane_normal_vector(t_plane plane);
float					compute_plane_intersection(t_vector plane_normal,
							t_vector plane_point, t_vector ray_direction,
							t_vector ray_origin);
t_vector				normalize_vector(t_vector v);
t_vector				cylinder_normal_vector(t_cylinder cylinder,
							t_vector intersection);
void					apply_ambient_light(t_scene scene, int *pixel_color);
float					compute_diffuse_light(t_vector normal,
							t_vector light_pos, t_vector intersection_point);
int						in_shadow(t_vector intersection_point, t_light *light,
							t_scene scene);
float					compute_specular_light(t_vector normal,
							t_vector light_pos, t_vector intersection_point,
							t_vector camera_pos);
void					move_camera(t_camera *cam, t_vector move_dir,
							float speed);
t_vector				compute_right_vector(t_vector direction);
void					rotate_camera_y(t_camera *camera, float angle);
void					rotate_camera_x(t_camera *camera, float angle);
t_object_info			object_detector(int i, int j, t_scene *scene);
int						mouse_handler(int button, int x, int y, void *param);
int						find_closest_intersection(t_ray ray, t_scene scene,
							float *closest_t, t_hit_info *hit);
void					handle_camera_rotation_key(int key, t_camera *cam,
							float speed);
void					handle_object_rotation_key(int keycode,
							t_minirt *minirt);
void					handle_translation_key(int key, t_minirt *rt);
void					handle_exit_key(int key, t_minirt *rt);
void					handle_movement_key(int key, t_camera *cam,
							float speed);
void					resize_object(t_scene *scene, float delta);
void					handle_object_detection(int x, int y, t_scene *scene);
int						mouse_handler(int button, int x, int y, void *param);
t_vector				get_cylinder_projection(t_vector v, t_vector axis);
int						solve_quadratic(t_vector t, float *t1, float *t2);
void					draw_instruction_panel(t_mlx *mlx);
int						program_init(t_minirt *minirt, char *filename);
void					setup_hooks(t_minirt minirt);
t_ray					create_shadow_ray(t_vector intersection_point,
							t_vector light_dir);
int						is_sphere_in_shadow(t_ray shadow_ray,
							float light_distance, t_scene scene);
int						is_plane_in_shadow(t_ray shadow_ray,
							float light_distance, t_scene scene);
int						is_cylinder_in_shadow(t_ray shadow_ray,
							float light_distance, t_scene scene);
void					free_minirt(t_minirt *minirt);
void					free_scene(t_scene *scene);
void					free_split(char **split);
void update_camera_params(t_camera *camera);


#endif