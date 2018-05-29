#ifndef __ZERO_COMMAND_H__
#define __ZERO_COMMAND_H__

#include <Arduino.h>
#include <msgpck.h>
#include "../shared/config.h"

bool handle_incoming_command(uint8_t cmd_type);
bool cmd_servo();
#endif