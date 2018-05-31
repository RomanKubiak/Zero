#include "util.h"
#include <Servo.h>
Servo s_pan, s_tilt, s_radar;

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