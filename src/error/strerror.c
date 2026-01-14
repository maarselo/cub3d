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
[DUPLICATE_NO] = "Cub3D: the Nort Texture is declared twice in the file.",
[DUPLICATE_SO] = "Cub3D: the South Texture is declared twice in the file.",
[DUPLICATE_WE] = "Cub3D: the West Texture is declared twice in the file.",
[DUPLICATE_EA] = "Cub3D: the East Texture is declared twice in the file.",
[DUPLICATE_F] = "Cub3D: the Floor Color is declared twice in the file.",
[DUPLICATE_C] = "Cub3D: the Ceiling Color is declared twice in the file.",
[MULTI_STATEMENT] = "Cub3D: the file have two statements in the same line.",
[CONFIG_NOT_DEFINED] = "Cub3D: the file needs to define:\n  \
\tNO path/to/nort/texture\n \
\tSO path/to/south/texture\n \
\tWE path/to/west/texture\n \
\tEA path/to/east/texture\n \
\tF (RGB colors[0-255, 0-255, 0-255])\n \
\tC (RGB colors[0-255, 0-255, 0-255])"
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
