/*
	functions used:
	a. check_keyboard_entry() : to check the keys pressed by user
	b. control_bats() : to limit the movement of bats within court
	c. update_cock_position() : to update the variables regarding the x , y position and angle of cock
	d. serve() : to initialize or alter the service turn
*/

/*##### CHECK KEYBOARD ENTRY #############*/
void check_keyboard_entry()
{
     int random_serve;
     int angle_of_projection;
    /*Keys for movement of player*/
    

	if(game_runs_as == singleplayer)
    {
    // for player 1
        if(key[KEY_UP])     player1.y-=3;       // Player 2 moves up
    	if(key[KEY_DOWN])   player1.y+=3;       // Player 2 moves down
    	if(key[KEY_LEFT])   player1.x-=3;       // Player 2 moves left
    	if(key[KEY_RIGHT])  player1.x+=3;       // Player 2 moves right
    	
    //	player1.x=mouse_x;
    //	player1.y=mouse_y;

        	/* ARTIFICIAL INTELLIGENCE OF THE BAT 2 */
        	if(serve_started == 0 && player1_has_returned_cock == 1){
                
                if(cock.x <= court->w/2 - 200)
                    {player2.x -=3;
                     player2.y +=3;}
                    
                if(cock.y <=160 && cock.x <= court->w/2+200)
                    {player2.x +=4;
                     player2.y -=3;}
                    
                if(cock.x > court->w/2-120 && cock.y > 160)
                    {player2.x -=2;
                     player2.y +3;}
                    
                if(player2.y > player1.y_while_serving)
                    player2.y -=3;
                    
                if(player2.y < player1.y_while_serving)
                    player2.y+=3;
                    
                if(player2.y - cock.y <=40 && cock.x >= court->w)
                    {player2.y+=4;
                     player2.x-=2;}
            }
            if(player1_has_returned_cock == 1 && player2.y - cock.y <=100 && player2.x - cock.x <= 30){
                player2.x+=4;
                player2.y+=2;
            }
                
            if(cock_reaches_player2())
                player2_return_cock();

            if(player2.x <= 700 && serve_started == 0)
                player2.x += 3;
                
            if(serve_started == 0)
             player2.power = (player2.x - 650)/4;
    }
    
    else if(game_runs_as == multiplayer){

        if(key[KEY_W])    player1.y-=3;       // Player 1 moves up
    	if(key[KEY_S])   player1.y+=3;       // Player 1 moves down
    	if(key[KEY_A])   player1.x-=3;       // Player 1 moves left
    	if(key[KEY_D])  player1.x+=3;       // Player 1 moves right

    /* CONTORLS FOR THE SECOND PLAYER */
    	if(key[KEY_UP])     player2.y-=3;       // Player 2 moves up
    	if(key[KEY_DOWN])   player2.y+=3;       // Player 2 moves down
    	if(key[KEY_LEFT])   player2.x-=3;       // Player 2 moves left
    	if(key[KEY_RIGHT])  player2.x+=3;       // Player 2 moves right
    }
    /*Keys for controlling game*/
    if(key[KEY_ESC])
        display_exit_screen(true);
        
    if(key[KEY_SPACE] || (mouseinside(0,0,150,50) && mouse_b))   serve(serve_turn);
    if(key[KEY_HOME])   reset();

    /*** these controls are available only while serving ***/
    if(serve_started == 1){
        if(key[KEY_PGUP]){
			cock.move_y = 0;
			cock.y-=10;
			}
        if(key[KEY_PGDN]){
			cock.move_y = 0;
			cock.y+=10;
			}
        if(key[KEY_G]){
			cock.move_x = 0;
			cock.x -=10;
			}
        if(key[KEY_H]){
			cock.move_x = 0;
			cock.x +=10;
			}
    }
    /**** when the score of one of the players reaches high score... **/
        if(player1.score >= 25 || player2.score >= 25)
            game_over();
}
/******************************************/

