/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtohmeh <mtohmeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:35:13 by mtohmeh           #+#    #+#             */
/*   Updated: 2025/04/21 21:28:34 by mtohmeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "rendering.h"

typedef struct s_line
{
	char			*content;
	struct s_line	*next;
}					t_line;

int					open_file(const char *filename);
t_line				*get_all_lines(int fd);
t_line				*init_line(const char *content);
int					validate_ambient_lighting(char **line_parts);

//  services
t_ambient			*parse_ambient(char **line_parts);
t_camera			*parse_camera(char **line_parts);

//  validation
int					validate_ratio(char *str);
int					validate_camera(char **line_parts);

// getters
t_color				get_color(char *str);
float				get_float(char *str);
int					get_int(char *str);
t_vector			get_vector(char *str);

// setters
void				add_light(t_scene *scene, t_light *light);
void				add_sphere(t_scene *scene, t_sphere *sphere);
void				add_plane(t_scene *scene, t_plane *plane);
void				add_cylinder(t_scene *scene, t_cylinder *cylinder);
void				set_ambient(t_scene *scene, t_ambient *ambient);
void				set_camera(t_scene *scene, t_camera *camera);

// utils
void				error_exit(const char *msg);
t_color				init_color(int r, int g, int b);
t_ambient			*init_ambient(float ratio, t_color color);
float				ft_atof(const char *str);
int					ft_is_number(const char *str);
int					ft_is_integer(const char *str);
int					ft_is_float(const char *str);
int					ft_validate_range(float num, float min, float max);
char				**ft_split_by_ws(const char *s);
t_vector			init_vector(float x, float y, float z);
int					validate_colors(char *str);
int					validate_coordinates(char *str);
int					validate_id(char *str, const char *comp, int size);
int					validate_hfield(char *str);
int					validate_orientation_vector(char *str);
int					validate_3unit_range(char **str, float min, float max);
int					parts_size(char **line_parts);
t_light				*parse_light(char **line_parts);
t_sphere			*parse_sphere(char **line_parts);
t_plane				*parse_plane(char **line_parts);
t_cylinder			*parse_cylinder(char **line_parts);
t_scene				parse_elements(char *filename);
void				free_lines(t_line *head);
int					open_file(const char *filename);
t_line				*init_line(const char *content);
t_line				*get_all_lines(int fd);

#endif
