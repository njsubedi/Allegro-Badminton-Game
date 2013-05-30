#include "fundamentals.c" // all variable declarationd and prototypes
#include "initialize.c"   // set up hardwares, set initialize variables
#include "welcome_screen.c"// welcome screen menu
#include "collision.c"     // functions to check collision of objects
#include "sound.c"         // functions related to sound play
#include "draw_objects.c"  // functions to draw and print on screen
#include "controls.c"      // functions to control movement of objects
#include "reset.c"         // functions to pause/reset game play
#include "files.c"         // fucntions for scor handling (incomplete)

/* MAIN FUNCTION */
int main(){
    initialize_game();
    load_images();
    play_menu_sound();
    set_initial_values();
    
    welcome_screen();
	return 0;
}END_OF_MAIN()
/******************************************************************************/

void run_game(){
/* THE GAME RUNS WITHIN THIS TRUE WHILE LOOP */
	while (!0)
    {
    while(speed_limit > 0)
    {
         speed_limit --;
    /*============================================*/
        draw_court();               // GAME STEP 1
        show_mouse(court);
        set_mouse_range(0,0,court->w,court->h);
       	check_keyboard_entry();     // GAME STEP 2
    	control_bats();             // GAME STEP 3
        check_collision();          // GAME STEP 4
        update_cock_position();     // GAME STEP 5
		
        draw_bats_and_cock();       // GAME STEP 6
        draw_speed_meter();         // GAME STEP 7
        display_game_status();      // GAME STEP 8
        draw_buffer();              // GAME STEP 9
    /*============================================*/
    }
    // Speed limiting loop ends
    }
    deinitialize_game();
}

/*######## CONTINUE GAME ####################################*/
void continue_game(int no_of_players)
    {
   // edittext.c
    BITMAP *uname;
    //BITMAP* buffer6;
    //char name[20];
    int caret = 0;
    uname = load_bitmap("images/menu/username.pcx", NULL);
    
    for( i = 0 ; i <= no_of_players ; i++)
    
    masked_blit(uname, screen, 0, 0, 90, 80 + ( no_of_players * 100), uname->w, uname->h);
    
    while(1)
    {
        if(keypressed())
        {
            int newkey = readkey();
            char ASCII = newkey &0xff;
            char scancode = newkey >> 8;
 
            /* a character key was pressed; add it to the string */
            if(ASCII >= 32 && ASCII <= 126)
            {
                if(caret < 19)
                {
                    name[no_of_players][caret] = ASCII;
                    caret++;
                    name[no_of_players][caret] = '\0';
                }
            }
            else if(scancode == KEY_BACKSPACE)
            {
                if (caret > 0) 
                  
                   name[no_of_players][caret] = '\0';
                    caret--;
            }
        }
        
        /* all drawing goes here */
        //text_mode(15);
        textout(screen, font, name[no_of_players], 120, 123 + (no_of_players * 100), makecol(255, 20, 200));
      
        if(key[KEY_ENTER])
        {
            destroy_bitmap(uname);
           
            clear(screen);
            run_game();
            break;
            //gameStart();
        }
    }
}

/*************************************************************/

