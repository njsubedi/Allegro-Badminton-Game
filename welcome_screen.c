/*##############################################################################\
MINI BADMINTON GAME MAIN MENU, DESIGNED BY KRISHNA K.C.
IT USES BITMAPS, MOUSE INPUT AND BACKGROUND SOUND.
IT LETS THE USER SELECT DIFFERENT MENU ITEMS FROM A LIST

note about display_exit_screen() : 
	the function takes integer argument. if the argument
	is 1, the "cancel" command will return to welcome screen,
	else if 0 is the argument, it will continue to previous 
	lines of code which called it... easy to understand
\******************************************************************************/

void welcome_screen()
{
	// set the mouse button simulation to 0
    mouse_b = 0;
		// draw the buffer into the screen, to reduce flickering
        blit(buffer, screen, 0,0,0,0,buffer->w, buffer->h);
		// draw the menu's background over the buffer
        blit(back, buffer, 0, 0, 0, 0, 1024, 768);
		// draw the list of menu items too over it
        blit(list, buffer, 0, 0, 170, 220, list->w, list->h);
		// set the image for mouse; 'cursor' is user defined image
        set_mouse_sprite(cursor);
		// show mouse pointer over the list
        show_mouse(list);
		// limit the mouse movement within the list
        set_mouse_range(0,0,list->w-40, list->h);
		// start selecting the menu items
        menu_selectItem();
}
	/* this function is created to make easy the task of checking position of mouse. */
	/* it takes four arguments.. x,y for top left edge, and x,y for right bottom */
	/* the x and y positions of mouse are checked whether they fall within the rectangular area */
        int mouseinside(int x1,int y1,int x2,int y2)
        {
                if (mouse_x > x1 && mouse_x < x2 && mouse_y > y1 && mouse_y < y2)
                     return 1;
                else
                    return 0;
        }

        void menu_selectItem()
        {
				// IF F5 KEY IS PRESSED, PROMPTLY START NEW GAME,
				// this is only for me :D .. since user won't know about it
                if(key[KEY_F5])
                {
                    clear(screen);
                    run_game();
                }
            // if menu items are hovered by mouse
				// when mouse is inside any of the list items,
				// draw a highlighted image of the item over it.
                if(mouseinside(95, 40, 480, 95)){
                    masked_blit(list_start, buffer, 0,0, 258,255, list_start->w, list_start->h);
                }
                if(mouseinside(95, 140, 480, 195)){
                    masked_blit(list_instructions, buffer, 0,0,258, 353,list_instructions->w,list_instructions->h);
                 }
                if(mouseinside(95, 240, 480, 295)){
                    masked_blit(list_gameOptions, buffer, 0,0,258,453,list_gameOptions->w,list_gameOptions->h);
                }
                if(mouseinside(95 , 340, 480, 370)){
                    masked_blit(list_aboutGame, buffer, 0,0,258,553,list_aboutGame->w,list_aboutGame->h);
                }
                /* if menu items are selected, ie mouse button is pressed, select specific function to call */
                if(mouseinside(95, 40, 480, 95) && mouse_b && 1) {
                        play_select_sound();
                       menu_selectStart();
                }
                if(mouseinside(95, 140, 480, 195) && mouse_b && 1){
                    play_select_sound();
                         menu_selectInstructions();
                }
                if(mouseinside(95, 240, 480, 295) && mouse_b && 1){
                    play_select_sound();
                       menu_selectGameOptions();
                }
                if(mouseinside(95 , 340, 480, 370) && mouse_b && 1){
                    play_select_sound();
                      menu_selectAboutGame();
                }
                if(mouseinside(565, 0, 665, 65) && mouse_b && 1){
                    play_select_sound();
                      menu_selectExit();
                    }
                else if(key[KEY_ESC])
                     display_exit_screen(false);
                else
                    welcome_screen();
		}
	// when the "Start" item is selected
        void menu_selectStart()
        {
            clear(screen);
			// display a menu to choose new game or continued
            choose_game();
        }

        void choose_game()
        {
            //rest(200);
                blit(choice, screen, 0 , 0,295, 300, choice->w, choice->h);
                set_mouse_sprite(cursor);
                set_mouse_range(0,0, choice->w, choice->h);
                show_mouse(choice);
				// if "new game" is selected, run new game
                if(mouseinside(0,0, 150,50) && mouse_b && 1)
                {
                        play_select_sound();
                        rest(500);
                        game_mode_choose();
                }
				// else if "continue" is selected, run continued game
                else if(mouseinside(250,0, 400, 50) && mouse_b && 1)
                        {
                           play_select_sound();
                           game_mode_choose();
                        }
				// else if Welcome Screen is displayed when clicked..
                else if (mouseinside(80,100, 310,150) && mouse_b && 1)
                        welcome_screen();
				// else .. i.e. when other keys are pressed, self call
                else choose_game();
        }


         void game_mode_choose()
        {
           // rest(200);

                blit(game_mode, screen, 0 , 0,295, 300, game_mode->w, game_mode->h);
                set_mouse_sprite(cursor);
                set_mouse_range(0,0, game_mode->w, game_mode->h);
                show_mouse(game_mode);
				// if "Single Player" is selected, run new game with single player
                if(mouseinside(0,0, 150,50) && mouse_b && 1)
                {
                        play_select_sound();
                        game_runs_as = singleplayer;
                        continue_game(0);
                }
				// else if "Multi Player" is selected, run multiplayer game
                else if(mouseinside(250,0, 400, 50) && mouse_b && 1)
                        {
                           play_select_sound();
                           game_runs_as = multiplayer;
                           continue_game(1);
                        }
				// else if Welcome Screen is displayed when clicked..
                else if (mouseinside(80,100, 310,150) && mouse_b && 1)
                        welcome_screen();
				// else .. i.e. when other keys are pressed, self call
                else game_mode_choose();
        }


         void menu_selectInstructions()
                {
                        blit(instruction, screen, 0, 0, 170, 220, back->w, back->h);
                        set_mouse_sprite(cursor);
                        show_mouse(instruction);
                        set_mouse_range(0,0,instruction->w,instruction->h);
                        if(mouseinside(575,335,665,365) && mouse_b && 1)
                        {
                            play_select_sound();
                             welcome_screen();
                        }
                        else menu_selectInstructions();
                }

        void menu_selectGameOptions()
                {
                        int resolution = 720;
                        int fullscreen = GFX_AUTODETECT_FULLSCREEN;
                        blit(options_back, screen, 0, 0, 200, 0, options_back->w, options_back->h);
                        set_mouse_sprite(cursor);
                        show_mouse(options_back);
                        set_mouse_range(0,0,options_back->w,options_back->h);
						// menu item to change the resolution
                        if(mouseinside(170,70,350,120) && mouse_b && 1){
                            resolution = 768;
                            set_gfx_mode(fullscreen, 1024, resolution, 0, 0);
                        }
						// menu item to change the game window
                        else if(mouseinside(170,130,250,160) && mouse_b && 1){

                            fullscreen= GFX_AUTODETECT_WINDOWED;
                           set_gfx_mode(fullscreen, 1024, resolution, 0, 0);
                        }
						// menu item at the bottom, to return to welcome screen
                        else if(mouseinside(75, 565, 350, 590) && mouse_b && 1){
                            play_select_sound();
                            welcome_screen();
                        }
						// in case other keys or buttons pressed, self call
                        else menu_selectGameOptions();
                }
		// upon selecting the Exit icon on welcome screen
        void menu_selectExit()
            {
                display_exit_screen(false);
            }
		
         void menu_selectAboutGame()
                {
						// display the image that is about the game
                        blit(about, screen, 0, 0, 170, 220, about->w, about->h);
                        set_mouse_sprite(cursor);
                        show_mouse(about);
                        set_mouse_range(0,0,about->w,about->h);
						// for the 'back' button ... 
                        if(mouseinside(575,335,665,365) && mouse_b && 1) welcome_screen();
                        else menu_selectAboutGame();
                }
                

        /*####### CUSTOMIZE KEYBOARD ###########################*/
        void customize_keyboard()
        {
            clear(screen);
				// till now.. no commands have been added here!
                textprintf(screen, font, 300, 200, makecol(255,255,255), "You have successfully customized keyboard.");
                readkey();
        }
        /********************************************************/

/************************* WELCOME SCREEN ENDS *******************************/
