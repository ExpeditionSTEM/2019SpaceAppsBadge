
////////////////////////////////////////////////////////////////
//////////  2019 SPACE APPS HUNTSVILLE - PCB BADGE DEMO CODE - BY ANDREW DENIO 
////////////////////////////////////////////////////////////////

/*
  THIS CODE WAS USED TO DEMO THE BADGE FOR 2019 SPACE APPS CHALLENGE EVENT IN HUNTSVILLE.

  ALL LIBRARIES FOR COMPONENTS WILL BE INCLUDED IN GITHUB LINK, SO FEEL FREE TO TINKER AROUND!
  https://github.com/ExpeditionSTEM/2019SpaceAppsBadge

  LIBRARIES FOR NEOPIXELS WERE DERIVED FROM LIBRARIES BY ADAFRUIT

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
  
 */


////////////////////////////////////////////////////////////////
//////////  ATTINY 85 PINOUT
////////////////////////////////////////////////////////////////

 
/*
  
  GND - BATTERY NEGATIVE TERMINAL
  VCC - BATTERY POSITIVE TERMINAL
  PBO - I2C BUS - SDA
  PB1 - NEOPIXEL OUT
  PB2 - I2C BUS - SCL
  PB3 - BUTTON INPUT
  PB4 - LIGHT SENSOR INPUT
  PB5 - RESET BUTTON
  
 */


////////////////////////////////////////////////////////////////
//////////  VARIABLES AND LIBRARIES
////////////////////////////////////////////////////////////////

#include "TinyWireM.h" // USED FOR I2C CAPABILITIES
#include "TinyOzOLED.h" // USED FOR THE SSD1306 OLED SCREEN

#include <tinyNeoPixel_Static.h>  // USED FOR NEOPIXELS
#define PIN 1
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// Parameter 4 = array to store pixel data in      
#define NUMPIXELS 10
// Since this is for the static version of the library, we need to supply the pixel array
// This saves space by eliminating use of malloc() and free(), and makes the RAM used for
// the frame buffer show up when the sketch is compiled.
byte pixels[NUMPIXELS * 3];
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values. Finally, for the 4th argument we pass the array we
// defined above.
tinyNeoPixel strip = tinyNeoPixel(NUMPIXELS, PIN, NEO_GRB, pixels);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#define BUTTON_PIN   3    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

                          

#define LIGHT_SENSOR_PIN A2  // THIS IS PB4, BUT MUST LABEL IT A2 IN ORDER FOR THE ANALOG FUNCTIONS TO WORK
int lightSensorValue = 0;



