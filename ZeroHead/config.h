#ifndef CONFIG_H__
#define CONFIG_H__

#include <evhttp.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include "mpack/mpack.h"

#include "../shared/config.h"

#define CONFIG_DEBUG
#if defined(CONFIG_DEBUG)
	#define DEBUG(fmt, args...)\
		fprintf(stderr, "DEBUG: %s:%d: " fmt, __func__, __LINE__, ##args)
#else
 #define DEBUG(fmt, args...) /* Don't do anything in release builds */
#endif

#define ERROR(fmt, args...)\
		fprintf(stderr, "ERROR: %s:%d: " fmt, __func__, __LINE__, ##args)

#define INFO(fmt, args...)\
		fprintf(stderr, "INFO : %s:%d: " fmt, __func__, __LINE__, ##args)

int udp_server_register(struct event_base *evbase);
int http_server_register(struct event_base *evbase);
int heartbeat_led_register(struct event_base *evbase);
int utils_register(struct event_base *evbase);
int serial_register(struct event_base *evbase);

char *get_ip_str(const struct sockaddr *sa);
in_port_t get_in_port(struct sockaddr *sa);

bool handle_serial_message(uint8_t message_type, mpack_reader_t *reader);
bool handle_udp_message(mpack_reader_t *reader);
#endif