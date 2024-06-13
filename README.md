## MAZE RUNNR
>Because, why not?

### Introduction


This project is features a maze game built entirely in C using the SDL library and upng library for texture loading.
 - Video can be found [here](https://www.youtube.com/watch?v=sCuARQZPzCk)
 - Landing page [here](https://michaelgift.github.io/Maze-Runner/)
 - Author(me) can be found [here](https://linkedin.com/in/smichaelgift)

### Installation

Install SDL on your system by following the appropriate tutorials [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
Afterwards
1. Clone this repo
2. Configure SDL Path
3. Compile the project with
```sh
gcc -Wall -Werror -Wextra -pedantic ./src/*.c -lm -o maze_runnr `sdl2-config --cflags` `sdl2-config --libs`;
```
4. Run the game with
```sh
./maze_runnr
```

### Contributions

Contributions are welcome. 

Fork the repo, make the changes and open the pr when ready.
You can use open an issue if you need further discussion or clarification.
