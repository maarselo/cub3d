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
[MAP_EXTENSION] = "Cub3D: invalid map extension"
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
