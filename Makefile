ifeq ($(OS),Windows_NT)
	NAME = raycaster.exe
	SEP = \\
	DELETE = del 
else
	NAME = raycaster
	SEP = /
	DELETE = rm -f
endif

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(SRC_DIR)$(SEP)*.c
OBJS = *o

all: $(NAME)

$(NAME):
	gcc -c $(SRCS) -Wall -Wextra -I"C:\libsdl\include" -L"C:\libsdl\lib" -lmingw32 -lSDL2main -lSDL2
	gcc -s $(OBJS) -I"C:\libsdl\include" -L"C:\libsdl\lib" -lmingw32 -lSDL2main -lSDL2 -o $(NAME)

clean:
	$(DELETE) $(OBJS)

fclean: clean
	$(DELETE) $(NAME)

re: fclean all
