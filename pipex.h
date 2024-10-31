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

#include "pipex.h"

int ft_is_delimiter(char c);
int ft_words_len(char *str);
char *ft_get_word(char *str);
char **ft_split(char *str);
void ft_free(char **result);

#endif
