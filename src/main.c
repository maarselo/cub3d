/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 21:14:32 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "validator.h" //function main validator
#include "free.h" //ft_free_Data
#include "parser.h" //ft_parser
#include "game.h"

int	main(int argc, char **argv)
{
	t_error	*error;
	t_data	*data;

	error = ft_init_error();
	ft_validator(argc, argv, error);
	data = ft_init_data(error);
	ft_parser(argv[1], data, error);
	ft_game_loop(data);
	if (ft_error_handler(error, data))
		return (FAILED);
	ft_free_data(data);
	return (SUCCES);
}
