/*

 GLCD Pong
 
 This example for the Arduino GLCD reads the values 
 of 2 potentiometers to move a rectangular platform
 on the x and y axes. The platform can intersect 
 with a ball causing it to bounce. 
 
 This example code is in the public domain.
 
 Created by Tom Igoe December 2012
 Modified 15 April 2013 by Scott Fitzgerald
 
 http://arduino.cc/en/Tutorial/GLCDPong
 
 */
 
#include <Adafruit_GFX.h>    // Core graphics library
#include <Arduino_GLCD.h> // Hardware-specific library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8  

// pin definition for the Leonardo
// #define cs   7
// #define dc   0
// #define rst  1 

Arduino_GLCD LCDscreen = Arduino_GLCD(cs, dc, rst);

// variables for the position of the ball and paddle
int paddleX = 0;
int paddleY = 0;
int oldPaddleX, oldPaddleY;
int ballDirectionX = 1;
int ballDirectionY = 1;

int ballSpeed = 10; // lower numbers are faster

int ballX, ballY, oldBallX, oldBallY;

void setup() {
  // initialize the display
  LCDscreen.begin();
  // black background
  LCDscreen.background(0,0,0); 
}

void loop() {

  // save the width and height of the screen
  int myWidth = LCDscreen.width();
  int myHeight = LCDscreen.height();
  
  // map the paddle's location to the position of the potentiometers   
  paddleX = map(analogRead(A0), 512, -512, 0, myWidth) - 20/2; 
  paddleY = map(analogRead(A1), 512, -512, 0, myHeight) - 5/2; 
  
  // set the fill color to black and erase the previous 
  // position of the paddle if different from present
  LCDscreen.fill(0,0,0);

 if (oldPaddleX != paddleX || oldPaddleY != paddleY) {
    LCDscreen.rect(oldPaddleX, oldPaddleY, 20, 5);
  }

  // draw the paddle on screen, save the current position
  // as the previous.
  LCDscreen.fill(255,255,255);

  LCDscreen.rect(paddleX, paddleY, 20, 5);
  oldPaddleX = paddleX;
  oldPaddleY = paddleY;

  // update the ball's position and draw it on screen
  if (millis() % ballSpeed < 2) {
  moveBall();
  }
}

// this function determines the ball's position on screen
void moveBall() {
  // if the ball goes offscreen, reverse the direction:
 if (ballX > LCDscreen.width() || ballX < 0) {
   ballDirectionX = -ballDirectionX;
 }
 
  if (ballY > LCDscreen.height() || ballY < 0) {
   ballDirectionY = -ballDirectionY;
 }  
 
  // check if the ball and the paddle occupy the same space on screen
  if (inPaddle(ballX, ballY, paddleX, paddleY, 20, 5)) {
    ballDirectionX = -ballDirectionX;
    ballDirectionY = -ballDirectionY;
 }
 
 // update the ball's position
 ballX += ballDirectionX;
 ballY += ballDirectionY;
 
// erase the ball's previous position
 LCDscreen.fill(0,0,0);
 
  if (oldBallX != ballX || oldBallY != ballY) {
    LCDscreen.rect(oldBallX, oldBallY, 5, 5);
  }
  
  
  // draw the ball's current position
  LCDscreen.fill(255,255,255);
  LCDscreen.rect(ballX, ballY, 5, 5);
 
  oldBallX = ballX;
  oldBallY = ballY;
  
}

// this function checks the position of the ball
// to see if it intersects with the paddle
boolean inPaddle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight) {
  boolean result = false;
   
  if ((x >= rectX && x <= (rectX + rectWidth)) && 
      (y >= rectY && y <= (rectY + rectHeight))) {
       result = true; 
      }
 
return result;  
}


