/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorctx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define NORTH_TEX "NO "
# define SOUTH_TEX "SO "
# define WEST_TEX "WE "
# define EAST_TEX "EA "
# define FLOOR_COLOR "F "
# define CEILING_COLOR "C "

#include <stdbool.h>

typedef struct s_config_flags
{
	bool	no_found;
	bool	so_found;
	bool	we_found;
	bool	ea_found;
	bool	f_found;
	bool	c_found;
} t_config_flags;

#endif