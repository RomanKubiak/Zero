#include "util.h"
Servo s_pan, s_tilt, s_radar;
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