
/*########### INITIALIZATION FUNCTION ############################*/
void initialize_game() {
	allegro_init(); // initialize allegro library
	set_color_depth(32); // set desktop color depth, 32 to support buffering and transparency

	if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024, 768, 0, 0) != 0)// window mode for running the game
        {
        allegro_message("Error initializing graphics hardware!");
        return;
    }
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "") != 0) // in case sound driver is not found
        {
        allegro_message("Error initializing sound system!");
        return;
    }
	install_timer(); // install the timer variables
	install_keyboard(); // install keyboard driver
	install_mouse(); // install mouse driver

	/* Game speed limiting functions*/
     LOCK_VARIABLE(speed_limit);	// allegro specific line
     LOCK_FUNCTION(speed_limiter);	// allegro spicific line
     install_int_ex(speed_limiter, BPS_TO_TIMER(50)); // set the rate of BPS, here 50; the greater the more speed of game
    /***********************************************/
}/*****************************************************************/


/*##### LOAD IMAGES ##########################################################*/
/* note:buffer is blank bitmap pointer of dimensions equal to screen resolution
        court, bat1 etc are images used throughout the game*/
void load_images()
{
  // actually not only images but also sounds are loaded.. ;) 
  
    // IMAGES USED IN THE MAIN GAME PLAY
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
    scoreboard = load_bitmap("images/scoreboard.pcx", NULL);
    court = load_bitmap("images/court_new.pcx", NULL);
	bat1 = load_bitmap("images/bat1.pcx", NULL);
	bat2 = load_bitmap("images/bat2.pcx", NULL);
	pic_cock = load_bitmap("images/cock.pcx", NULL);
    exit_image = load_bitmap("images/exit.pcx", NULL);
    net = load_bitmap("images/net.pcx", NULL);
    hand1 = load_bitmap("images/hand1.pcx", NULL);
    hand1_arm = load_bitmap("images/hand1_arm.pcx", NULL);
	
	// MENU ITEM IMAGES
	menu_buffer = create_bitmap(700,600);
    back = load_bitmap("images/menu/menu_back.pcx", NULL);
    list = load_bitmap("images/menu/menu_list.pcx", NULL);
    hand = load_bitmap("images/menu/hand.pcx", NULL);
    cursor = load_bitmap("images/menu/mouse.pcx", NULL);
    about = load_bitmap("images/menu/about.pcx", NULL);
    instruction = load_bitmap("images/menu/instruction.pcx", NULL);
    choice = load_bitmap("images/menu/choice.pcx", NULL);
    game_mode = load_bitmap("images/menu/game_mode.pcx", NULL);
    options_back = load_bitmap("images/menu/options_back.pcx", NULL);

    //MENU HOVER ITEM IMAGES
    list_start = load_bitmap("images/menu/list_start.pcx", NULL);
    list_instructions = load_bitmap("images/menu/list_instructions.pcx", NULL);
    list_gameOptions = load_bitmap("images/menu/list_gameOptions.pcx", NULL);
    list_aboutGame = load_bitmap("images/menu/list_aboutGame.pcx", NULL);

	// SOUNDS USED THROUGHOUT THE GAME ARE LOADED
    select_sound = load_sample("sounds/select.wav");
    menu_sound = load_sample("sounds/menu.wav");
    whistle_sound = load_sample("sounds/whistle.wav");
    returnL_sound = load_sample("sounds/return_left.wav");
    returnR_sound = load_sample("sounds/return_right.wav");

	// EXCEPTION HANDLING: in case any of the files are not found,
	// our program will terminate abnormally. to prevent it...
	if(buffer==NULL || court==NULL || bat1==NULL || bat2==NULL || pic_cock==NULL || net == NULL || menu_buffer==NULL
    || back==NULL || list==NULL || hand == NULL || cursor==NULL || about==NULL || instruction==NULL || choice== NULL
    || list_start == NULL || list_instructions == NULL || list_aboutGame == NULL || options_back == NULL ||
     list_start == NULL || list_instructions == NULL || list_gameOptions == NULL || list_aboutGame == NULL ||
      select_sound == NULL || menu_sound == NULL || whistle_sound == NULL || returnL_sound == NULL ||
    returnR_sound == NULL)
	{
        set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("Error: Installation is probably corrupted. Please reinstall game. This error has been experienced due to failure in accessing the required image and sound files from the program directory. Please make sure that there exist two folders named \'images\' and \'sounds\' in the program directory. In case the files exist there and still this error is seen, please run this game as Administrator!");
		exit(EXIT_FAILURE);
    }
}
/******************************************************************************/

/*######## SET INITIAL VALUES OF VARIABLES ################*/
void set_initial_values()
{
    player1.x = 30; // player 1 x position
    player1.y = 250;// player 1 y position
    player1.angle = 0;//player 1 orientation angle
    player1.score = 0;//player 1 score
    player2.x = 936;//player2 x position
    player2.y = 250;//player 2 y position
    player2.angle = 0;//player 2 orintation angle
    player2.score = 0;//player 2 score
    cock.x = 497;//cock x position
    cock.y= 250;//cock y position
    cock.move_x = 0;//cock's range of movement in x direction
    cock.move_y = 0;//cock's range of movement in y direction
    cock.angle = 0;//cock's rotation angle
    cock.deflector = 0;//cock's angle deflector variable


}
/***********************************************************/
