Main Object: Button-Master
Sub Object: README
Author: Christoph Amon
Contact: christoph.amon.htl@gmail.com
School: HTL 3 Rennweg
Place: Austria, Vienna
Date: 25.04.2016
Version: v1.0.2-014

Debounce Library:
This library debounces inputs, which is based on the timer1 (function
millis()). The time to debounce is controlable.
Functions to read button states on use/real-time (like digitalRead())
or with update & get functionality are available.
Furthermore functions to read/get current state, rosen or fallen edge
and changed state are added.
Pulldown, pullup and intern pullup modes are supported. Moreover
inverted input (mostly used for pullup button) are also available.

Button Library:
This library only works with the debounce library and reads button actions.
It is also based on the timer1 (function millis()). Functions to read button
actions on use/real-time (like digitalRead()) or with update & get
functionality are available.
For this library parameters can be set up to control the timing
for different button actions.
As in the debounce library pulldown, pullup and intern pullup such as
inverted input are supported.
The whole functionality of the debounce library is available.
Additionaly functions to read/get a single click, a double click,
a long click or all three combined in one are available. There is
also a adding function which makes the pressed button adding values
to another value. After a suspended time the values getting added faster.
More about this functions in the examples and time diagrams.

All examples are written in update and real-time functionality, this
can be changed through a global bool variable.

Further information in "Button-Master Documentation.pdf"

Tested on:
	- Arduino Uno Board
	- Arduino Mega Board