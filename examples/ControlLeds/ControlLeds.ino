/*
	Main Object: Button Debounce & Actions Library
	Sub Object: Example-Sketch
	Author: Christoph Amon
	School: HTL 3 Rennweg
	Place: Austria, Vienna
	Date: 30.04.2016
	Version: v1.0.2-011

	Hardware needed:
		- one button
		- three LEDs
		- one 10k resistor
		- some jumper wires
		- one arduino board

	This example-sketch of the Button Library control 3 LEDs with one button.
	A single click turns LED 1 on/off, a double click controls LED 2 and a
	long click LED 3.
*/

#include <ButtonEvent.h>

const int buttonPin = 5; // pulldown button
const int debounceTime = 50;

Button button(buttonPin, debounceTime, Pulldown, NoInvert);

// extern leds
const int led1Pin = 8;
const int led2Pin = 9;
const int led3Pin = 10;

// functionality switch:
// true = update
// false = realtime
const bool enableUpdate = true;

bool state1, state2, state3; // led states
bool mode = 0; // change option demonstrations

void setup()
{
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  Serial.begin(9600);
  if (enableUpdate == true) Serial.println("----- Update Functionality -----");
  else if (enableUpdate == false) Serial.println("----- Real-Time Functionality -----");

  // single click max 300ms, double click min 100 & max 400ms between clicks, long click > 1500ms
  // for more infos look at time diagrams
  button.setParaClick(300, 100, 400, 1500);
}

void loop()
{
  if (enableUpdate == true) updateLoop();
  else if (enableUpdate == false) realtimeLoop();
}

// ----- Update Functionality -----
void updateLoop()
{
  button.updateButton();

  // demonstrate option 1
  if (mode == 0) {
    if (button.getSingle() == true) {
      state1 ^= 1; // toggle state (more infos of ^-Operator (XOR) at documents)
      mode = 1; // change to option 2 (demonstration)
      Serial.println("Single click: toggle LED 1.");
    }
    else if (button.getDouble() == true) {
      state2 ^= 1;
      mode = 1;
      Serial.println("Double click: toggle LED 2.");
    }
    else if (button.getLong() == true) {
      state3 ^= 1;
      mode = 1;
      Serial.println("Long click: toggle LED 3.");
    }
  }
  // demonstrate option 2
  else if (mode == 1) {
    switch (button.getAction()) {
      case SingleClick:
        state1 ^= 1;
        mode = 0;
        Serial.println("Single click: toggle LED 1.");
        break;
      case DoubleClick:
        state2 ^= 1;
        mode = 0;
        Serial.println("Double click: toggle LED 2.");
        break;
      case LongClick:
        state3 ^= 1;
        mode = 0;
        Serial.println("Long click: toggle LED 3.");
        break;
    }
  }

  // write leds
  digitalWrite(led1Pin, state1);
  digitalWrite(led2Pin, state2);
  digitalWrite(led3Pin, state3);
}

// ----- Real-Time Functionality -----
void realtimeLoop()
{
  // demonstrate option 1
  if (mode == 0) {
    if (button.readSingle() == true) {
      state1 ^= 1; // toggle state
      mode = 1;
      Serial.println("Single click: toggle LED 1.");
    }
    else if (button.readDouble() == true) {
      state2 ^= 1;
      mode = 1;
      Serial.println("Double click: toggle LED 2.");
    }
    else if (button.readLong() == true) {
      state3 ^= 1;
      mode = 1;
      Serial.println("Long click: toggle LED 3.");
    }
  }

  // demonstrate option 2
  else if (mode == 1) {
    switch (button.readAction()) {
      case SingleClick:
        state1 ^= 1;
        mode = 0;
        Serial.println("Single click: toggle LED 1.");
        break;
      case DoubleClick:
        state2 ^= 1;
        mode = 0;
        Serial.println("Double click: toggle LED 2.");
        break;
      case LongClick:
        state3 ^= 1;
        mode = 0;
        Serial.println("Long click: toggle LED 3.");
        break;
    }
  }

  // write leds
  digitalWrite(led1Pin, state1);
  digitalWrite(led2Pin, state2);
  digitalWrite(led3Pin, state3);
}
