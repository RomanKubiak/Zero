#ifndef __ZERO_CONFIG_H__
#define __ZERO_CONFIG_H__

#define CONFIG_SERIAL_SPEED		9600

#define CONFIG_PI_JSON_FILE 		"./zero.json"
#define CONFIG_PI_SERIAL		"/dev/ttyUSB0"
#define CONFIG_PI_PORT			12345
#define CONFIG_PI_DEBUG			1

// 9,10,12 reserved pins
#define CONFIG_AR_SERVO_PAN_PIN 	14
#define CONFIG_AR_SERVO_TILT_PIN 	15
#define CONFIG_AR_SERVO_RADAR_PIN	7
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

#define CMD_MOTOR	0xf1
#define CMD_SERVO	0xf2
#define CMD_RADAR	0xf3
#define CMD_NEOPIXEL	0xf4
#define CMD_RESET	0xf5

enum servo_function
{
	cam_pan,
	cam_tilt,
	radar
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
	uint8_t servo_cam_pan_position;
	uint8_t servo_cam_tilt_position;
	uint8_t servo_radar_position;
	uint32_t battery_mv;
	uint32_t body_millis;
	uint16_t compass_heading1;
	uint16_t compass_heading2;
	uint32_t neopixel[CONFIG_AR_NEOPIXEL_COUNT];
} __attribute__((packed));;

#endif