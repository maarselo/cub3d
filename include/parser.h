/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "MLX42.h"
# include "cub3d.h"

# define WINDOW_WIDTH  1920
# define WINDOW_HEIGHT 1080

typedef enum s_start_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
} t_start_orientation;

typedef struct s_colors
{
	uint32_t	floor;
	uint32_t	ceiling;
} t_colors;

typedef struct textures
{
	mlx_image_t	*north;
	mlx_image_t *south;
	mlx_image_t	*west;
	mlx_image_t	*east;
} t_textures;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
} t_map;

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
	int	orientation;
} t_player;

typedef struct s_mlx{
	mlx_t	*window;
} t_mlx;

//parser.c
void	ft_parser(char *file, t_data *data, t_error *error);

//init_data.c
t_data	*ft_init_data(t_error *error);


#endif