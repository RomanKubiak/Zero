#include "util.h"
#include <Servo.h>
Servo s_pan, s_tilt, s_radar;

#ifdef DEBUG_SERIAL_ENABLED
SoftwareSerial debugSerial(CONFIG_AR_DEBUG_SERIAL_RX_PIN, CONFIG_AR_DEBUG_SERIAL_RX_PIN);

void initialize_debug_stream()
{
	debugSerial.begin(9600);
	debugSerial.println("START");
}

SoftwareSerial *getDebugStream()
{
	return (&debugSerial);
}

extern "C" {
 int serialputc(char c, FILE *fp)
 { 
     if(c == '\n')
       debugSerial.write('\r'); 
   debugSerial.write(c); 
 }
}


void _SerialPrintf(const char *fmt, ...)
{
FILE stdiostr;
va_list ap;

 fdev_setup_stream(&stdiostr, serialputc, NULL, _FDEV_SETUP_WRITE);

 va_start(ap, fmt);
 vfprintf_P(&stdiostr, fmt, ap);
 va_end(ap);
}

#endif

void initialize_servos()
{
	s_pan.attach(CONFIG_AR_SERVO_PAN_PIN);
	s_tilt.attach(CONFIG_AR_SERVO_TILT_PIN);
	s_radar.attach(CONFIG_AR_SERVO_RADAR_PIN);
}

Servo *get_servo_by_function(servo_function f)
{
	switch(f)
	{
		case servo_pan:
			return (&s_pan);
		case servo_tilt:
			return (&s_tilt);
		case servo_radar:
			return (&s_radar);
		default:
			break;
	}
	return (nullptr);
}