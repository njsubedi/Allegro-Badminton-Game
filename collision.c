
/*###### CHECK COLLISION BETWEEN COCK AND BATS ################################*/
/* 
This file contains following functions:
	a. check_collision() : This is the major function that tallies the return values from different functions under this file and calls the functions to 	continue the game play.
	b. cock_reaches_player1() : This fuctions checks if the boundary of the cock image fall within the image of the racket representing the player 1 and returns true or false values
	c. cock_reaches_player2() : This function checks if the boundary of the cock image fall within the image of the racket representing the player 2 and returns true or false values
	d. check_net_cross(int) : This function checks whether the cock thrown by the player (wrt the argument passed) crosses the net or not and returns true or false results accordingly
	e. player1_check_hit(int) : This function checks if the user, i.e. the player presses one of the assigned keys to return back the cock. This function is called with one of the two arguments 0 or 1. In case 1 is passed, it checks the key and respectively calls the function to return the cock, drop down the cock or simulate escaping of the cock. In case 0 is passed, it only checks for the key press and returns true or false results respectively. This function is multifunctional.
	f. player2_check_hit(int) : Similar to player1_check_hit();
	g. player1_return_cock() : It changes the velocity of the cock in x and y directions, assigns angle of rotation and restores the game state variables to zero, hence returning the cock towards opponent, simulating the new instance of service.
	h. player2_return_cock() : Similar to player1_return_cock();
	i. player1_drop_cock() : This function is called in two cases. One, in case the cock crosses the boundry, and other when the cock drops on the court due to failure of the player to return it back. The function changes the turn of service, position and velocity of cock and updates the score of opponent.
	j. player2_drop_cock() : Similar to player1_drop_cock();
	
	
*/
void check_collision()
{
    /* This if block gets executed if serve() function has been called. It only controls the y position of cock. If the cock moves more upwards, here 250px, it checks its x position and calls the serve() function. If the cock is towards left from middle of court, player 1 will get chance to serve, else player 2 will get chance to serve */
    if(serve_started == 1){
            if(cock.y < 250)
            if(cock.x <= court->w/2)
                serve(1);
            else serve(2);
        }

	/* This else if ladder checks whether any key is pressed by the user if the cock reaches either of the players, else it checks if the cock crosses over the net. Moreover it checks if the cock drops down, i.e. falls below the bottom y position of the bat that's supposed to return it back */
    if(cock_reaches_player1()==1)
             player1_check_hit(1);
    else if(cock_reaches_player2()==1)
             player2_check_hit(1);
    else{//if the cock is not with either of the players, check if it touches net
        check_net_cross();
    
        // if the cock drops down before player 2 can return it
        if(player1_has_returned_cock == 1 && cock.y >= player2.y + bat1->h)
            player2_drop_cock();
		// if the cock drops down before player 1 can return it
        if(player2_has_returned_cock == 1 && cock.y >= player1.y + bat2->h)
            player1_drop_cock();
      }      

     /* Now animate the bats to show as if they are really hitting the cock, instead of giving the sight as if the cock reflects back after striking the bats.
	  So, when service has not been started, the cock approaches near the bats, and until it crosses beyond the bats, assign the angle to the bats on the basis of distance from the cock, i.e angle of rotation of bats will be backwards while the cock approaches, and towards forward while it returns, hence giving the smooth animated look. After the cock moves away from bats, restore their angles back to 0. */
     if(serve_started == 0 && cock.x - player1.x < 60 && cock.x - player1.x >= 10)
         player1.angle = cock.x - player1.x - 60;
        else player1.angle = 0;

     if(serve_started == 0 && player2.x - cock.x < 50 && player2.x - cock.x >= 10)
         player2.angle = 50 - (player2.x - cock.x);
        else player2.angle = 0;
    
}
/*******************************************************************************/

void check_net_cross(int player)
{
    if(player1_has_returned_cock == 1 && cock.x >= court->w/2 - 10 && cock.x <= court->w/2 && cock.y >= court->h/2+30)
    // if player1 throws cock and it doesn't cross the net
	{
            player1_drop_cock();
    }
        
    else if(player2_has_returned_cock == 1 && cock.x <= court->w/2+10 && cock.x >= court->w/2 && cock.y >= court->h/2+30)
	// if player 2 throws cock and it doesn't cross the net
    {
            player2_drop_cock();
    }
}

/************ if cock reaches player 1*************/
        int cock_reaches_player1(){
          if(cock.y < player1.y+30 && cock.y+20 > player1.y && cock.x+20 > player1.x && cock.x < player1.x+10)
          return 1;
          else return 0;
        }
/************ if cock reaches player 2 ************/
        int cock_reaches_player2(){
           if(cock.y < player2.y+50 && cock.y+40 > player2.y && cock.x < player2.x + 30 && cock.x+20 > player2.x)
           return 1;
           else return 0;
        }

