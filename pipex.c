#include "pipex.h"

// ./pipex in.txt "ls -l" "wc -l" out.txt

int process1(t_data *data, char **argv, char **envp)
{
	int fd;
	int nb_read;
	char buf[BUFFER_SIZE + 1];

	close(data->pd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	dup2(fd, 0);
	close(fd);
	dup2(data->pd[1], 1);
	close(data->pd[1]);

	nb_read = read(0, buf, BUFFER_SIZE);
	// dprintf(1, "%d\n", nb_read);
	buf[nb_read] = '\0';
	// dprintf(1, "CMD1: %s\n", buf);

	write(1, buf, 6);
}

void process2(t_data *data, char **argv, char **envp)
{
	char buf[BUFFER_SIZE + 1];

	close(data->pd[1]);
	dup2(data->pd[0], 0);
	close(data->pd[0]);
	// dprintf(1, "CMD2:\n");
	read(0, buf, 5);
	buf[5] = '\0';
	write(1, buf, 5);
	write(1, "\n", 1);
}

void pipex(t_data *data, char **argv, char **envp)
{
	pid_t pid; // ต้อง include <sys/types.h>

	if (pipe(data->pd) == -1)
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
