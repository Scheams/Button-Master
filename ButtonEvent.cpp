/*
	Main Object: Button Debounce & Actions Library
	Sub Object: ButtonActions C++
	Author: Christoph Amon
	School: HTL 3 Rennweg
	Place: Austria, Vienna
	Date: 30.04.2016
	Version: v1.0.2-014
*/

#include "ButtonEvent.h"

void Button::getValues() // get button state and time
{
	mState = readState();
	mNow = millis();
}

void Button::click() // get new actions, save in bit mask
{
	// if input is high
	if (mState) {
		// start
		if (READ_F == LOW_F){
			mTimer_c = mNow;
			SET_F(START_F);
		}
		// long click done
		else if ((READ_F == START_F) && (mNow - mTimer_c > mLong_c)){
			SET_F(BETWEEN_F);
			SET_C(LONG_C);
		}
	    // double click done
		else if ((READ_F == END_F) && (mMinBetween_c < (mNow - mTimer_c)) && ((mNow - mTimer_c) < mMaxBetween_c)) {
			SET_F(BETWEEN_F);
			SET_C(DOUBLE_C);
		}
	}
	// not high during low phase
	else if (READ_F == LOW_F);
	// if input is low
	else {
		// first single click too long
		if ((READ_F == START_F) && (mNow - mTimer_c > mSingle_c)){
			SET_F(LOW_F);
		}
		// first single click
		else if (READ_F == START_F){
			mTimer_c = mNow;
			SET_F(END_F);
		}
		// hold click (after long & double) finished
		else if (READ_F == BETWEEN_F) SET_F(LOW_F);
		// no double click, single click done
		else if ((READ_F == END_F) && ((mNow - mTimer_c) > mMaxBetween_c)){
			SET_F(LOW_F);
			SET_C(SINGLE_C);
		}
	}
}

void Button::add()
{
	// reset add bit
	mRegister &= ~_BV(ADD_C);
	// if input is high
	if (mState) {
    	// add value
		if (READ_ADD_F && mNow - mTimer_a > mDelay_a) {
			mTimer_a = mNow;
			SET_C(ADD_C);
		// fast add after change time
			if (mNow - mStart_a > mChange_a) mDelay_a = mFast_a;
		}
		// first loop
		else if (!READ_ADD_F) {
			mStart_a = mNow;
			mDelay_a = mSlow_a;
			SET_ADD_F(1);
		}
	}
	// if input is low, set 0
	else if (READ_ADD_F) {
		SET_ADD_F(0);
	}
}

Button::Button() { } // default constructor

Button::Button(uint8_t buttonPin, uint8_t debounceTime)
	:Debounce(buttonPin, debounceTime)
{
	// setup standard parameter
	setParaStandard();
}

Button::Button(uint8_t buttonPin, uint8_t debounceTime, uint8_t buttonMode, bool invertMode)
	:Debounce(buttonPin, debounceTime, buttonMode, invertMode) // setup debounce library
{
	// setup debounce library with standard parameter
	setParaStandard();
}

void Button::setParaStandard()
{
	mLong_c = 1000; mSingle_c = 400; mMaxBetween_c = 300; mMinBetween_c = 100;
	mChange_a = 1000; mSlow_a = 200; mFast_a = 20;
}

void Button::setParaClick(uint32_t single_c, uint32_t minBetween_c, uint32_t maxBetween_c, uint32_t longClick)
{
	// single must be over debounce time
	if (single_c > mDebounce) mSingle_c = single_c;
	// min between time must be bigger than debounce
	if (minBetween_c >= mDebounce) mMinBetween_c = minBetween_c;
	// max between time must be bigger than min between time
	if (maxBetween_c > minBetween_c) mMaxBetween_c = maxBetween_c;
	// long click must be longer than single click
	if (longClick > mSingle_c) mLong_c = longClick;
}

