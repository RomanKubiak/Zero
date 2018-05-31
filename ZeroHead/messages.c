#include "config.h"

bool handle_serial_message(uint8_t message_type, mpack_reader_t *reader)
{
    switch (message_type)
    {
        case MSG_PONG:
            DEBUG("PONG!\n");
            return (true);
        default:
            break;
    }
    return (false);
}

bool handle_udp_message(uint8_t message_type, mpack_reader_t *reader)
{
    switch (message_type)
    {
        case MSG_CMD:
            DEBUG("processing remote command\n");
            return (true);
        default:
            break;
    }
    
    return (false);
}