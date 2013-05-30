/*
includes 
the header files,
 definitions,
 global variables and game state varibles declaration,
 BITMAP and SOUND variables declaration,
 struct variable declaration for cock and bats,
 function prototypes,
 Allegro's specific function for speed maintenance

*/
#include <allegro.h>
#include <math.h>


#define false 0
#define true 1
#define _left 1
#define _right -1

#define multiplayer 2
#define singleplayer 1

#define game_graphics_mode GFX_AUTODETECT_WINDOWED
#define fullscreen_selected 1
#define resolution_high 1

int left_edge, right_edge;
int server = 0;
int player1_has_served = 0;
int player2_has_served = 0;
int serve_started = 0;
int reached_top;
int serve_turn;
int game_runs_as;

int i;
char name[2][20];

int player1_has_returned_cock = 0;
int player2_has_returned_cock = 0;

int endLine_left;
int endline_right;
          
/*##### BITMAP VARIABLES ####################*/
SAMPLE *select_sound;
SAMPLE *menu_sound;
SAMPLE *whistle_sound;
SAMPLE *returnL_sound;
SAMPLE *returnR_sound;

BITMAP *buffer;

BITMAP *scoreboard;
BITMAP *court;
BITMAP *bat1;
BITMAP *bat2;
BITMAP *pic_cock;
BITMAP *exit_image;
BITMAP *net;
BITMAP *hand1;
BITMAP *hand1_arm;

BITMAP *menu_buffer;
BITMAP *back;
BITMAP *list;
BITMAP *hand;
BITMAP *cursor;
BITMAP *about;

BITMAP *instruction;
BITMAP *choice;
BITMAP *game_mode;
BITMAP *options_back;

BITMAP *list_start;
BITMAP *list_instructions;
BITMAP *list_gameOptions;
BITMAP *list_aboutGame;

/**************************************/

/*##### STRUCTURES ###################*/
struct Player{
       int x;
       int y;
       int x_while_serving;
       int y_while_serving;
       int y_predicted;
       int power_while_serving;
       int angle;
       int score;
       int power;
} player1, player2;


struct Cock{
      int x;
      int y;
      int move_x;
      int move_y;
      int angle;
      int deflector;
      int speed_changer;
      int artificial_deviation1;
      int artificial_deviation2;
} cock;
/**************************************/

/*##### FUNCTION PROTOTYPES #########*/
/*****/ void welcome_screen();
    /*****/ void display_menu();
    /*****/ void menu_selectItem();
    /*****/ void choose_game();
    /*****/ void menu_selectStart();
    /*****/ void menu_selectInstructions();
    /*****/ void menu_selectGameOptions();
    /*****/ void customize_keyboard();
    /*****/ void menu_selectAboutGame();
    /*****/ void menu_selectExit();
    /*****/ int mouseinside();
    /*****/ void game_mode_choose();

/*****/ void run_game();
/*****/ void continue_game();
/*****/ void initialize_game();
/*****/ void set_initial_values();
/*****/ void load_images();
/*****/ void draw_court();
/*****/ void draw_buffer();
/*****/ void check_keyboard_entry();
/*****/ void control_bats();



/*****/ void play_menu_sound();
/*****/ void play_select_sound();
/*****/ void play_whistle_sound();
/*****/ void play_player1_return_sound();
/*****/ void play_player2_return_sound();

/*****/ void deinitialize_game();
/*****/ void display_exit_screen();

/*****/ void check_collision();
    /*****/ void check_net_cross();
    /*****/ int cock_reaches_player1();
    /*****/ int cock_reaches_player2();
    /*****/ int player1_check_hit();
    /*****/ int player2_check_hit();
    /*****/ void player1_return_cock();
    /*****/ void player2_return_cock();
    /*****/ void player1_drop_cock();
    /*****/ void player2_drop_cock();

/*****/ void update_cock_position();
/*****/ void draw_bats_and_cock();
/*****/ void draw_speed_meter();
/*****/ void game_over();
/*****/ void serve();
/*****/ void reset();
/*****/ void display_game_status();
/*************************************/

/*##### SPEED LIMITING TECHNIQUE #######*/
        volatile long speed_limit = 0;
        void speed_limiter(){
            speed_limit++;
        }
        END_OF_FUNCTION(speed_limiter);
/****************************************/
