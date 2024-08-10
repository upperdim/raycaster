ifeq ($(OS),Windows_NT)
	NAME = raycaster.exe
	DELETE_NAME = if exist $(NAME) del $(NAME)
	DELETE_OBJS = tools/clean_objs.bat
	DELETE_OBJS_DIR = if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	MKDIR_SAFE = mkdir
	LIBS = -L"C:\libsdl\lib" -lmingw32 -lSDL2main -lSDL2 -mwindows
	INCLUDES = -I"C:\libsdl\include"
else
	NAME = raycaster
	DELETE_NAME = rm -f $(NAME)
	DELETE_OBJS = rm -f $(OBJS)
	DELETE_OBJS_DIR = rm -rf $(OBJ_DIR)
	MKDIR_SAFE = mkdir -p
	LIBS = -L/usr/local/lib -lSDL2main -lSDL2 -lm
	INCLUDES = -I/usr/include/SDL2
endif

SRCS = $(wildcard src/*.c)
OBJ_DIR = obj
OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC = gcc
IGNORE_WARNINGS = -Wno-implicit-fallthrough -Wno-unused-parameter
CFLAGS = -Wall -Wextra -Ofast $(IGNORE_WARNINGS)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)

$(OBJ_DIR):
	$(MKDIR_SAFE) $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(DELETE_OBJS)
	$(DELETE_OBJS_DIR)

fclean: clean
	$(DELETE_NAME)

re: fclean all

run: $(NAME)
	$(NAME)

rer: re run

runlim: $(NAME)
	$(NAME) -l
