#ifndef __ZERO_MESSAGES_H__
#define __ZERO_MESSAGES_H__

#include <Arduino.h>
#include <msgpck.h>
#include "../shared/config.h"

bool handle_incoming_message(uint8_t message_type);
bool send_msg_pong();
bool send_msg_unknown();

#endif