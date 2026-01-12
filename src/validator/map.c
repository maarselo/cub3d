/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include <fcntl.h> //open()
#include <errno.h>

void	ft_check_map(char *file, t_error *error)
{
	int		fd;
	//char	**map;

	if (ft_has_error(error))
		return ;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_set_error_join(errno, file, error, SYSTEM);
	
}