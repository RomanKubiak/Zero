#include "util.h"
#include "messages.h"
#include <AStar32U4.h>
#include <Servo.h>
#include <MechaQMC5883.h>
#include <Adafruit_NeoPixel.h> 
#include <Wire.h>

Servo s_pan, s_tilt, s_radar;
//MechaQMC5883 m_body;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(CONFIG_AR_NEOPIXEL_COUNT, CONFIG_AR_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
current_status_t body_health;

#ifdef DEBUG_SERIAL_ENABLED
SoftwareSerial debugSerial(CONFIG_AR_DEBUG_SERIAL_RX_PIN, CONFIG_AR_DEBUG_SERIAL_RX_PIN);

void initialize_debug_stream()
{
	debugSerial.begin(9600);
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

/*MechaQMC5883 *get_magnetometer(magnetometer_function f)
{
	switch (f)
	{
		case mag_body:
			return (&m_body);
		default:
			break;
	}
	return (nullptr);
}

void initialize_magnetometers()
{
	m_body.init();
	m_body.setMode(Mode_Continuous, ODR_200Hz, RNG_8G, OSR_512);
}
*/

void initialize_neopixels()
{
	pixels.begin();
	pixels.setPixelColor(17, pixels.Color(4,4,4));
	pixels.setPixelColor(18, pixels.Color(4,4,4));
	set_local_mode();
	
}

bool set_local_mode()
{
	pixels.setPixelColor(15, pixels.Color(0,16,0));
	pixels.setPixelColor(16, pixels.Color(0,16,0));
	pixels.show();
	return (true);
}

bool set_remote_mode()
{
	pixels.setPixelColor(15, pixels.Color(16,0,0));
	pixels.setPixelColor(16, pixels.Color(16,0,0));
	pixels.show();
	return (true);
}

void set_body_health()
{
	/*MechaQMC5883 *qmc = get_magnetometer(mag_body);
	uint16_t x,y,z;
	qmc->read(&x,&y,&z);
	body_health.azimuth_body = qmc->azimuth(&x,&y);*/
	body_health.current_draw = analogRead(CONFIG_AR_CURRENT_SENS_PIN);
	body_health.battery_mv = analogRead(19);
}
