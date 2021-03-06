/*

 Esplora GLCD Graph
 
 This example for the Esplora with an Arduino GLCD reads 
 the value of the light sensor, and graphs the values on
 the screen.
 
 This example code is in the public domain.
 
 Created 15 April 2013 by Scott Fitzgerald
 
 http://arduino.cc/en/Tutorial/EsploraGLCDGraph
 
 */

#include <Esplora.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <GLCD.h> // Hardware-specific library
#include <SPI.h>

// position of the line on screen
int xPos = 0;

void setup(){

  // initialize the screen
  EsploraLCD.begin();

  // clear the screen with a nice color
  EsploraLCD.background(250,16,200); 
}

void loop(){

  // read the sensor value
  int sensor = Esplora.readLightSensor();
  // map the sensor value to the height of the screen
  int graphHeight = map(sensor,0,1023,0,EsploraLCD.height());

  // draw the line in a pretty color
  EsploraLCD.stroke(250,180,10);
  EsploraLCD.line(xPos, EsploraLCD.height() - graphHeight, xPos, EsploraLCD.height());

  // if the graph reaches the edge of the screen
  // erase it and start over from the other side
  if (xPos >= 160) {
    xPos = 0;
    EsploraLCD.background(250,16,200); 
  } 
  else {
    // increment the horizontal position:
    xPos++;
  }

  delay(16);
}
