#ifndef __ZERO_CONFIG_H__
#define __ZERO_CONFIG_H__

#define CONFIG_SERIAL_SPEED		115200

#define CONFIG_MPACK_WRITER_BUFFER	1024

#define CONFIG_PI_JSON_FILE 		"./zero.json"
#define CONFIG_PI_SERIAL		"/dev/ttyACM0"
#define CONFIG_PI_PORT			31337
#define CONFIG_PI_DEBUG			1

// 9,10,12 reserved pins
#define CONFIG_AR_SERVO_PAN_PIN 	18
#define CONFIG_AR_SERVO_TILT_PIN 	19    
#define CONFIG_AR_SERVO_RADAR_PIN	20
#define CONFIG_AR_NEOPIXEL_PIN		16
#define CONFIG_AR_NEOPIXEL_COUNT	10
#define CONFIG_AR_SERIAL_RX		8
#define CONFIG_AR_SERIAL_TX		11

/* MSGPACK commands */
#define MSG_HEARTBEAT 	0xe1
#define MSG_STATUS	0xe2
#define MSG_CMD		0xe3
#define MSG_PONG	0xe4
#define MSG_PING	0xe5
#define MSG_UNKNOWN	0xef
#define MSG_ACK_CMD	0xe6
#define MSG_NAK_CMD	0xe7

#define CMD_MOTOR	0xf1
#define CMD_SERVO	0xf2
#define CMD_RADAR	0xf3
#define CMD_NEOPIXEL	0xf4
#define CMD_RESET	0xf5

#define CONFIG_AUTH_TOKEN	0x429b
#define CONFIG_AUTH_TOKEN_TYPE	0xd7

enum servo_function
{
	servo_pan,
	servo_tilt,
	servo_radar,
	servo_count
};

struct current_status_t
{
	uint8_t motor_left_speed;
	uint8_t motor_left_dir;
	uint8_t motor_right_speed;
	uint8_t motor_right_dir;
	uint8_t radar_angle;
	uint32_t radar_reading1;
	uint32_t radar_reading2;
	uint8_t servos[servo_count];
	bool setup_done;
	uint8_t last_ping_seq;
	uint32_t battery_mv;
	uint32_t body_millis;
	uint16_t compass_heading1;
	uint16_t compass_heading2;
	uint32_t neopixel[CONFIG_AR_NEOPIXEL_COUNT];
};

#endif