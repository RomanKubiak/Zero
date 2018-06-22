#ifndef __ZERO_CONFIG_H__
#define __ZERO_CONFIG_H__

#define CONFIG_SERIAL_SPEED		9600

#define CONFIG_MPACK_WRITER_BUFFER	256
#define CONFIG_MPACK_MSG_ARRAY_MAX	128

#define CONFIG_PI_JSON_FILE 		"/home/atom/devel/ZeroHead/zero.json"
#define CONFIG_PI_SERIAL		"/dev/ttyACM0"
#define CONFIG_PI_PORT			31337
#define CONFIG_PI_DEBUG			1

// 9,10,12 reserved pins
#define CONFIG_AR_SERVO_PAN_PIN 	18 //A0
#define CONFIG_AR_SERVO_TILT_PIN 	20 //A2   
#define CONFIG_AR_SERVO_RADAR_PIN	21 //A3
#define CONFIG_AR_CURRENT_SENS_PIN	22 //A4
#define CONFIG_AR_NEOPIXEL_PIN		23 //A5
#define CONFIG_AR_DEBUG_SERIAL_RX_PIN	-1
#define CONFIG_AR_DEBUG_SERIAL_TX_PIN	-1

#define CONFIG_AR_NEOPIXEL_COUNT	26
#define CONFIG_AR_SERIAL_RX		8
#define CONFIG_AR_SERIAL_TX		11

#define CONFIG_HEAD_IS_STUPID		1

/* MSGPACK commands */
#define MSG_HEARTBEAT 		0xe1
#define MSG_STATUS		0xe2
#define MSG_CMD			0xe3
#define MSG_PONG		0xe4
#define MSG_PING		0xe5
#define MSG_UNKNOWN		0xef
#define MSG_ACK_CMD		0xe6
#define MSG_NAK_CMD		0xe7
#define MSG_I2C_SCAN_RESULT	0xe8
#define MSG_I2C_SCAN		0xe9
#define MSG_HEALTH_UPDATE	0xea
#define MSG_MODE_REMOTE		0xeb
#define MSG_MODE_LOCAL		0xec

#define CMD_MOTOR		0xf1
#define CMD_SERVO		0xf2
#define CMD_RADAR		0xf3
#define CMD_NEOPIXEL		0xf4
#define CMD_RESET		0xf5

#define CONFIG_AUTH_TOKEN	0x429b
#define CONFIG_AUTH_TOKEN_TYPE	0xd7

enum servo_function
{
	servo_pan,
	servo_tilt,
	servo_radar,
	servo_count
};

enum magnetometer_function
{
	mag_body,
	mag_radar,
	mag_camera
};

struct __attribute__((__packed__)) current_status_t
{
	uint8_t motor_left_speed;
	uint8_t motor_left_dir;
	uint8_t motor_right_speed;
	uint8_t motor_right_dir;
	uint16_t radar_reading1;
	uint16_t radar_reading2;
	uint8_t servos[servo_count];
	uint32_t battery_mv;
	uint16_t azimuth_body;
	uint16_t compass_heading2;
	uint16_t current_draw;
	uint32_t last_ping_seq;
};

#endif