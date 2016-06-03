/*
	Main Object: Button Debounce & Actions Library
	Sub Object: Debounce Header
	Author: Christoph Amon
	School: HTL 3 Rennweg
	Place: Austria, Vienna
	Date: 30.04.2016
	Version: v1.0.2-014
*/

#ifndef __DEBOUNCE_H_INCLUDED__
#define __DEBOUNCE_H_INCLUDED__

#include "Arduino.h"

// debounce bit mask
#define IM 		 		6 // invert mode
#define CS 		 		5 // current state
#define RV				4 // return value
#define PS 				3 // previous state
#define DS 		 		2 // debounced state
#define RS 	 			1 // rising state
#define FS 				0 // falling state

// bit mask funtions
#define READ_DEB(bit) (mRegister & _BV(bit))
#define SET_DEB(bit) (mRegister = mRegister | _BV(bit))
#define CLEAR_DEB(bit) (mRegister = mRegister & ~_BV(bit))

// input commands for modes
// invertMode
#define NoInvert 		0
#define Invert 			1

// buttonMode
#define NoMode 			0
#define Pulldown 		1
#define Pullup 			2
#define InternPullup 	3

class Debounce {

public:
	// constructor
	Debounce(); // default constructor
	Debounce(uint8_t buttonPin, uint8_t debounceTime); // constructor 1
	Debounce(uint8_t buttonPin, uint8_t debounceTime, uint8_t buttonMode, bool invertMode); // constructor 2

	void setDebounce(uint16_t debounceTime); // set new debounce value
	
	// real-time functions
	bool readState(); // read state
	bool readRise(); // read rising edge
	bool readFall(); // read falling edge
	bool readChange(); // read changing state

	// update functions
	void updateBounce(); // update all actions
	bool getState(); // get state
	bool getRise(); // get risen edge
	bool getFall(); // get fallen edge
	bool getChange(); // get changed state

private:
	// private timer
	uint32_t mPrev;
	// private variables
	uint8_t mRegister, mButtonPin;

	// private functions
	void edge();
	void state();

public:	
	// timer parameter
	uint16_t mDebounce;
};

#endif