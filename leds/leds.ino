#include <Adafruit_NeoPixel.h>
//Led Settings
#define PIN 6
#define NUMPIXELS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//Light Sensor Pin
#define LIGHTSENSOR A0
//Swicth pin
#define SWITCH 2

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH, INPUT);
  pixels.begin();
}

void loop() {

  int lightIN = analogRead(LIGHTSENSOR); // Range [0,1023]
  int switchIN = digitalRead(SWITCH); // Digital Switch 0 and 1
  int stateS, previous;
  
  //Tests for the modules
  /*Serial.println(lightIN);
  Serial.print("Switch status - ");
  Serial.println(switchIN);
  Serial.print("State - " );
  Serial.println(stateS);*/
  // IF stateS == 1 - The leds get turn on if the sensor receive little light
  // IF stateS == 0 - The leds get turn on if the sensor receive a lot of light
  
  if(switchIN == 1 && previous == 0) {
    if(stateS == 1)
      stateS = 0;
    else 
      stateS = 1;
    previous = switchIN;
  }
    
  if(stateS == 1){
    if(lightIN > 500)
      turnonLeds();
    else
      clearLeds();
  } 
  if(stateS == 0) {
    if(lightIN < 500)
      turnonLeds();
    else
      clearLeds();
  }
      
  delay(10000);
}

//This function makes raimbow
//Function copy from strandtest of Adafruit Lib examples
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void clearLeds() {

  for(int i=0;i<NUMPIXELS;i++) {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
  }
}

void turnonLeds() {

  for(int i=0; i< NUMPIXELS; i++) {
    pixels.setPixelColor(i, Wheel(((i * 256 / NUMPIXELS)) & 255));
    pixels.show();
    delay(1000);
  }
}

