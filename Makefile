NAME = pipex
# LIBFTPRINTF= libftprintf.a

# LIBFTNAME = libft.a
# LIBFTDIR = ./libft
# LIBFT_PATH = $(LIBFTDIR)/$(LIBFTNAME)

CXX = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
IFLAGS = -I.

SRCS = pipex.c  utils.c
OBJS = $(SRCS:.c=.o)

# SRC_PRINTF = ft_printf.c ft_printchar.c ft_printstr.c ft_printptr.c ft_printdec.c ft_printhex.c ft_printuint.c \
# 		ft_printf_utilities.c
# OBJ_PRINTF = $(SRC_PRINTF:.c=.o)

all: $(NAME)
	@echo "built $(NAME) successfully"

# $(NAME): $(OBJS) $(LIBFTPRINTF)
# 	@$(CXX) -o $(NAME) $(OBJS) -L. -lftprintf


# $(LIBFTPRINTF): $(OBJ_PRINTF)
# 	@make -C $(LIBFTDIR)
# 	@cp $(LIBFT_PATH) $(LIBFTNAME)
# 	@mv $(LIBFTNAME) $(LIBFTPRINTF)
# 	@ar rcs $(LIBFTPRINTF) $(OBJ_PRINTF)


# $(LIBFT): $(OBJ_LIBFT)
# 	@ar rcs $(LIBFT) $(OBJ_LIBFT)

# %.o: %.c push_swap.h ft_printf.h ./libft/libft.h
# 	@$(CXX) $(CCFLAGS) $(IFLAGS) -c $< -o $@

%.o: %.c push_swap.h ft_printf.h ./libft/libft.h
	@$(CXX) $(CCFLAGS) $(IFLAGS) -c $< -o $@

# clean:
# 	@rm -f $(OBJS) $(OBJ_PRINTF)
# 	@make clean -C $(LIBFTDIR)

# fclean: clean
# 	@rm -f $(NAME) $(LIBFTPRINTF)
# 	@rm -f $(LIBFT_PATH)

re: fclean all

# .PHONY: all clean fclean re
