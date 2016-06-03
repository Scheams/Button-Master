/*
	Main Object: Button Debounce & Actions Library
	Sub Object: Example-Sketch
	Author: Christoph Amon
	School: HTL 3 Rennweg
	Place: Austria, Vienna
	Date: 26.04.2016
	Version: v1.0.2-011

	Hardware needed:
		- one button
		- one led (optional)
		- one 10k resistor
		- some jumper wires
		- one arduino board

	This example-sketch of the Button (Debounce) Library prints
	button informations on the serial monitor. Furthermore an extern/
	onboard led will be written to same state as the button state.
*/

#include <Debounce.h>

const int buttonPin = 5; // pulldown button
const int debounceTime = 50;

Debounce button(buttonPin, debounceTime, Pulldown, NoInvert);

const int ledPin = 8; // extern led (optional: change to 13 for onboard led)

// functionality switch:
// true = update
// false = realtime
const bool enableUpdate = true;

bool mode = 0; // change realtime option demonstrations

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  if (enableUpdate == true) Serial.println("----- Update Functionality -----");
  else if (enableUpdate == false) Serial.println("----- Real-Time Functionality -----");
}

void loop()
{
  if (enableUpdate == true) updateLoop();
  else if (enableUpdate == false) realtimeLoop();
}

void updateLoop()
{
  button.updateBounce();

  digitalWrite(ledPin, button.getState()); // write led same state as button
  if (button.getChange() == true) {
    Serial.print("Button state changed to ");
  }
  if (button.getRise() == true) {
    Serial.println("HIGH.");
  }
  else if (button.getFall() == true) {
    Serial.println("LOW.");
    Serial.println();
  }
}

void realtimeLoop()
{
  digitalWrite(13, button.readState()); // write led same state as button

  // demonstrate option 1
  if (mode == 0) {
    if (button.readRise() == true) {
      Serial.println("Button state changed to HIGH.");
    }
    else if (button.readFall() == true) {
      Serial.println("Button state changed to LOW.");
      Serial.println();
      mode = 1; // change demonstration
    }
  }

  // demonstrate option 2
  else if (mode == 1) {
    if (button.readChange() == true) {
      Serial.print("Button state changed to ");
      if (button.readState() == HIGH) {
        Serial.println("HIGH");
      }
      else if (button.readState() == LOW) {
        Serial.println("LOW");
        Serial.println();
        mode = 0; // change demonstration
      }
    }
  }
}
