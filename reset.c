

/*######### DE-INITIALIZATION FUNCTION ############################*/
void game_over()
{
    clear(screen);
    textprintf(screen, font, 300, 220, makecol(255,255,255), "CURRENT GAME IS NOW OVER!");
    textprintf(screen, font, 320, 250, makecol(255,255,255), "PRESS [ENTER] TO RESET THE GAME, [ESC] TO EXIT.");
    if(player1.score > player2.score)
    textprintf(screen, font, 340, 200, makecol(0,255,255), "PLAYER 1 WINS!");
    else if (player2.score > player1.score)
    textprintf(screen, font, 340, 200, makecol(0,255,255), "PLAYER 2 WINS!");
    else
    textprintf(screen, font, 340, 200, makecol(0,255,255), "MATCH ENDS IN A DRAW!");
    readkey();
    if(key[KEY_ENTER])
    {
                clear_keybuf();
                cock.x = 504;
                cock.y = 500;
                cock.move_x = 0;
                cock.move_y = 0;
                cock.deflector = 0;
                cock.angle = 0;
                cock.move_y = 0;

                player1.x = 30;
                player1.y = 250;
                player1.score = 0;
                player1.power = 0;

                player2.x = 936;
                player2.y = 250;
                player2.score = 0;
                player2.power = 0;

                serve_started = 0;
				player1_has_returned_cock = 0;
				player2_has_returned_cock = 0;
    }
    else if(key[KEY_ESC]){
        welcome_screen();
        }
    else game_over();       // if other keys are pressed, call self
}

void deinitialize_game() {
	clear_keybuf();
	destroy_bitmap(court);
    destroy_bitmap(bat1);
    destroy_bitmap(bat2);
    destroy_bitmap(pic_cock);
    exit(EXIT_SUCCESS);
}
/*******************************************************************/

/*######### EXIT SCREEN ##########################################*/
void display_exit_screen(int a)
        {
                clear(buffer);
                blit(exit_image, screen, 0 , 0,295, 300, exit_image->w, exit_image->h);
                set_mouse_sprite(cursor);
                set_mouse_range(0,0, exit_image->w, exit_image->h);
                show_mouse(exit_image);
                if(mouseinside(0,0, 150,50) && mouse_b && 1 || key[KEY_ENTER])
                       {
                        play_select_sound();
                       rest(500);
                       clear(screen);
                       textprintf(screen, font, 300, 200, makecol(255,255,255), "Exiting the game...");
                       rest(1000);
                       deinitialize_game();
                       }

                else if(mouseinside(250,0, 400, 50) && mouse_b && 1 || key[KEY_ENTER])
                        {
                            if(a == false)
                                welcome_screen();
                                 /* continue_game() */;
                        }
                else if (mouseinside(80,100, 310,150) && mouse_b && 1)
                        welcome_screen();
                else display_exit_screen(a);
        }
/******************************************************************/


/*###### RESET THE GAME IF USER WANTS ###############*/
void reset()
{
    clear(screen);
    textprintf(screen, font, 300, 200, makecol(255,255,255), "You Have Requested to Reset the Current Game!");
    textprintf(screen, font, 320, 220, makecol(255,255,255), "Please press 'Enter' to reset the game.");
    textprintf(screen, font, 340, 230, makecol(255,255,255), "Press 'C' to continue playing!");
    readkey();
    if(key[KEY_ENTER])
    {
                clear_keybuf();
                cock.x = 504;
                cock.y = 500;
                cock.move_x = 0;
                cock.move_y = 0;
                cock.deflector = 0;
                cock.angle = 0;
                cock.move_y = 0;

                player1.x = 30;
                player1.y = 250;
                player1.score = 0;
                player1.power = 0;

                player2.x = 936;
                player2.y = 250;
                player2.score = 0;
                player2.power = 0;

                serve_started = 0;
				player1_has_returned_cock = 0;
				player2_has_returned_cock = 0;
    }
    else if(key[KEY_C]){ /* do nothing, just end the function call */;}
    else reset();       // if other keys are pressed, call self
}
