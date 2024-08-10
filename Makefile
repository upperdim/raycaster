ifeq ($(OS),Windows_NT)
	NAME = raycaster.exe
	DELETE_NAME = if exist $(NAME) del $(NAME)
	DELETE_OBJS = tools/clean_objs.bat
	DELETE_OBJS_DIR = if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	MKDIR_SAFE = mkdir
else
# TODO: untested
	NAME = raycaster
	DELETE_NAME = rm -f $(NAME)
	DELETE_OBJS = rm -f $(OBJS)
	DELETE_OBJS_DIR = rm -rf $(OBJ_DIR)
	MKDIR_SAFE = mkdir -p
# end of untested
endif

SRCS = $(wildcard src/*.c)
OBJ_DIR = obj
OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	gcc $(OBJS) -L"C:\libsdl\lib" -lmingw32 -lSDL2main -lSDL2 -mwindows -I"C:\libsdl\include" -o $(NAME)

$(OBJ_DIR):
	$(MKDIR_SAFE) $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c
	gcc -Wall -Wextra -Ofast -I"C:\libsdl\include" -c $< -o $@

clean: $(DELETE_OBJS)
	$(DELETE_OBJS_DIR)

fclean: clean
	$(DELETE_NAME)

re: fclean all

run: $(NAME)
	$(NAME)

runlim: $(NAME)
	$(NAME) -l
