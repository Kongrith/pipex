/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:30:30 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 21:36:54 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(t_data *data, char *cmd_failure, int err_code)
{
	if (cmd_failure && err_code != 200 && err_code != 201 && err_code != 202 && \
	err_code != 203 && err_code != 204 && err_code != 205)
	{
		free(cmd_failure);
		cleanup(data);
	}
	if (err_code == ENOENT || err_code == EACCES || err_code == 200 || \
	err_code == 201 || err_code == 202 || err_code == 203 || err_code == 204)
		exit(EXIT_FAILURE);
	if (err_code == 205)
		exit(126);
	exit(EXIT_FAILURE);
}

/*
200: Invalid Agrument
201: NO ENV PATH
202: EMPTY ENV
203: Can Not Pipe
204: Can Not Fork
*/
void	err_handler(t_data *data, char *cmd_failure, int err_code)
{
	if (err_code == ENOENT)
		perror(cmd_failure);
	else if (err_code == EACCES)
		perror(cmd_failure);
	else if (err_code == 200)
		write(2, cmd_failure, 47);
	else if (err_code == 201)
		write(2, cmd_failure, 25);
	else if (err_code == 202)
		write(2, cmd_failure, 23);
	else if (err_code == 203)
		write(2, cmd_failure, 5);
	else if (err_code == 204)
		write(2, cmd_failure, 5);
	else if (err_code == 205)
		write(2, cmd_failure, 7);
	exit_handler(data, cmd_failure, err_code);
}

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_ptr(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = (void *) NULL;
	}
}

void	cleanup(t_data *data)
{
	if (data->path_arr)
		free_double_ptr(data->path_arr);
	if (data->cmd1_arg)
		free_double_ptr(data->cmd1_arg);
	if (data->cmd2_arg)
		free_double_ptr(data->cmd2_arg);
	if (data->cmd1)
		free(data->cmd1);
	if (data->cmd2)
		free(data->cmd2);
}
