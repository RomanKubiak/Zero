#include <Servo.h>
#include <msgpck.h>
#include <AStar32U4.h>
#include "../shared/config.h"
#include "commands.h"
#include "util.h"

extern struct current_status_t body_health;
AStar32U4Motors motors;

bool handle_incoming_command(uint8_t cmd_type)
{
    switch (cmd_type)
    {
        case CMD_SERVO:
            return (cmd_servo());
        case CMD_MOTOR:
            return (cmd_motor());
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
        s->write(angle);
        body_health.servos[function] = angle;
        cmd_ack(CMD_SERVO);
        return (true);
    }
    else
    {
        cmd_nak(CMD_SERVO);
        return (false);
    }
}

bool cmd_motor()
{
    msgpck_read_integer(&Serial, (uint8_t *)&body_health.speed_left, sizeof(int16_t));
    msgpck_read_integer(&Serial, (uint8_t *)&body_health.speed_right, sizeof(int16_t));
    motors.setSpeeds(body_health.speed_left, body_health.speed_right);
    cmd_ack(CMD_MOTOR);
    return (true);
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

void initialize_motors()
{
    motors.setSpeeds(0,0);
}