/*##### CONTROL BATS WITHIN THE COURT #####################*/
void control_bats()
{
        
          /* Determine the side-ends of court, since the edges are at 45* angle, the position of shift is equal to difference between the bottom of court with the position of bats */
          int endLine_left  = 390 - player1.y;
          int endLine_right = 390 - player2.y;
          
		  /* This line actually controls the cock, not bats... It doesn't let the cock go beyond 450px at y axis */
          if(cock.y >= 500) cock.y = 500;
          
          /****** Control the Bat of player 1 within the court ****/
          // If bat1 reaches the net from the left
          if(player1.x >= 450)   player1.x = 450;
		  
          // If bat1 moves below the court
	 	  if(player1.y >= 370)  player1.y =370;
		  
          // If bat1 moves above the court
          if(player1.y <= 190)   player1.y =190;
		  
          // If bat1 reaches far left of the court
          if(player1.x <= endLine_left-30)  player1.x = endLine_left-30;

          /**** Control the Bat of player 2 within the court ****/
		  // if bat reaches the net from the right
		  if(player2.x <= 535)         player2.x = 535;
		  
		  // if bat moves below the court
          if(player2.y >= 370)         player2.y = 370;
		  
          // if bat moves above the court
          if(player2.y <= 190 )        player2.y +=2;
		  
		  // if bat moves far right from the court
          if(player2.x >= 984 - endLine_right+30) player2.x = 984 - endLine_right + 30;
}
/***********************************************************/

/*###### UPDATE THE CO-ORDINATES OF COCK'S POSITION ######################*/
void update_cock_position()
{
     /* Determine the side-ends of court */
      int endLine_left  = 390 - player1.y;
      int endLine_right = 390 - player2.y;
      float angle_of_projection;

      if(game_runs_as == singleplayer){

             // if the cock has been hit by player 1,
             if(player1_has_returned_cock)
                {
        			// the angle_of_projection is actually a divisor only
        			// though, it depends on the y position of the bat
                    angle_of_projection = (court->h - player1.y_while_serving)/20 + 45;
        			// Use a sine(angle) function to give projectile motion
        			// Them movement depends on the y position of bat while throwing the cock
                    cock.y =  (player1.y_while_serving + 50)- (200 * sin((0.2 * cock.x)/angle_of_projection));

                }

            if(player2_has_returned_cock)
                {
        			// similar to the earlier case
                    angle_of_projection = (court->h - player2.y_while_serving)/20 + 30 - cock.artificial_deviation1 + cock.artificial_deviation2;
                    cock.y = (player2.y_while_serving + 50) - (200 * sin((0.2 * (player2.x_while_serving + 100 - cock.x))/angle_of_projection));

                }

        	// in case the cock moves down to court due to failure of returning :)
             if(player2_has_returned_cock == 1 && cock.x <= endLine_left-20 && cock.y >= player2.y_while_serving+100)
                    player1_drop_cock();
             if(player1_has_returned_cock == 1 && cock.x<= endline_right && cock.y >= player1.y_while_serving+100)
                    player2_drop_cock();

         if(player2_has_returned_cock == 1 && cock.x <= endLine_left-50) player2_drop_cock();
         if(player1_has_returned_cock == 1 && cock.x >= 1024) player1_drop_cock();

        	 // Finally update the x and y position of the cock, its angle, etc
        	 // Actually the y position doesn't need to be updated,
        	 // though it could be useful while enhancing the motion
             cock.x -= cock.move_x;
             cock.y -= cock.move_y;
             if(cock.y >= 500)
                cock.y = 500; // again, limit the cock within the court
             cock.angle += cock.deflector;
    }
    /**************** multiplayer *******************/
    else if(game_runs_as == multiplayer){

         // if the cock has been hit by player 1,
         if(player1_has_returned_cock)
            {
    			// the angle_of_projection is actually a divisor only
    			// though, it depends on the y position of the bat
                angle_of_projection = (court->h - player1.y_while_serving)/20 + 40;
    			// Use a sine(angle) function to give projectile motion
    			// Them movement depends on the y position of bat while throwing the cock
                cock.y =  (player1.y_while_serving + 50) -(200 * sin((0.2 * cock.x)/angle_of_projection));

    			// in case the bats come too close to the net or go too high,
    			// limit the speed so that it is easier to play
                if(player1.y_while_serving <200 || player1.x_while_serving >= 300)
                    cock.move_x = -5;
            }

        if(player2_has_returned_cock)
            {
    			// similar to the earlier case
                angle_of_projection = (court->h - player2.y_while_serving)/20 + 40;
                cock.y = player2.y_while_serving -(160 * sin((0.2 * (player2.x_while_serving+20 - cock.x))/angle_of_projection));

                 if(player2.y_while_serving < 200 || player2.x_while_serving <=600)
                    cock.move_x =-5;

            }

    	// in case the cock moves beyond the endlines... see code! :)
    	if(player2_has_returned_cock == 1 && cock.y >= player2.y_while_serving+100)
                    player1_drop_cock();
             if(player1_has_returned_cock == 1 && cock.y >= player1.y_while_serving+100)
                    player2_drop_cock();

         if(player2_has_returned_cock == 1 && cock.x <= endLine_left-30 && cock.y<250) player2_drop_cock();
         if(player1_has_returned_cock == 1 && cock.x >= 1024 && cock.y<250) player1_drop_cock();

    	 // Finally update the x and y position of the cock, its angle, etc
    	 // Actually the y position doesn't need to be updated,
    	 // though it could be useful while enhancing the motion
         cock.x -= cock.move_x;
         cock.y -= cock.move_y;
         if(cock.y >= 500)
            cock.y = 500; // again, limit the cock within the court
         cock.angle += cock.deflector;
    }

}
/**************************************************************************/

