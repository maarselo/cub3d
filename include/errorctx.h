/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorctx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORCTX_H
# define ERRORCTX_H

# include <stdbool.h> //struct variable

# define SUCCES 0 //exit_code in main
# define FAILED 1 //exit_code in main

# define FT_FAILED_INT -1
# define FT_FAILED_PTR NULL

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
	DUP_CFG,
	MULTI_STATEMENT,
	CONFIG_NOT_DEFINED,
	//MAP_NOT_DEFINED,

	ERROR_COUNT
}	t_validator_error;


//init_error.c
t_error	*ft_init_error(void);

//set_error.c
void	ft_set_error_static(int errnum, t_error *error, int process);
void	ft_set_error_join(int errnum, char *join, t_error *error, int process);

//strerror.c
char	*ft_strerror(int errnum, int process);

//handler_error.c
bool	ft_has_error(t_error *error);
int		ft_error_handler(t_error *error);

#endif