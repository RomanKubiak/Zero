#ifndef __ZERO_COMMAND_H__
#define __ZERO_COMMAND_H__

#include <Arduino.h>
#include <msgpck.h>
#include "../shared/config.h"

bool handle_incomming_message(uint8_t message_type);
bool send_msg_pong();
#endif