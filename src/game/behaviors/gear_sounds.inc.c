void bhv_gear_sounds_loop() {
  if (o->oTimer == 60) {
        play_sound(SOUND_GENERAL2_ROTATING_BLOCK_CLICK, gGlobalSoundSource);
        o->oTimer = 0;
    }
}
