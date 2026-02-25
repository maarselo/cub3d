/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 16:23:53 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"

# define WINDOW_NAME "cub3D"
# define WINDOW_WIDTH  1920
# define WINDOW_HEIGHT 1080

typedef enum e_finish
{
	KILL_ALL_ENEMIES = 1,
	DIE = 2,
}	t_finish;

void	ft_game_loop(t_data *data);

#endif