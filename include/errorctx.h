/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorctx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 21:29:53 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORCTX_H
# define ERRORCTX_H

# include <stdbool.h> //struct variable
#include "cub3d.h" //t_data struct

# define SUCCES 0 //exit_code in main
# define FAILED 1 //exit_code in main

typedef enum e_process
{
	SYSTEM,
	VALIDATOR,

}	t_process;

typedef struct s_error
{
	int		error_number;
	char	*message;
	bool	is_freeable;
}	t_error;

//validator errors
typedef enum e_validator_error
{
	ERROR_NONE,

	ARGUMENTS_NUMBER,
	EMPTY_ARGUMENT,
	MAP_EXTENSION,
	EMPTY_FILE,
	INVALID_ORDER,
	DUP_CFG,
	MULTI_STATEMENT,
	CONFIG_NOT_DEFINED,
	MAP_NOT_DEFINED,
	CFG_TEX_WITHOUT_PATH,
	CFG_TEX_MULTI_PATHS,
	CFG_COLOR_UNDEF,
	CFG_COLOR_LASTC_COMMA,
	CFG_COLOR_CONSECUTIVE_COMMAS,
	CFG_COLOR_INVALID_VALUE_COUNT,
	CFG_COLOR_INVALID_CHARS,
	CFG_COLOR_INVALID_RANGE,
	MAP_INVALID_CHARS,
	MAP_MULTI_STARTS,
	MAP_NOT_CLOSED,
	MLX_ERROR,

	ERROR_COUNT
}	t_validator_error;

//init_error.c
t_error	*ft_init_error(void);

//set_error.c
void	ft_set_error_static(int errnum, t_error *error, int process);
void	ft_set_error_join(int errnum, char *join, t_error *error, int process);
void	ft_set_error_system(t_error *error);
void	ft_set_error_mlx(t_error *error);

//strerror.c
char	*ft_strerror(int errnum, int process);

//handler_error.c
bool	ft_has_error(t_error *error);
bool	ft_error_handler(t_error *error, t_data *data);

#endif