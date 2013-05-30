Allegro-Badminton-Game
======================

This is a mini badminton game created using Allegro 4.2.2 library in C. Can be compiled for windows and linux.

How to compile?

Linux: ~$ gcc main.c `allegro-config --libs` -o badminton

Windows: Run the "windows_make.bat" file in the directory

The machine should have already installed allegro 4.2.2 package.


Project Source Description:

- Images:
	- MenuImage
		All the images used in menu
	+ All other images

- Sounds:
	- All the sounds used in the game

- main.c : 		This includes all other sources, so compiling this file only is enough
- collison.c:		Includes collision related functions and checks
- controls.c:		Includes functions to check user input and modify the coordinate of objects
- draw_objects.c:	Includes functions to output text and draw images
- files.c:		Used for score-keeping (Currently not used)
- fundamentals.c:	Variable declaration
- initialize.c:		Variable initialization
- reset.c:		Includes functions to reset the game after one session ends
- sound.c:		Includes functionst to play appropriate sounds
- users.c:		Used for score-keeping (Currently not used)
- welcome_screen.c:	Includes the functions related to welcome screen.
			This is where the game loop enters at first.


Other files:
- windows_make.bat:	Run this file to compile this game for windows (double click / from cmd)
- badminton:		Executable for Linux
