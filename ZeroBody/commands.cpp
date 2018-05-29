#include "commands.h"


bool handle_incoming_command(uint8_t cmd_type)
{
    switch (cmd_type)
    {
        case CMD_SERVO:
            return (cmd_servo());
        default:
            break;
    }   
    return (false);
}

bool cmd_servo()
{
    servo_function function;
    uint8_t angle;
}