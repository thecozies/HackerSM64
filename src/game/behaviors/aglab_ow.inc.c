void ow_ctl_init()
{
    gDoInertia = 1;
    gDoPlatformDisplacement = 1;
}

void ow_ctl_loop()
{
    if (gIsGravityFlipped)
    {
        gMarioStates->health = 0x880;
        if (0 == o->oTimer)
            seq_player_play_sequence(SEQ_PLAYER_LEVEL, 0, 0);

        if (30 == o->oTimer)
            seq_player_play_sequence(SEQ_PLAYER_LEVEL, SEQ_DUCKTALES, 0);

        if (o->oTimer > 120)
        {
            print_text_centered(160, 180, "GAME OVER");
            print_text_centered(160, 60, "PRESS L TO RESTART");
            if (gPlayer1Controller->buttonPressed & L_TRIG)
            {
                gIsGravityFlipped = 0;
                o->activeFlags = 0;
            }
        }

        if (gMarioStates->pos[1] < -6000.f)
        {
            gMarioStates->pos[1] = -6000.f;
        }
    }
}