//THIS IS THE BITMAP OUTPUT TO DISPLAY THE SPACE APPS LOGO ON STARTUP
const unsigned char spaceapps [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0x18, 0x08, 0x0C,
0x08, 0x38, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF0, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x18,
0x08, 0x0C, 0x08, 0x18, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF8, 0xF8, 0xE0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF0, 0xC0, 0x00, 0x00,
0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0x08,
0x08, 0x08, 0x18, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x3F, 0xE0, 0xC0, 0x80,
0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x7F, 0x00,
0x00, 0x00, 0x00, 0xE0, 0xFF, 0x01, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x03, 0x01, 0xFF, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xFF, 0x3F, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xFF, 0x06, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0xC0,
0x80, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x01, 0x03,
0x07, 0x1C, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x03, 0x00, 0x00, 0x01, 0xFF,
0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00,
0x01, 0x03, 0x0E, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3F, 0x30, 0x20, 0x20,
0x20, 0x38, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x38, 0x3F, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x30,
0x20, 0x60, 0x20, 0x30, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3F, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03,
0x3F, 0x30, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x38, 0x20,
0x20, 0x20, 0x30, 0x3F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//THIS IS THE BITMAP OUTPUT TO DISPLAY THE NASA WORM LOGO DURING MENU 
const unsigned char nasabitmap [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xF0,
0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0x03, 0x01, 0x01, 0x01, 0x0F, 0xFF, 0xFF,
0xFE, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0xE0, 0xFC, 0xFF, 0xFF, 0x1F, 0x03, 0x01, 0x01, 0x01, 0x0F, 0x7F, 0xFF, 0xFF, 0xF8, 0xC0, 0x00,
0x00, 0x00, 0x7E, 0xFF, 0xFF, 0xFF, 0xC3, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0xC1, 0x81,
0x81, 0x81, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF8, 0xFF, 0xFF, 0x7F, 0x0F, 0x01, 0x01,
0x01, 0x03, 0x1F, 0xFF, 0xFF, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
0x7F, 0xFF, 0xFF, 0xF0, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xC0, 0xF8, 0xFF,
0xFF, 0x7F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1F, 0xFF, 0xFF, 0xFC,
0xE0, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
0x8F, 0xFF, 0xFF, 0xFE, 0x78, 0x00, 0xE0, 0xFC, 0xFF, 0xFF, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0x3F, 0xFF, 0xFF, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x03, 0x07, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x03, 0x00, 0x0C, 0x0F, 0x0F, 0x0F,
0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x07, 0x07, 0x03, 0x01, 0x08, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x0F, 0x0F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// MENU VARIABLES
int NewMenuVar = 1;
int MenuCount = 9;
int OldMenuVar = MenuCount + 1; 

// BUTTON VARIABLES
bool newState;
bool oldState = HIGH;


////////////////////////////////////////////////////////////////
//////////  SETUP LOOP
////////////////////////////////////////////////////////////////

void setup() {

  //Initialize pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(PIN,OUTPUT); //set pin output - this is not done internally by the library for Static version of library

  //Start Neopixels
  //strip.begin(); //Static version does not use this.
  strip.show(); // Initialize all pixels to 'off'

  //Start Screen.  Some of these settings are to get the screen in the right orientation.
  OzOled.init();                 
  OzOled.clearDisplay(); 
  OzOled.setNormalDisplay();  
  OzOled.sendCommand(0xA1);
  OzOled.sendCommand(0xC8);
  OzOled.setHorizontalMode(); 
  OzOled.setBrightness(255);    

  //Draw the SPACE APPS logo
  OzOled.drawBitmap(spaceapps, 0, 0, 16, 8);

  delay(1000);

  OzOled.clearDisplay();  
}


////////////////////////////////////////////////////////////////
//////////  MAIN LOOP
////////////////////////////////////////////////////////////////

void loop() {

  // Check the button for activity
  DoButton();

  // Change the menu if button has been pushed
  MenuChange();

  //Reinitialize menu variables
  OldMenuVar = NewMenuVar;

}


////////////////////////////////////////////////////////////////
//////////  OTHER FUNCTIONS
////////////////////////////////////////////////////////////////


void DoButton(){

    // Get current button state.
  newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      NewMenuVar = OldMenuVar + 1;
      OzOled.clearDisplay();  
    }
    else {
      NewMenuVar = OldMenuVar;
    }
    if (NewMenuVar == MenuCount+1) {
       NewMenuVar = 1;
       }      
  }

  // Set the last button state to the old state.
  oldState = newState;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuChange() {
  
         if (NewMenuVar == MenuCount+1) {
              NewMenuVar = 1;
             }
         
         if (NewMenuVar == 0) {
            NewMenuVar = MenuCount;
          }
      
        if (NewMenuVar == 1)
          {
              OzOled.setCursorXY(0,0);   
              OzOled.printString(" MAIN MENU");  
              OzOled.setCursorXY(0,2);  
              OzOled.printString(" PRESS BUTTON TO ");  
              OzOled.setCursorXY(0,3);  
              OzOled.printString(" TEST COMPONENTS "); 
              //rainbow(20);
          } 
        else if (NewMenuVar == 2)
          {
            if (newState == LOW){
              OzOled.setCursorXY(0,2);   
              OzOled.printString(" SHOWING BITMAP ");
              delay(1000);
            }
            else {
              //OzOled.setCursorXY(0,0);   
              //OzOled.printString(" HIGH ");
              showBitmap();
            }
          }     
        else if (NewMenuVar == 3)
          {
            showLightSensor();
          }  
         else if (NewMenuVar == 4)
          {
            OzOled.setCursorXY(0,0);   
            OzOled.printString(" NEOPIXEL ");
            OzOled.setCursorXY(0,2);   
            OzOled.printString(" COLOR WIPE ");
            if (newState == LOW){
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              colorWipe(strip.Color(255, 0, 0), 50);  // Red
              colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
              colorWipe(strip.Color(0, 255, 0), 50);  // Green
              colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
              colorWipe(strip.Color(0, 0, 255), 50);  // Blue
              colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
              colorWipe(strip.Color(255, 255, 255), 50);  // Blue
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
            }
            else {
              colorWipe(strip.Color(0, 0, 0), 0); //off
            }
          }                 
          else if (NewMenuVar == 5)
          {
            OzOled.setCursorXY(0,0);   
            OzOled.printString(" NEOPIXEL ");
            OzOled.setCursorXY(0,2);   
            OzOled.printString(" THEATER CHASE ");
            if (newState == LOW){
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              theaterChase(strip.Color(127, 127, 127), 50); // White
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              theaterChase(strip.Color(127,   0,   0), 50); // Red
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              theaterChase(strip.Color(  0,   0, 127), 50); // Blue
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
            }
            else {
              colorWipe(strip.Color(0, 0, 0), 0); //off
            }
          }   
          else if (NewMenuVar == 6)
          {
            OzOled.setCursorXY(0,0);   
            OzOled.printString(" NEOPIXEL ");
            OzOled.setCursorXY(0,2);   
            OzOled.printString(" RAINBOW ");
            if (newState == LOW){
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              rainbow(20);
            }
            else {
              colorWipe(strip.Color(0, 0, 0), 0); //off
            }
          }
          else if (NewMenuVar == 7)
          {
            OzOled.setCursorXY(0,0);   
            OzOled.printString(" NEOPIXEL ");
            OzOled.setCursorXY(0,2);   
            OzOled.printString(" RAINBOW CYCLE ");
            if (newState == LOW){
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              rainbowCycle(20);
            }
            else {
              colorWipe(strip.Color(0, 0, 0), 0); //off
            }
          }  
          else if (NewMenuVar == 8)
          {
            OzOled.setCursorXY(0,0);   
            OzOled.printString(" NEOPIXEL ");
            OzOled.setCursorXY(0,2);   
            OzOled.printString(" THEATER CHASE ");
            OzOled.setCursorXY(0,3);   
            OzOled.printString(" RAINBOW ");
            if (newState == LOW){
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              theaterChaseRainbow(50);
            }
            else {
              colorWipe(strip.Color(0, 0, 0), 0); //off
            }
          }
          else if (NewMenuVar == 9)
          {
            //showLightSensor();
            OzOled.setCursorXY(0,0);   
            OzOled.printString(" NEOPIXEL ");
            OzOled.setCursorXY(0,2);   
            OzOled.printString(" SHOW MODE ");
            showMode(1000);
          }                      
           else 
              {
               // OnOffBool1 = 0;
              }  

  //delay(100);        
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showLightSensor(){
  lightSensorValue = analogRead(LIGHT_SENSOR_PIN);
    
  OzOled.setCursorXY(0,0);   
  OzOled.printString("LIGHT SENSOR");  
  OzOled.printString("VALUE",0,1.2);  
 //OzOled.setCursorXY(0,2);  
  OzOled.printNumber(long(lightSensorValue), 0, 3); 
  OzOled.printString("    "); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showBitmap(){
  OzOled.drawBitmap(nasabitmap, 0, 0, 16, 8);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
            break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
            break;
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Theatre-style crawling lights with rainbow effect
void showMode(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      delay(wait);
      
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
