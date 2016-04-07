/*
 * Sample sketch which makes the Arduino to impersonate a Classic Controller.
 *
 * Use a PushButton connected to the digital pin 2 and GND. It will trigger
 * a D-Pad RIGHT button press of the impersonated Classic Controller.
 *
 * Copyright (c) 2011 Peter Brinkmann (peter.brinkmann@gmail.com)
 *
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "Wire.h" // This seems redundant, but we need to declare this
                  // dependency in the pde file or else it won't be included
                  // in the build.

#include "wiimote.h"

// Classic Controller Buttons
int bdl = 0; // D-Pad Left state
int bdr = 0; // D-Pad Right state
int bdu = 0; // D-Pad Up state
int bdd = 0; // D-Pad Down state
int ba = 0; // A button state
int bb = 0; // B button state
int bx = 0; // X button state
int by = 0; // Y button state
int bl = 0; // L button state
int br = 0; // R button state
int bm = 0; // MINUS button state
int bp = 0; // PLUS button state
int bhome = 0; // HOME button state
int bzl = 0; // ZL button state
int bzr = 0; // ZR button state

/*
 * Analog Buttons.
 * They are initialized with center values from the calibration buffer.
 */
byte lx = calbuf[2]>>2;
byte ly = calbuf[5]>>2;
byte rx = calbuf[8]>>3;
byte ry = calbuf[11]>>3;

int pinRight = 2;


// Wiimote button data stream
byte *stream_callback(byte *buffer) {
	wiimote_write_buffer(buffer, bdl, bdr, bdu, bdd, ba, bb, bx, by, bl, br,
			bm, bp, bhome, lx, ly, rx, ry, bzl, bzr);

	return buffer;
}

void setup() {
	// Set PushButton pins as input, turning pull-up on
	pinMode(pinRight, INPUT);
	digitalWrite(pinRight, HIGH);

	// Prepare wiimote communications
	wiimote_stream = stream_callback;
	wiimote_init();
}

void loop() {
	/*
	 * If PushButton is pressed, pinRight will be LOW.
	 * This value is then inverted and given to variable "bdr", that represents
	 * D-Pad RIGHT button.
	 */
	bdr = digitalRead(pinRight);

	delay(50);
}
