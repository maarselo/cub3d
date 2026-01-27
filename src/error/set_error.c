/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 20:25:15 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include "libft.h" //ft_multijoin
#include <errno.h>
#include "MLX42.h"

void	ft_set_error_static(int errnum, t_error *error, int process)
{
	error->error_number = errnum;
	error->message = ft_strerror(errnum, process);
	error->is_freeable = false;
}

void	ft_set_error_join(int errnum, char *join, t_error *error, int process)
{
	error->error_number = errnum;
	error->message = ft_multijoin(4, ft_strerror(errnum, process),
			" \"", join, "\".");
	error->is_freeable = true;
}

void	ft_set_error_system(t_error *error)
{
	error->error_number = errno;
	error->message = ft_strerror(errno, SYSTEM);
	error->is_freeable = false;
}

void	ft_set_error_mlx(t_error *error)
{
	error->error_number = MLX_ERROR;
	error->is_freeable = false;
	error->message = (char *)mlx_strerror(mlx_errno);
}
