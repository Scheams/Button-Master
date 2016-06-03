/*
	Main Object: Button Debounce & Actions Library
	Sub Object: Debounce C++
	Author: Christoph Amon
	School: HTL 3 Rennweg
	Place: Austria, Vienna
	Date: 30.04.2016
	Version: v1.0.2-014
*/

#include "Debounce.h"

void Debounce::edge() {
	// if input is low
	if (!readState()) {
		// if state changed (fallen)
		if (READ_DEB(PS)) {
			SET_DEB(FS);
			CLEAR_DEB(PS);
		}
	}
	// if inut is high & state changed (rosen)
	else if (!READ_DEB(PS)) {
		SET_DEB(RS);
		SET_DEB(PS);
	}
}

void Debounce::state(){
	// set (inverted) state bit
	if (READ_DEB(IM)) mRegister ^= (-(!digitalRead(mButtonPin)) ^ mRegister) & _BV(CS);
  	else mRegister ^= (-digitalRead(mButtonPin) ^ mRegister) & _BV(CS);

  	// wait for/set debounced state
  	if ((READ_DEB(CS) != READ_DEB(DS)) && (millis() - mPrev >= mDebounce)) {
  		mRegister ^= (-((bool)(READ_DEB(CS))) ^ mRegister) & _BV(DS);
  		mPrev = millis();
 	}
 	else if (READ_DEB(DS) == READ_DEB(CS)) mPrev = millis();
}

Debounce::Debounce(){ }

Debounce::Debounce(uint8_t ButtonPin, uint8_t debounceTime){
	// setup debounce
	mDebounce = debounceTime;
	mButtonPin = ButtonPin;
	mRegister = 0;
}

Debounce::Debounce(uint8_t ButtonPin, uint8_t debounceTime, uint8_t buttonMode, bool invertMode){
	mDebounce = debounceTime;
	mButtonPin = ButtonPin;

	// setup modes
	mRegister = invertMode ? (mRegister | _BV(IM)) : 0;
	switch(buttonMode){
		case NoMode:
			break;
		case Pulldown:
			pinMode(mButtonPin, INPUT);
			break;
		case Pullup:
			pinMode(mButtonPin, INPUT);
			break;
		case InternPullup:
			pinMode(mButtonPin, INPUT_PULLUP);
			break;
		default:
			break;
	}
}

void Debounce::setDebounce(uint16_t debounceTime)
{
	// set new debounce time
	mDebounce = debounceTime;
}

bool Debounce::readState(){
	state();
 	return READ_DEB(DS);
}


bool Debounce::readRise(){
	edge();
	if (!(READ_DEB(RS))) return 0;
	else {
		mRegister &= ~_BV(RS);
		return 1;
	}
}

bool Debounce::readFall(){
	edge();
	if (!(READ_DEB(FS))) return 0;
	else {
		mRegister &= ~_BV(FS);
		return 1;
	}
}

bool Debounce::readChange(){
	edge();
	if (readRise())	return 1;
	else if (readFall()) return 1;
	else return 0;
}

void Debounce::updateBounce(){
	// reset bit mask
	mRegister &= ~(_BV(RS) | _BV(FS));
	state();
	edge();
}

bool Debounce::getState(){
	return READ_DEB(DS);
}

bool Debounce::getRise(){
	return READ_DEB(RS);
}

bool Debounce::getFall(){
	return READ_DEB(FS);
}

bool Debounce::getChange(){
	return (READ_DEB(FS)) | (READ_DEB(RS));
}