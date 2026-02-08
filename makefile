# **************************************************************************** #
#                                  MiniRT Makefile                             #
# **************************************************************************** #

NAME        = miniRT

CC          = gcc
DEBUG       = 0

ifeq ($(DEBUG), 1)
    CFLAGS  = -g -Wall -Wextra -Werror -fopenmp -I./minilibx-linux
else
    CFLAGS  = -Ofast -flto -march=native -funroll-loops -fno-plt -fstrict-aliasing -fopenmp -Wall -Wextra -Werror -I./minilibx-linux
endif

LDFLAGS     = -L./minilibx-linux -lmlx -lX11 -lXext -lm -fopenmp

LIBFT_DIR   = LIBFT
MINILIBX_DIR= minilibx-linux
SRC_DIR     = src
OBJ_DIR     = obj

LIBFT       = $(LIBFT_DIR)/lib/libft.a
MINILIBX    = $(MINILIBX_DIR)/libmlx.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/main_utils.c \
	$(SRC_DIR)/rendering/math/cylinder_math.c \
	$(SRC_DIR)/rendering/math/cylinder_math_utils.c \
	$(SRC_DIR)/rendering/rendering_related/lighting_utils.c \
	$(SRC_DIR)/rendering/math/general_math.c \
	$(SRC_DIR)/rendering/math/plane_math.c \
	$(SRC_DIR)/rendering/math/ray_math.c \
	$(SRC_DIR)/rendering/math/sphere_math.c \
	$(SRC_DIR)/rendering/rendering_related/put_pixels.c \
	$(SRC_DIR)/rendering/rendering_related/render.c \
	$(SRC_DIR)/rendering/rendering_related/wind_init.c \
	$(SRC_DIR)/rendering/rendering_related/lighting.c \
	$(SRC_DIR)/rendering/math/normal_vector_math.c \
	$(SRC_DIR)/rendering/hooks/mouse_object_detection.c \
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
	$(SRC_DIR)/parsing/parse_element_utils.c \
	$(SRC_DIR)/rendering/rendering_related/intersections.c \
	$(SRC_DIR)/rendering/hooks/camera_rotation.c \
	$(SRC_DIR)/rendering/hooks/camera_translation.c \
	$(SRC_DIR)/rendering/hooks/object_translation.c \
	$(SRC_DIR)/rendering/hooks/object_rotation.c \
	$(SRC_DIR)/rendering/hooks/exit.c \
	$(SRC_DIR)/rendering/hooks/objects_resize.c \
	$(SRC_DIR)/rendering/hooks/key_hooks.c \
	$(SRC_DIR)/rendering/hooks/mouse_hooks.c \
	$(SRC_DIR)/rendering/math/general_math2.c \
	$(SRC_DIR)/rendering/rendering_related/left_panel.c \
	$(SRC_DIR)/cleaners/cleaner.c \
	$(SRC_DIR)/cleaners/cleaner_utils.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ============================== RULES ============================== #

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MINILIBX_DIR):
	@git clone https://github.com/42paris/minilibx-linux.git $(MINILIBX_DIR)

$(MINILIBX): | $(MINILIBX_DIR)
	@$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(MINILIBX) $(LDFLAGS) -o $(NAME)
	@echo "Build successful!"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MINILIBX_DIR) clean
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Executable removed."

re: fclean all

.PHONY: all clean fclean re

