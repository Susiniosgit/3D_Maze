# 3D_Maze
- The Maze is a 3D Maze game that uses ray casting to render a 2D map into a 3D navigable world!.
- The Maze was written was written in C ussing SDL2 library. Deveploment was performed using Ubuntu 14.04 LTS - gcc (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4.
- It runs on Mac OS X and Linux/Ubuntu. The game uses the technique raycasting to create the apparent 3D nature of the maze.
# About SDL2
- Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It is used by video playback software, emulators, and popular games including Valve's award winning catalog and many Humble Bundle games. for more information on[SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer)

# Requirements to Play
  - Linux/ubuntu or Macos
  - SDL2 and its sdl_image
# Installation

 - Sdl2 installation
download the installation script [install_SDL2.sh](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/graphics_programming/install_SDL2.sh) and run it in your ubuntu Terminal as follows:
root@h:cd ~/Downloads$ ls
install_SDL2.sh
root@h:cd ~/Downloads$chmod 755 install_SDL2.sh
root@h:cd ~/Downloads$sudo ./install_SDL2.sh

# Play the game
 - clone the [github repository](https://github.com/Susiniosgit/3D_Maze.git)
 - Compile all .c files in the maze directory:
  ```
  gcc -Wall -Werror -Wextra -pedantic ./src/*.c -lm $(sdl2-config --cflags --libs) -lSDL_image -o maze
   ```
 - Execute ./mazea and play game.
 - Use up and down arrow keys to move forward and backward (keys w and s serve the same function)
 - Use right and left arrow keys to turn the camera arround (keys d and a serve the same function)
# Controls
 W or up arrow key - Moving forward
 S or down arrow - Moving backward
 left arrow key - to rotate the player in counter clock wise direction
 right arrow key - to rotate the player in clock wise direction