void Button::setParaAdd(uint32_t changeAdd, uint32_t slowAdd, uint32_t fastAdd)
{
	// slow add must run once, than it can change
	if (changeAdd > slowAdd) mChange_a = changeAdd;
	// first add must be positive
	if (slowAdd) mSlow_a = slowAdd;
	// second add must be positive
	if (fastAdd) mFast_a = fastAdd;
}

void Button::updateButton()
{
	// reset bit mask
	mRegister &= NEG_C;
	// update new actions
	getValues();
	click();
	add();
}

bool Button::getSingle()
{
	if (READ_C(A_C_MODE)) { // if add mode is active
		WRITE_A_C(0); // set click mode
		return 0; // no value (0) returned
	}
	else return READ_C(SINGLE_C);
}

bool Button::getDouble()
{
	if (READ_C(A_C_MODE)) {
		WRITE_A_C(0);
		return 0;
	}
	else return READ_C(DOUBLE_C);
}

bool Button::getLong()
{
	if (READ_C(A_C_MODE)) {
		WRITE_A_C(0);
		return 0;
	}
	else return READ_C(LONG_C);
}

uint8_t Button::getAction()
{
	if (READ_C(A_C_MODE)) {
		WRITE_A_C(0);
		return 0;
	}
	else {
		if (READ_C(SINGLE_C)) return SingleClick;
		else if (READ_C(DOUBLE_C)) return DoubleClick;
		else if (READ_C(LONG_C)) return LongClick;
		else return 0;
	}
}

bool Button::getAdd()
{
	if (!READ_C(A_C_MODE)) { // if click mode is active
		WRITE_A_C(1); // set add mode
		return 0; // no value (0) returned
	}
	else return READ_C(ADD_C);
}

void Button::getAddCalc(int16_t & value, int16_t add)
{
	// add value if true
	if (getAdd()) value += add;
}

void Button::getAddCalc(int16_t & value)
{
	// add 1 if true
	if (getAdd()) value ++;
}

bool Button::readSingle()
{
	if (READ_C(A_C_MODE)) {
		WRITE_A_C(0);
		return 0;
	}
	else {
		// update actions
		getValues();
		click();
		// save return value
		bool ret = READ_C(SINGLE_C);
		// reset bit
		mRegister &= ~_BV(SINGLE_C);
		return ret;
	}
}

bool Button::readDouble()
{
	if (READ_C(A_C_MODE)) {
		WRITE_A_C(0);
		return 0;
	}
	else {
		// update actions
		getValues();
		click();
		// save return value
		bool ret = READ_C(DOUBLE_C);
		// reset bit
		mRegister &= ~_BV(DOUBLE_C);
		return ret;
	}
}

bool Button::readLong()
{
	if (READ_C(A_C_MODE)) {
		WRITE_A_C(0);
		return 0;
	}
	else {
		// update actions
		getValues();
		click();
		// save return value
		bool ret = READ_C(LONG_C);
		// reset bit
		mRegister &= ~_BV(LONG_C);
		return ret;
	}
}

uint8_t Button::readAction()
{
	if (READ_C(A_C_MODE)) {
		WRITE_A_C(0);
		return 0;
	}
	else {
		// update actions
		getValues();
		click();
		// save return value
		uint8_t ret = 0;
		if (READ_C(SINGLE_C)) ret = SingleClick;
		else if (READ_C(DOUBLE_C)) ret = DoubleClick;
		else if (READ_C(LONG_C)) ret = LongClick;
		// reset bit mask
		mRegister &= NEG_C;
		return ret;
	}
}

bool Button::readAdd()
{
	if (!READ_C(A_C_MODE)) { // if click mode is active
		WRITE_A_C(1); // set add mode
		return 0; // no value (0) returned
	}
	else {
		// update actions
		getValues();
		add();
		return READ_C(ADD_C);		
	}
}

void Button::readAddCalc(int16_t & value, int16_t add)
{
	// add value if true
	if (readAdd()) value += add;
}

void Button::readAddCalc(int16_t & value)
{
	// add 1 if true
	if (readAdd()) value ++;
}