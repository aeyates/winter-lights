char filename[13];

/**
 * Force the file to play, stopping whatever is playing. 
 * Pass the name of the file. It will be copied into flash for you.
 */
void forcePlay(char* name) {
  strcpy_P(filename, name);
  playfile(filename);
}

/*
 * Force a file to play and wait for it to complete.
 * Pass the name already copied into flash.
 */
void playcomplete(char *name) {
  playfile(name);
  while (wave.isplaying) {
  }
}


/*
 * Force a file to play and wait for it to complete, flashing lights while playing.
 * Pass the name of the file. It will be copied into flash for you.
 */
void playblink(char *name) {
  strcpy_P(filename, name);
  playfile(filename);
  while (wave.isplaying) {
    switchLight(DIM);
    delay(500);
    switchLight(BRIGHT);
    delay(500);
  }
}

/*
 * Play a file again only if the previous is complete.
 * Pass the name of the file. It will be copied into flash for you.
 */
void playAgainIfComplete() {
  if (!wave.isplaying) {
    Serial.println("Song complete. Play again.");
    wave.seek(0);
    wave.play();
  }  
}

/*
 * Play a file, stopping what is already playing. This method is used
 * internally and expects the name to be in flash.
 */
void playfile(char *name) {
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  if (!file.open(root, name)) {
    PgmPrint("Couldn't open file ");
    Serial.print(name); 
    return;
  }
  if (!wave.create(file)) {
    PgmPrintln("Not a valid WAV");
    return;
  }
  // ok time to play!
  wave.play();
}

