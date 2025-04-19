NAME = miniRT

CC = gcc
CFLAGS = -Ofast -flto -march=native -funroll-loops -fno-plt -fstrict-aliasing -Wall -Wextra -Werror -I./minilibx-linux -g
LDFLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm

LIBFT_DIR = LIBFT
MINILIBX_DIR = minilibx-linux
SRC_DIR = src
OBJ_DIR = obj

LIBFT = $(LIBFT_DIR)/lib/libft.a
MINILIBX = $(MINILIBX_DIR)/libmlx.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/rendering/key_hooks/hooks.c \
	$(SRC_DIR)/rendering/math/cylinder_math.c \
	$(SRC_DIR)/rendering/math/general_math.c \
	$(SRC_DIR)/rendering/math/plane_math.c \
	$(SRC_DIR)/rendering/math/ray_math.c \
	$(SRC_DIR)/rendering/math/sphere_math.c \
	$(SRC_DIR)/rendering/rendering_related/put_pixels.c \
	$(SRC_DIR)/rendering/rendering_related/render.c \
	$(SRC_DIR)/rendering/rendering_related/wind_init.c \
	$(SRC_DIR)/rendering/rendering_related/lighting.c \
	$(SRC_DIR)/rendering/math/normal_vector_math.c \
	$(SRC_DIR)/rendering/key_hooks/triggers.c \
	$(SRC_DIR)/rendering/key_hooks/mouse_object_detection.c \
	$(SRC_DIR)/parsing/getters/getters.c \
	$(SRC_DIR)/parsing/services/ambient_service.c \
	$(SRC_DIR)/parsing/services/camera_service.c \
	$(SRC_DIR)/parsing/services/cylinder_service.c \
	$(SRC_DIR)/parsing/services/light_service.c \
	$(SRC_DIR)/parsing/services/plane_service.c \
	$(SRC_DIR)/parsing/services/sphere_service.c \
	$(SRC_DIR)/parsing/setters/adders.c \
	$(SRC_DIR)/parsing/setters/setters.c \
	$(SRC_DIR)/parsing/utils/error_exit.c \
	$(SRC_DIR)/parsing/utils/ft_atof.c \
	$(SRC_DIR)/parsing/utils/ft_is_number.c \
	$(SRC_DIR)/parsing/utils/initialization.c \
	$(SRC_DIR)/parsing/utils/split_by_ws.c \
	$(SRC_DIR)/parsing/validation/validate_3unit_range.c \
	$(SRC_DIR)/parsing/validation/validate_colors.c \
	$(SRC_DIR)/parsing/validation/validate_coordinates.c \
	$(SRC_DIR)/parsing/validation/validate_hfield.c \
	$(SRC_DIR)/parsing/validation/validate_id.c \
	$(SRC_DIR)/parsing/validation/validate_orientation_vector.c \
	$(SRC_DIR)/parsing/validation/validate_range.c \
	$(SRC_DIR)/parsing/validation/validate_ratio.c \
	$(SRC_DIR)/parsing/parse_element.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

# Clone minilibx-linux if not already cloned
$(MINILIBX_DIR):
	@git clone https://github.com/42paris/minilibx-linux.git $(MINILIBX_DIR)

# Compile libmlx after ensuring repo is cloned
$(MINILIBX): | $(MINILIBX_DIR)
	@$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(MINILIBX) $(LDFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MINILIBX_DIR) clean
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
