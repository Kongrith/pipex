NAME = pipex
HEADER = pipex.h

CXX = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

SRCS = pipex.c ft_split.c ft_strncmp.c ft_strjoin.c ft_strchr.c ft_strlen.c ft_strdup.c \
	pipex_util_1.c pipex_util_2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "built $(NAME) successfully"

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	@$(CXX) $(CCFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
