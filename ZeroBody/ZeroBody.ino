#include <AStar32U4.h>
#include <TimerOne.h>
#include <Servo.h>
#include <Wire.h>

#include "messages.h"
#include "util.h"

volatile int timer_int;
uint32_t loop_count;
extern current_status_t body_health;

#define FPS 24

bool heartbeat_led_state = LOW;
char serial_buffer[CONFIG_MPACK_WRITER_BUFFER];

void timer_callback(void)
{
	if (++loop_count == FPS)
	{	
		ledYellow(heartbeat_led_state);
		heartbeat_led_state = !heartbeat_led_state;
		loop_count = 0;
	}
}

bool get_serial_message()
{
	bool res = true;
	if (Serial.available() > 0)
	{
		if (Serial.peek() == '\n')
		{
			Serial.println("newline: debuginfo\n");
			Serial.flush();
			return true;
		}
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
			DBG("can't read array size\n");
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
	Serial.begin(CONFIG_SERIAL_SPEED);
	DBG("start\n");
	memset((void *)&body_health, 0, sizeof(struct current_status_t));
#ifdef DEBUG_SERIAL_ENABLED
	initialize_debug_stream();
#endif
	DBG("attach timer1\n");
	Timer1.initialize(1000000/FPS);
	Timer1.attachInterrupt(timer_callback);
	DBG("init servos\n");
	initialize_servos();
	pinMode(19, INPUT);
	DBG("init i2c\n");
	Wire.begin();
	DBG("init magnetometers\n");
	// initialize_magnetometers();
	DBG("init neopixels\n");
	// initialize_neopixels();
}

void loop()
{
	if (!get_serial_message())
	{
		DBG("get_serial_message failed\n");
	}
}
