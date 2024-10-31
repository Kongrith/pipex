#ifndef PIPEX_H
# define PIPEX_H
// #include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>

#define BUFFER_SIZE 11
typedef struct s_data
{
	// char *limiter;
	// char *file_path;
	// int infile;
	// int outfile;
	int pid[2];
	// int ac;
	// int i;
	// int save;
	// int flag;
} t_data;

#endif
