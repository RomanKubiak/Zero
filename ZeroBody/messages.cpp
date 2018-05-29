#include "messages.h"
#include "commands.h"

bool handle_incoming_message(uint8_t message_type)
{
    switch (message_type)
    {
        case MSG_PING:
            return (send_msg_pong());

        case MSG_CMD:
            uint8_t cmd_type;
            msgpck_read_integer(&Serial, &cmd_type, 1);
            return (handle_incoming_command(cmd_type));
            
        default:
            break;
    }
    return (send_msg_unknown());
}

bool send_msg_pong()
{
    uint8_t seq;
    msgpck_read_integer(&Serial, &seq, 1);
    msgpck_write_array_header(&Serial,2);
    msgpck_write_integer(&Serial, MSG_PONG);
    msgpck_write_integer(&Serial, seq);
    return (true);
}

bool send_msg_unknown()
{
    msgpck_write_map_header(&Serial, 1);
    msgpck_write_integer(&Serial, MSG_UNKNOWN);
    return (true);
}