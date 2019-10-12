/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
// Should review https://github.com/adafruit/Adafruit_Learning_System_Guides/blob/master/Gordon_Cole_MP3_Player/Gordon_Cole_MP3_Player.ino on what I can steal.

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
//#define CLK 13       // SPI Clock, shared with SD card
//#define MISO 12      // Input data, from VS1053/SD card
//#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

#define BUTTON 13     // the button is attached to this pin and goes to +5v

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

int totaltracknum = 0;
Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  // Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
char filename[99];
void setup() {
  // pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }

  // list files
  totaltracknum = numFiles(SD.open("/"), 0);
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(0,0);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  // Play one file, don't return until complete
  // Serial.println(F("Playing track 001"));
  // musicPlayer.playFullFile("/track001.mp3");
  // Play another file in the background, REQUIRES interrupts!
  // Serial.println(F("Playing track 002"));
  // musicPlayer.startPlayingFile("/track002.mp3");
}

void loop() {
  randomSeed(analogRead(0));
  playCutNum(SD.open("/"), 0, random(1,totaltracknum)); 
  // Serial.println(F("Playing track 001"));
  // musicPlayer.playFullFile("/track001.mp3");
  // File is playing in the background

  // if (musicPlayer.stopped()) {
    // Serial.println("Done playing track");
    // while (1) {
      // delay(10);  // we're done! do nothing...
    // }
  // }
  while (digitalRead(BUTTON) == LOW) {
    delay(10);  // we're waiting for a button push. do nothing...
  }
  if (Serial.available()) {
    char c = Serial.read();
    
    // if we get an 's' on the serial console, stop!
    if (c == 's') {
      musicPlayer.stopPlaying();
    }
    
    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (! musicPlayer.paused()) {
        Serial.println("Paused");
        musicPlayer.pausePlaying(true);
      } else { 
        Serial.println("Resumed");
        musicPlayer.pausePlaying(false);
      }
    }
  }
  delay(1000);
}
/// File listing helper
void printDirectory(File dir, int numTabs) {
   int i=0;
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     if (entry.isDirectory()) {
       // Serial.println("/");
       //  printDirectory(entry, numTabs+1);
     } else {
       if (entry.size() > 5000) {
         i++;
         Serial.print(entry.name());
         // files have sizes, directories do not
         Serial.print("\t");
         Serial.println(entry.size(), DEC);
         // musicPlayer.playFullFile(entry.name());
       }
     }
     entry.close();
   }
   return(i);
}
int numFiles(File dir, int numTabs) {
   int i=0;
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     if (entry.isDirectory()) {
       // Serial.println("/");
       //  printDirectory(entry, numTabs+1);
     } else {
       if (entry.size() > 5000) {
         i++;
         Serial.print(entry.name());
         // files have sizes, directories do not
         Serial.print("\t");
         Serial.println(entry.size(), DEC);
       }
     }
     entry.close();
   }
   Serial.print("Number of tracks = ");
   Serial.println(i);
   return(i);
}

void playCutNum(File dir, int numTabs, int cutnum) {
   int i=0;
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     if (entry.isDirectory()) {
       // Serial.println("/");
       //  printDirectory(entry, numTabs+1);
     } else {
       if (entry.size() > 5000) {
         i++;
         if (cutnum==i) {
           Serial.print(entry.name());
           // files have sizes, directories do not
           Serial.print("\t");
           Serial.println(entry.size(), DEC);
           musicPlayer.playFullFile(entry.name());
         }
       }
     }
     entry.close();
   }
}
