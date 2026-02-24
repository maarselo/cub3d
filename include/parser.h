/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 23:05:53 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "MLX42.h"
# include "cub3d.h"
# include "game.h"

typedef enum s_start_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_start_orientation;

//Colors
typedef struct s_colors
{
	uint32_t	floor;
	uint32_t	ceiling;
}	t_colors;

//Textures
typedef struct s_weapon
{
	mlx_image_t	*idle;
	mlx_image_t	*shoot;
	mlx_image_t	*smoke;
	bool		is_shooting;
}	t_weapon;
typedef struct textures
{
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;
	mlx_image_t	*door;
	mlx_image_t	*timer;
	mlx_image_t	*date;
	t_weapon	*weapon;
}	t_textures;

//Map
typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
}	t_map;

//Enemies
typedef struct s_enemy
{
	double			pos_x;
	double			pos_y;
	bool			is_died;
	unsigned short	frame;
	struct s_enemy	*next;
}	t_enemy;
typedef struct s_enemies
{
	int			total_enemies;
	mlx_image_t	*enemy_frame1;
	mlx_image_t	*enemy_frame2;
	t_enemy		*enemies;
}	t_enemies;

//Player
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

//Game
typedef struct s_mlx
{
	mlx_t			*window;
	mlx_image_t		*framebuffer;
	double			z_buffer[WINDOW_WIDTH];
}	t_mlx;

typedef struct s_wall
{
	bool	hit; // used to knw if the ray hit a wall
	int		side; // to know if the ray passed a vertical or horizontal line first (0 vertical x 1 horizontal y)
	double	perpend_dist; // straight distance to the wall (avoid fisheye)
	int		wall_height; // how tall the wall looks on the screen
	int		draw_start; // point where you start to draw the wall
	int		draw_end; // point where you stop drawing the wall
	double	wall_x; // in what x pixel of the wall the ray collides
	int		tex_x; // x pixel (col) of the image wall_x represents
	double	step; // how many pixels to skip, to resize the image
	double	tex_pos; // initial position of the texture to draw
}	t_wall;

typedef struct s_render
{
	double	camera_x; // used to calculate in which side of the screen is current_col
	double	ray_dir_x; // direction of the ray casted on x axis
	double	ray_dir_y; // direction of the ray casted on y axis
	double	delta_dist_x; // how many pixels it takes for the ray to cross 1 whole x unit (vertical lines)
	double	delta_dist_y; // how many pixels it takes for the ray to cross 1 whole y unit (horizontal lines)
	double	side_dist_x; // distance to first vertical line
	double	side_dist_y; // distance to first horizontal line
	int		map_x; // player pos_x casted to int
	int		map_y; // player pos_y casted to int
	int		step_x; // used to know in which direction the player is going in the x axis
	int		step_y; // used to know in which direction the player is going in the y axis
	t_wall	*wall;
}	t_render;

//Bonus
//Minimap
typedef struct s_minimap
{
	int	start_x;
	int	start_y;
	int	final_x;
	int	final_y;
	int	center_x;
	int	center_y;
	int	tile_size;
}	t_minimap;

//parser.c
void	ft_parser(char *file, t_data *data, t_error *error);

//init_data.c
t_data	*ft_init_data(t_error *error);

#endif