# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 17:19:39 by dramos-j          #+#    #+#              #
#    Updated: 2025/02/25 13:55:29 by dramos-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = ./lib/libft.a
LIBFT_DIR = ./lib/libft/
MLX = ./lib/minilibx/libmlx.a
MLX_DIR = ./lib/minilibx/
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L./lib/minilibx -lmlx -lX11 -lXext
SRCS = src/main.c \
		src/utils/init_data.c \
		src/utils/free_mem.c \
		src/utils/utils.c \
		src/parse/parse.c \
		src/parse/parse_map.c \
		src/parse/parse_colors.c \
		src/parse/parse_textures.c \
		src/parse/parse_utils.c \
		src/raycasting/raycasting.c \
		src/raycasting/render.c \
		src/game/start_game.c \
		src/game/handle_events.c \
		src/parse/prints.c
OBJS_DIR = objs
OBJS = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling libft.a..."
	@$(MAKE) -C $(LIBFT_DIR) --silent
	@echo "✔️ libft.a compiled successfully"
	@echo "Compiling libmlx.a..."
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@echo "✔️ libmlx.a compiled successfully"
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)
	@echo "✔️ $(NAME) compiled successfully"

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
	@$(MAKE) clean -C $(MLX_DIR) > /dev/null 2>&1
	@$(RM) $(OBJS_DIR)
	@echo "🧹 Object files cleaned"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@$(RM) $(NAME)
	@echo "🧹 Executable $(NAME) cleaned"
	@echo "🧹 All cleaned (libft, mlx, objects, and executable)"

re: fclean all

.PHONY: all clean fclean re
