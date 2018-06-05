#include "config.h"

bool handle_serial_message(uint8_t message_type, mpack_reader_t *reader)
{
    switch (message_type)
    {
        case MSG_PONG:
            DEBUG("PONG!\n");
            mpack_expect_u8(reader);
            return (true);

        case MSG_NAK_CMD:
            ERROR("NAK_CMD type 0x%d\n", mpack_expect_u8(reader));
            return(true);

        case MSG_ACK_CMD:
            INFO("ACK_CMD type 0x%d\n", mpack_expect_u8(reader));
            return(true);

        default:
            break;
    }
    return (false);
}

bool handle_udp_message(mpack_reader_t *reader)
{   
    int ret;
    extern int serial_fd;    
    if (CONFIG_HEAD_IS_STUPID)
    {
        const char *data_ptr = NULL;
        uint32_t data_size = mpack_reader_remaining(reader, data_ptr);

        DEBUG("Re-Writing UDP data to serial port data_size:%d\n", data_size);

        if ((ret = write(serial_fd, reader->data, data_size)) == -1)
        {
            ERROR("Can't re-write data to serial \"%s\"\n", strerror(errno));
            return (false);
        }
        //usleep((data_size + 25) * 100);
        return (true);
    }
    else
    {
        DEBUG("We should be smart!\n");
        return (true);
    }
}

