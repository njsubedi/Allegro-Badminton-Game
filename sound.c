/*################### PLAY SOUNDS IN GAME #################################*/

 void play_menu_sound()
    {

    int panning = 100;
    int pitch = 1000;
    int volume = 100;
    //play the sample with looping
    play_sample(menu_sound, volume, panning, pitch, TRUE);
}
 void play_select_sound()
    {

        int panning = 100;
        int pitch = 1000;
        int volume = 200;
        //play the sample without looping
        play_sample(select_sound, volume, panning, pitch, FALSE);
    }
 void play_whistle_sound()
    {

        int panning = 100;
        int pitch = 1000;
        int volume = 400;
        //play the sample without looping
        play_sample(whistle_sound, volume, panning, pitch, FALSE);
    }
 void play_player1_return_sound()
    {

        int panning = 100;
        int pitch = 1000;
        int volume = 800;
        //play the sample without looping
        play_sample(returnL_sound, volume, panning, pitch, FALSE);
    }
 void play_player2_return_sound()
    {

        int panning = 100;
        int pitch = 1000;
        int volume = 800;
        //play the sample without looping
        play_sample(returnR_sound, volume, panning, pitch, FALSE);
    }
