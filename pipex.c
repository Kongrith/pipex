#include "pipex.h"

// ./pipex in.txt "ls -l" "wc -l" out.txt

int process1(t_data *data, char **argv, char **envp)
{
	int		fd;
	int		nb_read;
	char	buf[BUFFER_SIZE + 1];

	close(data->pid[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	dup2(fd, 0);
	close(fd);
	dup2(data->pid[1], 1);
	close(data->pid[1]);

	// nb_read = read(0, buf, BUFFER_SIZE);
	// buf[nb_read] = '\0';

	// debugging purpose
	// dprintf(1, "%s\n", argv[2]);
	// write(1, buf, 6);
	// char *args[3];
	char **args;
	args = ft_split(argv[2]);

	// args[0] = "grep";
	// args[1] = "a";
	// args[2] = NULL;
	execve("/bin/grep", args, NULL);
}

int process2(t_data *data, char **argv, char **envp)
{
	int fd;
	int nb_read;
	int status;
	char buf[BUFFER_SIZE + 1];
	char **args;

	// waitpid(-1, &status, 0);
	wait(NULL);
	nb_read = -1;
	close(data->pid[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (EXIT_FAILURE);
	dup2(fd, 1);
	close(fd);
	dup2(data->pid[0], 0);
	close(data->pid[0]);

	args = ft_split(argv[3]);
	execve("/bin/wc", args, NULL);
	// debugging purpose
	// while (nb_read != 0)
	// {
	// 	nb_read = read(0, buf, BUFFER_SIZE);
	// 	if (nb_read == -1)
	// 	{
	// 		printf("Read error!\n");
	// 		return (1);
	// 	}
	// 	else if (nb_read == 0)
	// 	{
	// 		return (0);
	// 	}

	// 	buf[nb_read] = '\0';
	// 	dprintf(1, "%s", buf);
	// }
	// dprintf(2, "%s\n", argv[4]);
	return (0);
}

void pipex(t_data *data, char **argv, char **envp)
{
	pid_t pid; // ต้อง include <sys/types.h>

	if (pipe(data->pid) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE); // ต้อง include <stdlib.h>
	}
	if (pid == 0)
		process1(data, argv, envp);
	else
	{
		wait(NULL); // ต้อง include <sys/wait.h>
		process2(data, argv, envp);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (!envp)
		printf("Error: Empty ENV !!\n");
	if (argc != 5)
		printf("Example Usage: ./pipex infile 'ls -l' 'wc -l' outfile\n");
	pipex(&data, argv, envp);
	return (0);
}
