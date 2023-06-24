NAME = cub3d
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
RM = rm -f
MLX_LIB = ./minilibx_opengl_20191021/libmlx.a
SRC = pars.c\
	  ./get_next_line/get_next_line.c\
	  ./get_next_line/get_next_line_utils.c\
	  libft.c\
	  ft_split.c\
	  window.c\
	  utils.c\
	  move.c\
	  move_player.c\
	  draw.c\
	  draw_utils.c\
	  raycasting.c\
	  raycasting_utils.c\
	  raycasting_utils2.c\


OBJECT = ${SRC:.c=.o}
all: $(NAME)
$(NAME) : $(OBJECT)
		make -C ./minilibx_opengl_20191021
		cc  $(CFLAGS) $(OBJECT) -lmlx -framework OpenGL -framework AppKit $(MLX_LIB) -o $(NAME)

clean:
	$(RM) $(OBJECT)
	$(RM) $(BOBJECT) 
	
fclean:
	$(RM) $(OBJECT) 
	$(RM) $(NAME)

re: fclean all