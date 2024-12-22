SOURCES_FILES  =  so_long.c \
                  map_name.c \
                  errors.c \
				  exit_game.c \
				  graphics.c \
				  keycodes.c \
				  valid_map.c \
				  get_next_line/get_next_line.c \
				  get_next_line/get_next_line_utils.c

# Define the header file
HEADER         =	so_long.h \

# Convert the source files into object files
OBJECTS        =  $(SOURCES_FILES:.c=.o)

# Output executable name
NAME           =  so_long

# MinilibX library path and file
MINILIBX_PATH  =  ./minilibx-linux
MINILIBX       =  $(MINILIBX_PATH)/libmlx.a

# Compiler and flags
CC             =  clang
RM             =  rm -f
CFLAGS         =  -Wall -Wextra -Werror
MLXFLAGS       =  -L. -lXext -L. -lX11

# Rule to compile .c files into .o files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Default target
all: $(NAME)

# Rule to link object files into the final executable
$(NAME): $(OBJECTS) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJECTS) $(MINILIBX) $(MLXFLAGS) -o $(NAME)

# Clean up object files
clean:
	$(RM) $(OBJECTS)

# Clean up everything, including the executable
fclean: clean
	$(RM) $(NAME)

# Rebuild the project
re: fclean all

# Declare these as non-file targets
.PHONY: all clean fclean re
