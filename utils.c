/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khkomasa <khkomasa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:05:54 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 15:09:07 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
200: Invalid Agrument
201: NO ENV PATH
202: EMPTY ENV
203: Can Not Pipe
204: Can Not Fork
*/
void	err_handler(char *cmd_failure, int err_code)
{
	if (err_code == ENOENT)
		perror(cmd_failure);
	else if (err_code == EACCES)
		perror(cmd_failure);
	else if (err_code == 200)
		write(2, cmd_failure, 56);
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
	if (cmd_failure)
		free(cmd_failure);
	if (err_code == ENOENT || err_code == EACCES || err_code == 200 || \
err_code == 201 || err_code == 202 || err_code == 203 || err_code == 204)
		exit(EXIT_FAILURE);
	if (err_code == 205)
		exit(126);
	exit(EXIT_FAILURE);
}

void	ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result = NULL;
}

void	get_path_arr(t_data *data, char **envp)
{
	int	i;

	i = 0;
	data->path_arr = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			data->path_arr = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (data->path_arr == NULL)
		err_handler("PATH variable is empty\n", 202);
}

void	parse_in_commands(t_data *data, char *path)
{
	int		i;
	char	*cmd1_path;

	i = 0;
	cmd1_path = NULL;
	while (data->path_arr[i])
	{
		if (cmd1_path)
		{
			free(cmd1_path);
			cmd1_path = NULL;
		}
		path = ft_strjoin(data->path_arr[i], "/");
		if (ft_strchr(data->cmd1_arg[0], '/') == NULL)
		{
			cmd1_path = ft_strjoin(path, data->cmd1_arg[0]);
		}
		else
		{
			cmd1_path = ft_strdup(data->cmd1_arg[0]);
		}
		if (path)
		{
			free(path);
			path = NULL;
		}
		if (access(cmd1_path, F_OK) == 0)
		{
			data->cmd1 = ft_strdup(cmd1_path);
			break ;
		}
		i++;
	}
	if (path)
	{
		free(path);
		path = NULL;
	}
	if (cmd1_path)
	{
		free(cmd1_path);
		cmd1_path = NULL;
	}
}

void	parse_out_commands(t_data *data, char *path)
{
	int		i;
	char	*cmd2_path;

	i = 0;
	cmd2_path = NULL;
	while (data->path_arr[i])
	{
		if (cmd2_path)
		{
			free(cmd2_path);
			cmd2_path = NULL;
		}
		path = ft_strjoin(data->path_arr[i], "/");
		if (ft_strchr(data->cmd2_arg[0], '/') == NULL)
		{
			cmd2_path = ft_strjoin(path, data->cmd2_arg[0]);
		}
		else
		{
			cmd2_path = ft_strdup(data->cmd2_arg[0]);
		}
		if (path)
		{
			free(path);
			path = NULL;
		}
		if (access(cmd2_path, F_OK) == 0)
		{
			data->cmd2 = ft_strdup(cmd2_path);
			break ;
		}
		i++;
	}
	if (path)
	{
		free(path);
		path = NULL;
	}
	if (cmd2_path)
	{
		free(cmd2_path);
		cmd2_path = NULL;
	}
}

void	cleanup(t_data *data)
{
	if (data->path_arr)
		ft_free (data->path_arr);
	if (data->cmd1_arg)
		ft_free (data->cmd1_arg);
	if (data->cmd2_arg)
		ft_free (data->cmd2_arg);
	if (data->cmd1)
		free (data->cmd1);
	if (data->cmd2)
		free(data->cmd2);
}