/*###### CHECK IF  PLAYER 1 HITS THE COCK #################################*/
        int player1_check_hit(int a)
        {
            if( a == 1){ 
                if(key[KEY_Q] || key[KEY_E] || mouse_b)
                    player1_return_cock();
                if(serve_started == 0 && cock.y <= player2.y_while_serving - 100 && cock.x <= endLine_left - 30)
                    player2_drop_cock();
            }
            if(a == 0) // if requested just to check position
            {
                if(key[KEY_Q] || key[KEY_E])
                return true;
                else return false;
            }
        }
        /**********************************************************/

/*###### CHECK IF  PLAYER 2 HITS THE COCK #################################*/
        int player2_check_hit(int a)
        {
            if(a == 0)// if requested just to check position
            {
                if(key[KEY_END] || key[KEY_RSHIFT])
                return true;
                else return false;
            }

            if(a == 1){
                 if(key[KEY_END] || key[KEY_RSHIFT])
                         player2_return_cock();
      
                  if(serve_started == 0 && cock.x >= endline_right + 60 && cock.y <= player1.y_while_serving - 100)
                         player1_drop_cock();
             }
        }
        /**********************************************************/

/*###### RETURN THE COCK BY PLAYER 1 #######################################*/

        void player1_return_cock()
        {
						// change the velocity, angle etc for cock
                       cock.move_x = -( 7+ player1.power/10);
                       cock.angle = 45*_left;
                       cock.deflector = _right;
                       player1.angle = cock.angle/2;
                       cock.move_y = 0;

					   // set the game status variables
                       player1.x_while_serving = player1.x;
                       player1.y_while_serving = player1.y;
                       player1.power_while_serving = player1.power;
					   serve_started = 0;
                       player2_has_returned_cock = 0;
                       player1_has_returned_cock = 1;
					   player1.power=0;
                       play_player1_return_sound();
        }
        /****************************************************************/

/*###### DROP THE COCK BY PLAYER 1 ##################################################*/
        void player1_drop_cock()
        {
                       cock.y = 450;
                       cock.move_x = 0;
                       cock.x = 0;
                       cock.angle = 60*_left;
                       cock.deflector = 0;
					   //reset the game status variable
                       if(player2_has_returned_cock == 1){
                           player2_has_returned_cock = 0;
                        }
                        player2.score ++;
                        readkey();
                      //  rest(500);
                        serve(1);
        }
        /**********************************************************/

/*###### RETURN THE COCK BY PLAYER 2 #######################################*/
        void player2_return_cock()
        {
                if(game_runs_as == singleplayer){
						// change the velocity, angle etc for the cock
                        cock.move_x = 7 + player2.power / 10;
                        if(serve_started == 1)
                            cock.move_x -= 2;
                        
                        cock.angle = 45*_right;
                        cock.deflector = _left;
                        player2.angle = cock.angle/2;
                        cock.move_y = 0;
                        // TO VARY THE ANGLE WITH WHICH THE PLAYER2 RESPONDS TO THE COCK,
                        // Take tow random numbers so that one is greater or equal to
                        // other. Their difference gives a random number, used for
                        // the purpose. Using two numbers makes us easy to specify the range
                                cock.artificial_deviation2 = rand()%25 ;
                                cock.artificial_deviation1 = rand()%10;
						
						// set the game state variables
                        player2.x_while_serving = player2.x;
                        player2.y_while_serving = player2.y  - rand()%60;
                        player2.power_while_serving = player2.power;
                        serve_started = 0;
                        player1_has_returned_cock = 0;
                        player2_has_returned_cock = 1;
                        player2.power = 0;
                        play_player2_return_sound();
                }
                else if(game_runs_as == multiplayer){
                       	// change the velocity, angle etc for the cock
                        cock.move_x = 7 + player2.power / 10;
                        cock.angle = 45*_right;
                        cock.deflector = _left;
                        player2.angle = cock.angle/2;
                        cock.y = player2.y;
                        cock.move_y = 0;

                        cock.artificial_deviation2 = rand()%30;
                        cock.artificial_deviation1 = rand()%20;

						// set the game state variables
                        player2.x_while_serving =player2.x;
                        player2.y_while_serving = player2.y  - rand()%60;
                        player2.power_while_serving = player2.power;
                        serve_started = 0;
                        player1_has_returned_cock = 0;
                        player2_has_returned_cock = 1;
                        play_player2_return_sound();
                        player2.power = 0;
                }
        }
        
        /****************************************************************/

/*###### DROP THE COCK BY PLAYER 2 ##################################################*/
        void player2_drop_cock()
        {
                        cock.y = 450;
                        cock.move_x = 0;
                        cock.angle = 60*_right;
                        cock.deflector = 0;
						// reset the game state variable
                        if(player1_has_returned_cock == 1){
                            player1_has_returned_cock = 0;
                        }
                        player1.score ++;
                        readkey();
                       // rest(500);
                        serve(2);
        }
        /**********************************************************/
