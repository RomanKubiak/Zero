#include <Servo.h>
#include <msgpck.h>
#include "../shared/config.h"
#include "commands.h"
#include "util.h"


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
    msgpck_read_integer(&Serial, (uint8_t *)&function, 1);
    msgpck_read_integer(&Serial, &angle, 1);
    Servo *s = get_servo_by_function(function);
    
    if (s)
    {
        s->write(angle);
        body_health.servos[function] = angle;
        cmd_ack(CMD_SERVO);
        msgpck_write_integer(&Serial, angle);
        return (true);
    }
    else
    {
        cmd_nak(CMD_SERVO);
        return (false);
    }
}

void cmd_nak(uint8_t cmd_type)
{
    msgpck_write_array_header(&Serial,3);
    msgpck_write_integer(&Serial, MSG_NAK_CMD);
    msgpck_write_integer(&Serial, cmd_type);
}

void cmd_ack(uint8_t cmd_type)
{
    msgpck_write_array_header(&Serial,3);
    msgpck_write_integer(&Serial, MSG_ACK_CMD);
    msgpck_write_integer(&Serial, cmd_type);
}
