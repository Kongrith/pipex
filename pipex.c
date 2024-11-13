/*
./pipex in.txt "grep a" "wc -l" out.txt
*/

#include "pipex.h"
#include <string.h>

int process1(t_data *data, char **argv, char **envp)
{
	int fd;
	char **args;

	fd = data->fd_infile;
	close(data->pid[0]);
	// fd = open(argv[1], O_RDONLY);
	// if (fd == -1)
	// 	return (EXIT_FAILURE);
	dup2(fd, 0);
	close(fd);
	dup2(data->pid[1], 1);
	close(data->pid[1]);
	if (access(data->cmd1, R_OK) == -1)
	{
		write(2, data->cmd1_arg[0], strlen(data->cmd1_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	execve(data->cmd1, data->cmd1_arg, NULL);
	return (0);
}

int process2(t_data *data, char **argv, char **envp)
{
	int fd;
	char **args;
	// execve(data->cmd1, data->cmd1_arg, NULL);
	fd = data->fd_outfile;
	close(data->pid[1]);
	// fd = open(argv[4], O_WRONLY | O_CREAT , 0777);
	// if (fd == -1)
	// 	return (EXIT_FAILURE);
	// execve(data->cmd1, data->cmd1_arg, NULL);
	dup2(fd, 1);
	close(fd);
	dup2(data->pid[0], 0);
	// dprintf(0, "dprintf: \n");
	if (access(data->cmd2, R_OK) == -1)
	{
		write(2, data->cmd2_arg[0], strlen(data->cmd2_arg[0]));
		write(2, ": command not found", 20);
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	execve(data->cmd2, data->cmd2_arg, NULL);
	// close(fd);
	return (0);
}

void ipc_setup(t_data *data, char **argv, char **envp)
{
	pid_t pid;
	// int fd;

	if (pipe(data->pid) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// fd = open(argv[4], O_WRONLY | O_CREAT, 0777);
	// if (fd == -1)
	// 	exit(EXIT_FAILURE);
	if (pid == 0)
		process1(data, argv, envp);
	else
	{
		waitpid(pid, NULL, 0);
		process2(data, argv, envp);
	}
}

void pipex(t_data *data, char **argv, char **envp)
{
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile == -1)
		exit (EXIT_FAILURE);
	data->fd_outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (data->fd_outfile == -1)
		exit(EXIT_FAILURE);
	// int infile;
	// int outfile;
	// const char str1[] = "bingrep";
	// char ch = '/';

	// printf(">>>%s\n", ft_strchr(str1, ch));

	// if (ft_strchr(data->cmd1_arg[0], '/') == NULL)
	parse_commands(data);
	ipc_setup(data, argv, envp);
	// clean_up();
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc != 5)
		write(1, "Example Usage: ./pipex <infile> 'CMD1' 'CMD2' <outfile>\n", 56);
	else
	{
		if (!envp)
		{
			perror("empty env");
			exit(EXIT_FAILURE);
		}
		if (open(argv[1], O_RDONLY) == -1)
		{
			perror(ft_strjoin("-bash: ", argv[1]));
			exit(EXIT_FAILURE);
		}
		if (access(argv[1], R_OK) == -1)
		{
			perror("permission");
			exit(EXIT_FAILURE);
		}
		get_path_arr(&data, envp);
		data.cmd1_arg = ft_split(argv[2], ' ');
		data.cmd2_arg = ft_split(argv[3], ' ');
		pipex(&data, argv, envp);
	}
	return (0);
}
