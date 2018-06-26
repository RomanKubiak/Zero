#ifndef __ZERO_UTIL_H__
#define __ZERO_UTIL_H__
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../shared/config.h"

#ifdef DEBUG_SERIAL_ENABLED
	class SoftwareSerial;
	SoftwareSerial *getDebugStream();
	void _SerialPrintf(const char *fmt, ...);
	void initialize_debug_stream();
	#define DBG(fmt, ...) _SerialPrintf(PSTR(fmt), ##__VA_ARGS__)
#else
	#define DBG(fmt, ...)
#endif


class Servo;
Servo *get_servo_by_function(servo_function f);
void initialize_servos();
void initialize_magnetometers();
void set_body_health();
bool set_local_mode();
bool set_remote_mode();
void initialize_neopixels();

// defined in commands.cpp
void initialize_motors();
#endif