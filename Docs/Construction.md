# Mark In A Box Construction

# Features / Look and Feel

The intention of this box was to make it as unassuming and dead simple to operate.  As this was a memorial to a rather unique person, it meant to have an element of surprise and not try to give away the bit before the user would interact with it.  To that, the construction is meant to be clean in design with just a box, a button and a label.

I wanted a way have the code really not care about the file name convention for the audio files.  At startup, I wanted it to just go out and count the files in the root directory and then play a random file number when the button was pushed.  I also wanted it to play one cut when powered up to have confidence that the box was working.

The box design was one that happened to be handy in the studio space I was using but ended up being perfect for the application.  It is a six-sided box, almost cylindar in design.  In painting it gold, it has a bit of a "urn" look to it.  I am going to skip how to build a six sided box in this document.  You can look for multi-sided glue joints router bits.

The box really shouldn't be opened by the person interactiving with it.  This gave me a bit of latitude in not worrying about what the inside looks like.  It also gave me a way to make a closed box speaker enclosure (see: http://audiojudgement.com/sealed-enclosure-closed-box). I think having the audio come from the box is important to have some of the effects I wanted.

# Parts List

1. The box. Not going to go into detail here.  Come up with your own design.  If you use my design in having the speaker face downward, you will need feet or some spacer to not have the bottom of the box sit directly on a table surface.
2. Arduino Mega 
   https://store.arduino.cc/usa/mega-2560-r3
3. Audio shield with an amplifier such as the Adafruit Music Maker MP3 Shield for Arduino w/3W Stereo Amp
   https://www.adafruit.com/product/1788
4. A speaker or two. They should be able to handle the power the amp(s) produce.  
   https://www.adafruit.com/product/3968
5. SD card to hold the audio files to play back.  This will plug into the audio shield.
6. A button.  I got this kinda slick button made by Ulincos.  The model is U16B1.  This is a Normally Open (N/O) switch with a nice clean look with nifty blue LED ring.
   https://www.amazon.com/Ulincos-Momentary-Pushbutton-Stainless-Suitable/dp/B01G00GHQY
7. A power supply jack
8. A 5VDC power supply with a plug that will mate with the jack.

# Construction


