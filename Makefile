
NAME		= 	so_long
CFLAGS		= 	-Wall -Werror -Wextra
MLXFLAGS	=	-lglfw -L "$(HOME)/.brew/opt/glfw/lib/"
CC			= 	cc
RM			=	rm -rf
INCLUDE 	= 	-I include

MAN_FILES	=	src/main.c \
				src/check_input.c \
				src/window.c \
				src/keys.c

MAN_OBJ		=	$(MAN_FILES:.c=.o)

LIBS		=	libs/libs.a
MLX42		=	MLX42/libmlx42.a


# RULES

all: $(NAME)

$(NAME): $(LIBS) $(MLX42) $(MAN_OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(MAN_OBJ) $(LIBS) $(MLX42) $(INCLUDE)
	@echo "\033[0;32m*** so_long compiled!***\033[0m"

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS):
	@if [ ! -d "./libs" ]; then git clone https://github.com/Christwelve/libs.git; fi
	@make --silent -C libs

$(MLX42):
	@if [ ! -d "./MLX42" ]; then git clone https://github.com/Christwelve/MLX42.git; fi
	@make --silent -C MLX42

clean:
	$(RM) $(MAN_OBJ)
	make clean --silent -C libs
	make clean --silent -C MLX42
	@echo "\033[0;32m*** Object files cleaned! ***\033[0m"

fclean: clean
	$(RM) $(NAME)
	make fclean --silent -C libs
	make fclean --silent -C MLX42
	@echo "\033[0;32m*** Executable (.a) file cleaned! ***\033[0m"

re: fclean all
	@echo "\033[0;32m*** Cleaned and rebuilt libs! ***\033[0m"

.PHONY:  test clean fclean re all
