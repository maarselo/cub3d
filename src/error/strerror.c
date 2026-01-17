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
[EMPTY_ARGUMENT] = "Cub3D: empty argument.",
[MAP_EXTENSION] = "Cub3D: invalid file extension",
[EMPTY_FILE] = "Cub3D: the file is empty.",
[INVALID_ORDER] = "Cub3D: configuration line malformed — token must appear first.",
[DUP_CFG] = "Cub3D: a configuration value is declared twice in the file.",
[MULTI_STATEMENT] = "Cub3D: the file has two statements in the same line.",
[CONFIG_NOT_DEFINED] = "Cub3D: the file needs to define:\n  \
\tNO path/to/nort/texture\n \
\tSO path/to/south/texture\n \
\tWE path/to/west/texture\n \
\tEA path/to/east/texture\n \
\tF (RGB colors[0-255, 0-255, 0-255])\n \
\tC (RGB colors[0-255, 0-255, 0-255])",
[MAP_NOT_DEFINED] = "Cub3D: there is any map defined.",
[CFG_WITHOUT_PATH] = "Cub3D: texture path missing for a cardinal direction (NO, SO, WE, EA).",
[CFG_MULTI_PATHS] = "Cub3D: multiple paths defined for the same cardinal direction.",
[CFG_COLOR_UNDEF] = "Cub3D: floor or ceiling color not defined."
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
