#include <Arduino.h>
#include <Wire.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

static const uint8_t PIN_MP3_TX = 11; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 10; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

DFRobotDFPlayerMini player;

int x = 0;
int lastX = 0;
const int volume = 15;

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  softwareSerial.begin(9600);
}

void loop()
{
  delay(100);
    if (x == 1 && lastX == 0)
  {
    operateSpeaker();
    Serial.println("operating speakers...");
  }
  lastX = x;
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{

  while (1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);      // print the character
  }
  x = Wire.read(); // receive byte as an integer
  Serial.println(x);
}

void operateSpeaker()
{
  if (player.begin(softwareSerial))
  {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(volume);
    // Play the first MP3 file on the SD card
    player.play(1);
  }
  else
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}
