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
		- one LED
		- one 10k resistor
		- some jumper wires
		- one arduino board

	This example-sketch of the Button Library controls the brightness
	of a led with one button.
	If the button gets pressed the brightness level increases slowly.
	After 1500ms the level increases faster.
	When the button is released, same process starts from begin.
*/

#include <ButtonEvent.h>

const int buttonPin = 5; // pulldown button
const int debounceTime = 50;

Button button(buttonPin, debounceTime, Pulldown, NoInvert);

const int ledPin = 8; // extern led on PWM-pin

// functionality switch:
// true = update
// false = realtime
const bool enableUpdate = true;

int value = 0;
int addValue = 1;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  if (enableUpdate == true) Serial.println("----- Update Functionality -----");
  else if (enableUpdate == false) Serial.println("----- Real-Time Functionality -----");

  button.setParaAdd(1500, 200, 10);
  // every 200ms value increments, after 1500ms: every 30ms value increments
  // for more infos look at time diagrams
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

  button.getAddCalc(value, addValue); // calculate value
  if (button.getAdd() == true) {  // if something got added
    Serial.print("Value was added: ");
    Serial.println(value);
  }
  if (value == 256) value = 0; // reset value if it is over 255
  analogWrite(ledPin, value); // write dimmed led
}

// ----- Real-Time Functionality -----
void realtimeLoop()
{
  // use this version with if:
  if (button.readAdd() == true) { // if add is active
    value += addValue; // calculate value
    Serial.print("Value was added: ");
    Serial.println(value);
  }

  // or only this function (without serial info):
  // button.readAddCalc(value, addValue);

  if (value == 256) value = 0; // reset value if it is 255
  analogWrite(ledPin, value); // write dimmed led
}
