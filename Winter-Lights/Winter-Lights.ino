/*
 * Haiku Kitty
 * -- Eyes softly glow
 * -- When button is pressed, eyes brighten and kitty tells your fortune in Haiku form
 */
#include <WaveHC.h>
#include <WaveUtil.h>

#define HAIKU 49
#define GREETING 10

int greetingCounter;
int haikuCounter;

// TODO: Holding these globally is expensive. Not sure how else to do it
FatReader root;   // This holds the information for the volumes root directory
FatReader file;
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

enum lightMode {OFF, DIM, BRIGHT};
lightMode currentLightMode;

//////////////////////////////////// SETUP
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging  
  Serial.println(F("\nHello Kitty"));  // say we woke up!
  Serial.println(FreeRam());

  SdReader card;
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    Serial.println(F("Card init. failed!"));  // Something went wrong, lets print out why
  }
  
  // enable optimize read
  card.partialBlockRead(true);
  
  // This card has a FAT partition on 1
  FatVolume vol;
  vol.init(card, 1); 
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    Serial.println(F("Can't open root dir!"));      // Something went wrong,
  }

  // Initialize random seed for a different result each time
  randomSeed(analogRead(3));
  greetingCounter=random(GREETING);
  haikuCounter=random(HAIKU);
  
  // Start by purring
  forcePlay(PSTR("purr1.WAV"));

  // Start with lights dim
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT);
  switchLight(DIM);

  // make the pushbutton's pin an input:
  pinMode(0, INPUT);

  delay(2000); // Let this go for a few seconds before looping

}

//////////////////////////////////// LOOP
void loop() {

  if (buttonDepressed()) {
    switchLight(BRIGHT);
    nextGreeting();
    playblink(PSTR("DATA.wav"));
    switchLight(BRIGHT);
    nextHaiku();
    playblink(PSTR("END.wav"));
    switchLight(DIM);
    // Delay a couple of seconds and purr again
    delay(1500);
    forcePlay(PSTR("purr1.WAV"));
  }
 
  playAgainIfComplete();    

  // Delay 100ms and start again
  delay(100);
  
}

/////////////////////////////////// INITIALIZE

// Convenient way to get character for index
char charForIndex[] =  {'0', '1', '2', '3', '4', '5', '6', 
      '7', '8', '9'}; 
      
void playHaiku(int num) {
  char name[11];
  
  // copy flash string to RAM
  strcpy_P(name, PSTR("HAIKUxx.WAV"));
  
  name[5] = charForIndex[(num+1)/10];
  name[6] = charForIndex[(num+1)%10];

  Serial.println(name);
 
  playcomplete(name);
}

void playGreeting(int num) {
  char name[11];
  // copy flash string to RAM
  strcpy_P(name, PSTR("GREETxx.WAV"));
  
  name[5] = charForIndex[(num+1)/10];
  name[6] = charForIndex[(num+1)%10];

  Serial.println(name);
 
  playcomplete(name);  
}

/////////////////////////////////// HELPERS

// Pass back true if the button is depressed
bool buttonDepressed() {
  int buttonState = digitalRead(0);
  return buttonState == 0;
}

void randomHaiku() {
  int number = random(HAIKU);
  playHaiku(number); 
}

void nextHaiku() {
  playHaiku(haikuCounter);
  haikuCounter++;
  if (haikuCounter == HAIKU) {
    haikuCounter = 0; 
  }
}

void nextGreeting() {
  playGreeting(greetingCounter);
  greetingCounter++;
  if (greetingCounter == GREETING) {
    greetingCounter = 0; 
  }
}



