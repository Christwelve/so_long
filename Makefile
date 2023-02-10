
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
MLX42		=	MLX42/build/libmlx42.a

GREEN		= 	\033[0;32m
WHITE		=	\033[0m


# RULES

all: $(NAME)

$(NAME): $(LIBS) $(MLX42) $(MAN_OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(MAN_OBJ) $(LIBS) $(MLX42) $(INCLUDE)
	@echo "$(GREEN)*** so_long compiled!***$(WHITE)"

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS):
	@if [ ! -d "./libs" ]; then git clone https://github.com/Christwelve/libs.git; fi
	@make --silent -C libs

$(MLX42):
	@if [ ! -d "./MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	# @make --silent -C MLX42
	@cd MLX42 && cmake -B build
	@cd MLX42 && cmake --build build -j4


clean:
	$(RM) $(MAN_OBJ)
	make clean --silent -C libs
	@echo "$(GREEN)*** Object files cleaned! ***$(WHITE)"

fclean: clean
	$(RM) $(NAME)
	make fclean --silent -C libs
	@echo "$(GREEN)*** Executable (.a) file cleaned! ***$(WHITE)"

cleanlib:
	$(RM) MLX42
	$(RM) libs

re: fclean all
	@echo "$(GREEN)*** Cleaned and rebuilt libs! ***$(WHITE)"

.PHONY:  test clean fclean re all cleanlib
