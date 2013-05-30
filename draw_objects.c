/*
	functions included:
	a. display_game_status() : to print the current game status in the screen for reference and information
	b. draw_buffer() : to draw a virtual (buffer) image on the screen, that helps reducing the flickring
	c. draw_court() : to draw the image of the court over the buffer image
	d. draw_bats_and_cocks(): to draw the rotated sprites (images with transparency) over the buffer
	e. draw_speed_meter() : to draw the rectangle on the basis of power of hit for each players

*/
/*###### DISPLAY GAME STATUS AT THE BOTTOM OF GAME SCREEN ########################*/
void display_game_status()
{
    text_mode(-1); // set the text mode with no background
    textprintf(buffer, font,  10, 510, makecol(0, 255, 255), "%s", name[0]);
    textprintf(buffer, font, 800, 510, makecol(2, 255, 255), "%s", name[1]);
	// information about the player 1
	textprintf(buffer, font, 100, 560, makecol(255,255,255), "%s", name);
    textprintf(buffer, font, 100, 530, makecol(255,255,255), "Player1: %d, %d", player1.x, player1.y);
    textprintf(buffer, font, 100, 550, makecol(255,255,255), "Player1 angle: %d", player1.angle);
	// information about the player 2
    textprintf(buffer, font, 800, 530, makecol(255,255,255), "Player2: %d, %d", player2.x, player2.y);
    textprintf(buffer, font, 800, 550, makecol(255,255,255), "Player2 angle: %d", player2.angle);
	// information about th position and orientation of cock
    textprintf(buffer, font, 400, 530, makecol(255,255,255), "Cock: %d, %d", cock.x, cock.y);
    textprintf(buffer, font, 400, 550, makecol(255,255,255), "Cock rotation: %d degrees", cock.angle);
	// information about the scores
    textprintf(buffer, font, 100, 590, makecol(255,255,255), "Player 1 score: %d", player1.score);
    textprintf(buffer, font, 800, 590, makecol(255,255,255), "Player 2 score: %d", player2.score);
    // information about the power of each player
    textprintf(buffer, font, 100, 610, makecol(255,255,0), "Player1 Power: %d", player1.power);
    textprintf(buffer, font, 800, 610, makecol(255,255,0), "Player2 Power: %d", player2.power);

    // game state variables display
    textprintf(buffer, font, 400, SCREEN_H - 50, makecol(200,200,200), "Serve started? %d", serve_started);
    textprintf(buffer, font, 400, SCREEN_H - 70, makecol(200,200,200), "Player 1 returned cock? %d", player1_has_returned_cock);
    textprintf(buffer, font, 400, SCREEN_H - 90, makecol(200,200,200), "Player 2 returned cock? %d", player2_has_returned_cock);

}
/**********************************************************************************/

/*###### DRAW SPEED METER ################################################*/
void draw_speed_meter()
{
		// Let the user Add extra speed or decrease speed of hit by checking key input
		// clear the rectangular speed bar
		
		// at first, draw black rectangles to remove the previously drawn bar
		rectfill(buffer, 100, 510, 100 + player1.power*5, 515, makecol(0,0,0));
        rectfill(buffer, 940, 510, 940 - player2.power*5, 515, makecol(0,0,0));
		
       // for player 1:
              // Q key and E key change the powers
              if (key[KEY_Q])
                    player1.power ++;
              if (key[KEY_E])
                    player1.power --;
					
              // if increased more than half of court,
                if(player1.power*5 >= 400)
                         player1.power -= player1.power * 0.02;
						 
              // if decreased more than initial position,
              if(player1.power*5 + 100 < 100)
                         player1.power ++;
						 
                // draw black rectangle to canopy the old position of bar
              rectfill(buffer, 100, 510, 100+ player1.power*5, 515, makecol(255,255-(player1.power*3), 0));

       // for player 2:
              // End key and Shift key change the power
              if (key[KEY_END])
                        player2.power ++;
              if (key[KEY_RSHIFT])
                         player2.power --;
						 
              // if move more than half of court
                if(940- player2.power*5 <= 524)
                         player2.power -= player2.power * 0.02;
						 
              // if decreased beyond initial position,
              if( 940 - player2.power*5 >940)
                         player2.power ++;
						 
                // draw black rectangle to canopy the old position of bar
              rectfill(buffer, 940, 500 + 10, 940-player2.power*5, 500 + 15, makecol(255,255-(player2.power*3), 0));
}
/**************************************************************************/

/*###### DRAW BATS AND COCK ###################################################*/
void draw_bats_and_cock()
{
        rotate_sprite(buffer, bat1, player1.x, player1.y, itofix(player1.angle));
        rotate_sprite(buffer, bat2, player2.x, player2.y, itofix(player2.angle));
        rotate_sprite(buffer, pic_cock, cock.x, cock.y, itofix(cock.angle));
      //  rotate_sprite(buffer,hand1, player1.x+15, player1.y+100, itofix(player1.angle));
      //  masked_blit(hand1_arm, buffer, 0,0,player1.x+18, player1.y+130, hand1_arm->w, hand1_arm->h);
}
/*******************************************************************************/

/*##### DRAW COURT AND BUFFER#####################################*/
        void draw_court()
        {
                    blit(court, buffer, 0, 0, 0, 0, court->w, court->h);
                    masked_blit(net, court, 0, 0, court->w/2-8 , court->h/2, net->w, net->h);
                    blit(scoreboard, buffer, 0, 0, 0, court->h, scoreboard->w, scoreboard->h);
        }
        void draw_buffer()
        {
                    blit(buffer, screen, 0, 0 , 0, 0, SCREEN_W, SCREEN_H);

        }
/********************************************************/
