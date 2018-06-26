#ifndef __ZERO_COMMAND_H__
#define __ZERO_COMMAND_H__

#include <Arduino.h>

bool handle_incoming_command(uint8_t cmd_type);
bool cmd_servo();
bool cmd_motor();
void cmd_nak(uint8_t cmd_type);
void cmd_ack(uint8_t cmd_type);
#endif