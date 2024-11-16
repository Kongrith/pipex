/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:05:54 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 21:33:00 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		err_handler(data, "PATH variable is empty\n", 202);
}

void	parse_in_commands(t_data *data, char *path)
{
	int		i;
	char	*cmd1_path;

	i = 0;
	cmd1_path = NULL;
	while (data->path_arr[i])
	{
		free_ptr(cmd1_path);
		path = ft_strjoin(data->path_arr[i], "/");
		if (ft_strchr(data->cmd1_arg[0], '/') == NULL)
			cmd1_path = ft_strjoin(path, data->cmd1_arg[0]);
		else
			cmd1_path = ft_strdup(data->cmd1_arg[0]);
		free_ptr(path);
		if (access(cmd1_path, F_OK) == 0)
		{
			data->cmd1 = ft_strdup(cmd1_path);
			break ;
		}
		i++;
	}
	free_ptr(cmd1_path);
}

void	parse_out_commands(t_data *data, char *path)
{
	int		i;
	char	*cmd2_path;

	i = 0;
	cmd2_path = NULL;
	while (data->path_arr[i])
	{
		free_ptr(cmd2_path);
		path = ft_strjoin(data->path_arr[i], "/");
		if (ft_strchr(data->cmd2_arg[0], '/') == NULL)
			cmd2_path = ft_strjoin(path, data->cmd2_arg[0]);
		else
			cmd2_path = ft_strdup(data->cmd2_arg[0]);
		free_ptr(path);
		if (access(cmd2_path, F_OK) == 0)
		{
			data->cmd2 = ft_strdup(cmd2_path);
			break ;
		}
		i++;
	}
	free_ptr(cmd2_path);
}