/*###### CHOOSE THE SERVER AND INITIALIZE SERVICE #######*/
void serve(int turn)
{
play_whistle_sound();
cock.move_x = 0; // restrict cock movement in x axis
serve_started = 1; // set game state variable
player1_has_returned_cock = 0; // set game state
player2_has_returned_cock = 0; // set game state

    if(game_runs_as == singleplayer){

           if(turn % 2 == 0) // If the turn of player 1
            {
                clear_keybuf(); // remove memory buffer of keypress

                    player1.x = 15; // position the bat at (15,390)
                    player1.y = 390;

                    cock.angle=200; // set the cock orientation
                    cock.x = 60;	// position the cock at (60,450)
                    cock.y = 450;
                    cock.move_y = 1;
                    cock.deflector = -1; // set rotation angle of cock
            }

            else if(turn %2 != 0) // If the turn of player 2
            {
                clear_keybuf();	// clear memory buffer of key press
                    player2.x = 950; // position the bat at (950,390)
                    player2.y = 390;

                    cock.angle=180; // set the cock's orientation
                    cock.x = 940;	// position the cock at (900,450)
                    cock.y = 480;

                    cock.move_y = 1;
                if(cock_reaches_player2()) player2_return_cock();
            }
           else serve(1); // in case other arguments are passed, service goes to player 1
    }
    
    else if(game_runs_as == multiplayer){
                if(turn % 2 == 0) // If the turn of player 1
            {
                clear_keybuf(); // remove memory buffer of keypress

                    player1.x = 15; // position the bat at (15,390)
                    player1.y = 390;

                    cock.angle=200; // set the cock orientation
                    cock.x = 60;	// position the cock at (60,450)
                    cock.y = 450;

                    cock.deflector = -1; // set rotation angle of cock
            }

            else if(turn %2 != 0) // If the turn of player 2
            {
                clear_keybuf();	// clear memory buffer of key press

                    player2.x = 950; // position the bat at (950,390)
                    player2.y = 390;

                    cock.angle=180; // set the cock's orientation
                    cock.x = 900;	// position the cock at (900,450)
                    cock.y = 450;

                    cock.deflector = 1; // set the rotation of cock

            }
           else serve(1); // in case other arguments are passed, service goes to player 1

    }
}
/******************************************************/
