cd ../src
gcc -c *.c -Wall -Wextra -I"C:\libsdl\include" -L"C:\libsdl\lib" -lmingw32 -lSDL2main -lSDL2
gcc -s *.o -I"C:\libsdl\include" -L"C:\libsdl\lib" -lmingw32 -lSDL2main -lSDL2 -o .\..\raycaster.exe
cd ../tools
