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

#include "error.h"
#include <errno.h>
#include <string.h>

/*validator message errors
static char	*g_error_message_validator[ERROR_COUNT] = {
		[ARGUMENTS_NUMBER] = "Cub3D: invalid number of arguments",
		[MAP_EXTENSION] = "Cub3D: invalid map extension",
};*/

/*
char	*ft_strerror(int errnum, int process)
{
	if (process == SYSTEM)
		return (strerror(errno));
	else
	{
		if (process == VALIDATOR)
			return (error_message_validator[errnum]);
	}
}
*/