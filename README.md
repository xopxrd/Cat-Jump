# Cat-Jump

my SDL2 project for learning game dev, inspired by Polymars Cursor Custodian game

Cat Jump is a simple endless jump game. The cat will jump if you press a up key and move to left or right using left or right keys.

## compiling

~~~
g++ new/src/*.cpp -std=c++14 -Wall -ISDL2/include -LSDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o bin/release/Main
~~~

dont forget to place the SDL2.dll, SDL2_image.dll, SDL2_mixer.dll and SDL2_ttf.dll with the exe file

## issue
there's a memory leak when im using SDL_Surface* in a function for displaying a score, so i decided to remove it. I still didnt know how to solve that problem
