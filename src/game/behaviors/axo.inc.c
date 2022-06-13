extern u8 totwc_dl_canvas_i4[];

void bhv_axo_controller_loop(void) {
    gMarioState->vel[2] = 0;
    gMarioState->pos[2] = 0;

    if (
        gMarioState->pos[0] >= -400.0f &&
        gMarioState->pos[0] <= 400.0f &&
        gMarioState->pos[1] >= 1000.0f &&
        gMarioState->pos[1] <= 1600.0f &&
        gPlayer1Controller->buttonDown & R_TRIG
    ) {
        u8 *image = segmented_to_virtual(totwc_dl_canvas_i4);
        s16 marioImageX = (s16)((gMarioState->pos[0] + 400) * 0.1075f);
        s16 marioImageY = (s16)((gMarioState->pos[1] - 1000) * 0.106667f);

        u8 pixel = marioImageY % 2 == 0 ? 0x0F : 0xF0;
        image[32 * marioImageX + (marioImageY / 2)] = pixel;
    }
    if (gPlayer1Controller->buttonPressed & L_TRIG) {
        u8 *image = segmented_to_virtual(totwc_dl_canvas_i4);
        u16 i;
        for (i = 0; i < 2752; i++) {
            image[i] = 0xFF;
        }
    }
}