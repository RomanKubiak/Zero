#include <AStar32U4.h>
#include <TimerOne.h>
#include <msgpck.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define DBG(x)
#include "../shared/config.h"
#include "command.h"

bool heartbeat_led_state = LOW;
struct current_status_t current_status;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel (
	CONFIG_AR_NEOPIXEL_COUNT,
	CONFIG_AR_NEOPIXEL_PIN,
	NEO_GRB + NEO_KHZ800
);

Servo servo[3];

void heartbeat_timer_callback(void)
{
	ledYellow(heartbeat_led_state);
	heartbeat_led_state = !heartbeat_led_state;
}

bool get_serial_message()
{
	bool res = true;
	if (Serial.available() > 0)
	{
		uint32_t map_size;
		uint8_t cmd_type;
		res &= msgpck_map_next(&Serial);
		if (!res)
		{	
			DBG("not a map message");
			return false;
		}

		res &= msgpck_read_map_size(&Serial, &map_size);

		if (!res)
		{
			DBG("can't read map size");
			return false;
		}

		res &= msgpck_read_integer(&Serial, &cmd_type, sizeof(uint8_t));
		if (!res)
		{
			DBG("can't read command type");
			return false;
		}

		return (handle_command(cmd_type));
	}

	return (res);
}

void write_pong()
{
	msgpck_write_map_header(&Serial,1);
	msgpck_write_integer(&Serial, MSG_PONG);
}

void setup()
{
	Serial.begin(9600);
	Timer1.initialize(450000);
	Timer1.attachInterrupt(heartbeat_timer_callback);
	servo[radar].attach(CONFIG_AR_SERVO_RADAR_PIN);
	pixels.begin();
	pixels.setPixelColor (0,pixels.Color(32,0,0,0));
	pixels.show();
}

void loop()
{
	get_serial_message();
}
