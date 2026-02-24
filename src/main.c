/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 23:54:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "validator.h" //function main validator
#include "free.h" //ft_free_Data
#include "parser.h" //ft_parser
#include "game.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_error	*error;
	t_data	*data;

	error = ft_init_error();
	ft_validator(argc, argv, error);
	data = ft_init_data(error);
	if (!data)
		return (ft_error_handler(error, data), FAILED);
	ft_parser(argv[1], data, error);
	ft_game_loop(data);
	if (ft_error_handler(error, data))
		return (FAILED);
	ft_free_data(data);
	exit(0);
	return (SUCCES);
}
