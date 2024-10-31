#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	char *limiter;
	// char *file_path;
	int infile;
	int outfile;
	int pd[2];
	// int ac;
	// int i;
	// int save;
	// int flag;
} t_data;

#endif
