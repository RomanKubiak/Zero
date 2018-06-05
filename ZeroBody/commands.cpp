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
            DBG("handle command servo\n");
            return (cmd_servo());
        default:
            break;
    }   
    return (false);
}

bool cmd_servo()
{
    uint8_t function;
    uint8_t angle;
    msgpck_read_integer(&Serial, (uint8_t *)&function, sizeof(uint8_t));
    msgpck_read_integer(&Serial, &angle, sizeof(uint8_t));
    Servo *s = get_servo_by_function((servo_function)function);
    
    if (s)
    {
        DBG("got a valid servo handle: type=%d angle=%d", function, angle);
        s->write(angle);
        body_health.servos[function] = angle;
        cmd_ack(CMD_SERVO);
        return (true);
    }
    else
    {
        DBG("can't get a valid servo handle for servo type=%d\n", function);
        cmd_nak(CMD_SERVO);
        return (false);
    }
}

void cmd_nak(uint8_t cmd_type)
{
    msgpck_write_array_header(&Serial,2);
    msgpck_write_integer(&Serial, MSG_NAK_CMD);
    msgpck_write_integer(&Serial, cmd_type);
}

void cmd_ack(uint8_t cmd_type)
{
    msgpck_write_array_header(&Serial,2);
    msgpck_write_integer(&Serial, MSG_ACK_CMD);
    msgpck_write_integer(&Serial, cmd_type);
}
