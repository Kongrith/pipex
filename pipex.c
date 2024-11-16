/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:27:34 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 21:37:29 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process1(t_data *data, char **envp)
{
	int	fd;

	fd = data->fd_infile;
	close(data->pid[0]);
	dup2(fd, 0);
	close(fd);
	dup2(data->pid[1], 1);
	close(data->pid[1]);
	if (access(data->cmd1, R_OK) == -1)
	{
		write(2, data->cmd1_arg[0], ft_strlen(data->cmd1_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		cleanup(data);
		exit(127);
	}
	if (execve(data->cmd1, data->cmd1_arg, envp) == -1)
		err_handler(data, "execve\n", 205);
}

void	process2(t_data *data, char **envp)
{
	int	fd;

	fd = data->fd_outfile;
	close(data->pid[1]);
	dup2(fd, 1);
	close(fd);
	dup2(data->pid[0], 0);
	if (access(data->cmd2, R_OK) == -1)
	{
		write(2, data->cmd2_arg[0], ft_strlen(data->cmd2_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		cleanup(data);
		exit(127);
	}
	if (execve(data->cmd2, data->cmd2_arg, envp) == -1)
		err_handler(data, "execve\n", 205);
}

void	ipc_setup(t_data *data, char **argv, char **envp)
{
	pid_t	pid;

	get_path_arr(data, envp);
	data->cmd1_arg = ft_split(argv[2], ' ');
	data->cmd2_arg = ft_split(argv[3], ' ');
	parse_in_commands(data, NULL);
	parse_out_commands(data, NULL);
	if (pipe(data->pid) == -1)
		err_handler(data, "pipe\n", 203);
	data->id = fork();
	if (data->id == -1)
		err_handler(data, "fork\n", 204);
}

void	pipex(t_data *data, char **argv, char **envp)
{
	if (data->id == 0)
	{
		if (access(argv[1], O_RDONLY) == -1)
			err_handler(data, ft_strjoin("-bash: ", argv[1]), errno);
		if (access(argv[1], R_OK) == -1)
			err_handler(data, ft_strjoin("-bash: ", argv[1]), errno);
		data->fd_infile = open(argv[1], O_RDONLY);
		if (data->fd_infile == -1)
			err_handler(data, ft_strjoin("bash: ", argv[1]), errno);
		process1(data, envp);
	}
	else
	{
		data->fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->fd_outfile == -1)
			err_handler(data, ft_strjoin("bash: ", argv[4]), errno);
		process2(data, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.path_arr = NULL;
	data.cmd1_arg = NULL;
	data.cmd2_arg = NULL;
	data.cmd1 = NULL;
	data.cmd2 = NULL;
	if (argc != 5)
		err_handler(&data, "hint: ./pipex <infile> 'CMD1' 'CMD2'\
 <outfile>\n", 200);
	else
	{
		if (!envp)
			err_handler(&data, "PATH variable is not set\n", 201);
		ipc_setup(&data, argv, envp);
		pipex(&data, argv, envp);
	}
	return (0);
}
