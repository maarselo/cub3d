/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //enum vars
#include <errno.h> //use of errno
#include <string.h> //use of strerror

//validator message errors
static char	*g_error_message_validator[ERROR_COUNT] = {
[ARGUMENTS_NUMBER] = "Cub3D: invalid number of arguments.",
[EMPTY_ARGUMENT] = "Cub3D: empty argument provided.",
[MAP_EXTENSION] = "Cub3D: invalid file extension. Expected \".cub\".",
[EMPTY_FILE] = "Cub3D: the file is empty.",
[INVALID_ORDER] = "Cub3D: invalid configuration order. The identifier must appear before its value.",
[DUP_CFG] = "Cub3D: a configuration value is declared twice in the file.",
[MULTI_STATEMENT] = "Cub3D: multiple configuration statements found on the same line.",
[CONFIG_NOT_DEFINED] = "Cub3D: missing required configuration entries.\n  \
Expected:\n \
	\tNO path/to/north_texture\n \
	\tSO path/to/south_texture\n \
	\tWE path/to/west_texture\n \
	\tEA path/to/east_texture\n \
	\tF  R,G,B  (0-255)\n \
	\tC  R,G,B  (0-255)",
[MAP_NOT_DEFINED] = "Cub3D: there is any map defined.",
[CFG_TEX_WITHOUT_PATH] = "Cub3D: texture identifier declared without a path (NO, SO, WE, EA).",
[CFG_TEX_MULTI_PATHS] = "Cub3D: multiple paths defined for the same texture identifier.",
[CFG_COLOR_UNDEF] = "Cub3D: floor or ceiling color not defined.",
[CFG_COLOR_LASTC_COMMA] = "Cub3D: invalid color format. The declaration must not end with a comma.",
[CFG_COLOR_CONSECUTIVE_COMMAS] = "Cub3D: invalid color format. Consecutive commas are not allowed.",
[CFG_COLOR_INVALID_VALUE_COUNT] = "Cub3D: invalid color format. Exactly three RGB values are required.",
[CFG_COLOR_INVALID_CHARS] = "Cub3D: invalid color format. RGB values must contain only digits and commas.",
[CFG_COLOR_INVALID_RANGE] = "Cub3D: invalid color value. RGB components must be in the range 0–255.",
[MAP_INVALID_CHARS] = "Cub3D: invalid map. Only characters '0', '1' and a single start position (N, S, E, W) are allowed.",
[MAP_MULTI_STARTS] = "Cub3D: invalid map. Exactly one start position (N, S, E, W) is required.",
[MAP_NOT_CLOSED] = "Cub3D: invalid map. The map is not properly closed by walls.",
};

char	*ft_strerror(int errnum, int process)
{
	if (process == SYSTEM)
		return (strerror(errno));
	else
	{
		if (process == VALIDATOR)
			return (g_error_message_validator[errnum]);
	}
	return ("Cub3D: Unknown error.");
}
