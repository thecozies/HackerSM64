extern u8 totwc_dl_canvas_i4[];
extern u8 totwc_dl_reference_i4[];
extern u8 totwc_dl_safezone_i4[];
extern u8 totwc_dl_undostate_i4[];

void bhv_axo_controller_loop(void) {
    s16 i, j;
    u8 *canvas = segmented_to_virtual(totwc_dl_canvas_i4);
    u8 *reference = segmented_to_virtual(totwc_dl_reference_i4);
    u8 *safezone = segmented_to_virtual(totwc_dl_safezone_i4);
    u8 *undostate = segmented_to_virtual(totwc_dl_undostate_i4);

    gMarioState->vel[2] = 0;
    gMarioState->pos[2] = 0;

    if (gPlayer1Controller->buttonPressed & R_TRIG) {
        for (i = 0; i < 2752; i++) {
            undostate[i] = canvas[i];
        }
    }

    if (
        gMarioState->pos[0] >= -400.0f &&
        gMarioState->pos[0] <= 400.0f &&
        gMarioState->pos[1] >= 1000.0f &&
        gMarioState->pos[1] <= 1600.0f &&
        gPlayer1Controller->buttonDown & R_TRIG
    ) {
        s16 marioImageX = (s16)((gMarioState->pos[0] + 400) * 0.1075f);
        s16 marioImageY = (s16)((gMarioState->pos[1] - 1000) * 0.106667f);
        for (i = 0; i < 5; i++) {
            s16 pixelX = (marioImageX - 2) + i;
            if (pixelX >= 0 && pixelX < 86) {
                for (j = 0; j < 5; j++) {
                    s16 pixelY = marioImageY + j;
                    if (pixelY >= 0 && pixelY < 64) {
                        if (
                            !(
                                (i == 0 && j == 0) || 
                                (i == 0 && j == 4) || 
                                (i == 4 && j == 0) || 
                                (i == 4 && j == 4)
                            )
                        ) {
                            u8 pixelNibble = pixelY % 2 == 0 ? 0x0F : 0xF0;
                            canvas[32 * pixelX + (pixelY / 2)] &= pixelNibble;
                        }
                    }
                }
            }
        }
    }

    if (gPlayer1Controller->buttonPressed & L_TRIG) {
        for (i = 0; i < 2752; i++) {
            u8 redoByte = canvas[i];
            canvas[i] = undostate[i];
            undostate[i] = redoByte;
        }
    }

    if (gPlayer1Controller->buttonDown & L_TRIG) {
        if (o->oF4 >= 0) {
            o->oF4++;
            if (o->oF4 >= 90) {
                for (i = 0; i < 2752; i++) {
                    canvas[i] = 0xFF;
                    o->oF4 = -1;
                }
            }
        }
    }
    else {
        o->oF4 = 0;
    }

    s16 numWrong = 0;

    for (i = 0; i < 2752; i++) {
        for (j = 0; j < 2; j++) {
            u8 canvasPixel = canvas[i] & (0xF << (4 * j));
            u8 referencePixel = reference[i] & (0xF << (4 * j));
            if (canvasPixel != referencePixel) {
                if (referencePixel == 0xF) {
                    u8 safezonePixel = safezone[i] & (0xF << (4 * j));
                    if (safezonePixel == 0xF) {
                        numWrong++;
                    }
                }
                else {
                    numWrong++;
                }
            }
        }
    }

    f32 accuracy = 1.0f - (numWrong / 1190.0f);

    print_text_fmt_int(16, 224, "%d PERCENT", (s16)(accuracy * 100));
}