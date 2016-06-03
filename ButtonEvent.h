/*
	Main Object: Button Debounce & Actions Library
	Sub Object: Example-Sketch
	Author: Christoph Amon
	School: HTL 3 Rennweg
	Place: Austria, Vienna
	Date: 30.04.2016
	Version: v1.0.2-014
*/

#ifndef __BUTTON_H_INCLUDED__
#define __BUTTON_H_INCLUDED__

#include "Debounce.h"

// click bit mask
#define A_C_MODE			7 // 0 == click mode, 1 == add mode;
#define ADD_C 				6
#define LONG_C 				5
#define DOUBLE_C 			4
#define SINGLE_C			3

// flags
#define ADD_F  				2
#define LOW_F			 	0
#define START_F				1
#define BETWEEN_F 			2
#define END_F				3

// bit functions
#define WRITE_A_C(Bool)	(mRegister = (mRegister & ~_BV(A_C_MODE)) | (Bool << A_C_MODE))
#define SET_F(flag)		(mRegister = ((mRegister & 0xFC) | flag))
#define READ_F 			(mRegister & 0x03)
#define SET_C(bit) 		(mRegister |= _BV(bit))
#define READ_C(bit) 	(mRegister & _BV(bit))
#define SET_ADD_F(flag) (mRegister = (mRegister & ~_BV(ADD_F)) | (flag << ADD_F))
#define READ_ADD_F 		(mRegister & _BV(ADD_F))
#define NEG_C 			(~(_BV(LONG_C) | _BV(DOUBLE_C) | _BV(SINGLE_C)))

// define action values
#define SingleClick 1
#define DoubleClick 2
#define LongClick 	3

class Button : public Debounce {

public:
	// constructor
	Button(); // default constructor
	Button(uint8_t buttonPin, uint8_t debounceTime); // Constructor 1
	Button(uint8_t buttonPin, uint8_t debounceTime, uint8_t buttonMode, bool invertMode); // Constructor 2

	// parameter functions
	void setParaStandard(); // set all parameters to standard
	void setParaClick(uint32_t singleTime, uint32_t minBetweenTime, uint32_t maxBetweenTime, uint32_t longTime); // setup click parameters
	void setParaAdd(uint32_t changeTime, uint32_t firstAddTime, uint32_t secondAddTime); // setup add parameters

	// real-time functions
	void updateButton(); // update all actions
	bool getSingle(); // get single click
	bool getDouble(); // get double click
	bool getLong(); // get long click
	uint8_t getAction(); // get single, double or long click (compare with action values)
	bool getAdd(); // get add click
	void getAddCalc(int16_t & value, int16_t increment); // get calculated value, if add click was done
	void getAddCalc(int16_t & value); // increment with 1

	// update functions
	bool readSingle(); // read single click
	bool readDouble(); // read double click
	bool readLong(); // read long click
	uint8_t readAction(); // read single, double or long click (compare with action values)
	bool readAdd(); // read add click
	void readAddCalc(int16_t & value, int16_t increment); // read calculated value, if add click was done
	void readAddCalc(int16_t & value); // increment with 1

private:
	// timer parameter
	uint32_t mLong_c, mSingle_c, mMinBetween_c, mMaxBetween_c, mChange_a, mSlow_a, mFast_a;
	// private timer
	uint32_t mTimer_c, mTimer_a, mNow, mDelay_a, mStart_a;
	// private variables
	uint8_t mRegister;
	bool mState;

	// private functions
	void getValues(); // get button state and time
	void click(); // update click bit mask
	void add(); // update add bit mask
};

#endif