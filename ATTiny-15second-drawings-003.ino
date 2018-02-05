// Based on Adafruit's goggle sketch - https://learn.adafruit.com/kaleidoscope-eyes-neopixel-led-goggles-trinket-gemma/software
// If anyone reads this and can figure out a way to save about 500 bytes, I'd love to be able to put this into an ATTiny45 rather than an ATTiny85 :)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

//  Define pins
#define LED 0
#define BUZZER 1

//  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED, NEO_GRB + NEO_KHZ800);

//  Set Variables
byte brightness        = 255;      //  BURN ALL THE THINGS
int buzzerTone      = 3000;     //  Hz for tone
byte buzzerDelay       = 255;      //  Number of ms on and off
bool buzzertap        = true;     //  Only if true...

void setup() {
  //  Output single Neopixel
  pinMode(LED, OUTPUT);  //  Neopixels
  //  Output buzzer
  pinMode(BUZZER, OUTPUT);  //  Buzzer
  //  Start the Neopixel awesomeness
  pixels.begin();
  pixels.setBrightness(brightness); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (buzzertap == true)  //  So that this runs only the very first time
    {
    buzzertap = false;  //  Now it will not trigger again
    //  Amber Light
    for (int i=0; i<3; i++)
      {
      changeColor(0, 1000);
      tone(BUZZER, buzzerTone); // Send sound signal...
      changeColor(3, 250);
      noTone(BUZZER);     // Stop sound...
      }
    tone(BUZZER, buzzerTone-500); // Send sound signal...
    //  Green
    changeColor(1, 750);
    noTone(BUZZER);     // Stop sound...
    delay(13250);
    //  Yellow
    changeColor(0, 1000);
    //  Red + Buzzer
    changeColor(2, 100);
    //  Buzzer!!!
    for (int i=0; i < 3; i++)
      {
      tone(BUZZER, buzzerTone/3); // Send sound signal...
      delay(buzzerDelay);        // ...for 1 sec
      tone(BUZZER, buzzerTone/2); // Send sound signal...
      delay(buzzerDelay);        // ...for 1sec
      }
    noTone(BUZZER);     // Stop sound...
    }
}

void changeColor(byte colors, int delayTimer)
  {
  if (colors == 0)  { pixels.setPixelColor(LED, 255, 100, 0); }
  else if (colors == 1)  { pixels.setPixelColor(LED, 0, 255, 0); }
  else if (colors == 2)  { pixels.setPixelColor(LED, 255, 0, 0); }
  else { pixels.setPixelColor(LED, 0); }

  pixels.show();
  delay(delayTimer);
  }
