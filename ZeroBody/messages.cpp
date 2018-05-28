#include "messages.h"

bool handle_incoming_message(uint8_t message_type)
{
    switch (message_type)
    {
        case MSG_PING:
            return (send_msg_pong());

        default:
            break;
    }
    return (false);
}

bool send_msg_pong()
{
	msgpck_write_map_header(&Serial,1);
	msgpck_write_integer(&Serial, MSG_PONG);
        return (true);
}
