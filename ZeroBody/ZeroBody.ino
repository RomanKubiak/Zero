#include <AStar32U4.h>
#include <TimerOne.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#include "messages.h"
#include "util.h"

volatile int timer_int;
uint32_t loop_count;
#undef DEBUG_SERIAL_ENABLED
#define LOOP_COUNT_PERIOD 5

bool heartbeat_led_state = LOW;
char serial_buffer[CONFIG_MPACK_WRITER_BUFFER];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel (
	CONFIG_AR_NEOPIXEL_COUNT,
	CONFIG_AR_NEOPIXEL_PIN,
	NEO_GRB + NEO_KHZ800
);

void timer_callback(void)
{
	timer_int = 1;
	loop_count++;
	if (loop_count == LOOP_COUNT_PERIOD)
		loop_count = 0;
	
	if (loop_count == 0)
	{
		ledYellow(heartbeat_led_state);
		heartbeat_led_state = !heartbeat_led_state;
	}

	set_body_health();
	timer_int = 0;
}

bool get_serial_message()
{
	bool res = true;
	if (Serial.available() > 0)
	{
		uint32_t array_size;
		uint8_t message_type;
		res &= msgpck_array_next(&Serial);
		if (!res)
		{	
			DBG("not an array message\n");
			Serial.readBytes(&serial_buffer[0], CONFIG_MPACK_WRITER_BUFFER);
			return false;
		}

		res &= msgpck_read_array_size(&Serial, &array_size);

		if (!res)
		{
			DBG("can't read map size\n");
			return false;
		}

		res &= msgpck_read_integer(&Serial, &message_type, sizeof(uint8_t));
		if (!res)
		{
			DBG("can't read message type\n");
			return false;
		}

		res &= handle_incoming_message(message_type);
		Serial.flush();
	}

	return (res);
}

void setup()
{
	Serial.begin(115200);
#ifdef DEBUG_SERIAL_ENABLED
	initialize_debug_stream();
#endif
	Timer1.initialize(50000 * LOOP_COUNT_PERIOD);
	Timer1.attachInterrupt(timer_callback);
	body_health.setup_done = true;
	initialize_servos();
	Wire.begin();
	initialize_magnetometers();
}

void loop()
{
	if (!get_serial_message())
	{
		DBG("get_serial_message failed\n");
	}
}
