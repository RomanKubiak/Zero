#include "config.h"

bool handle_serial_message(uint8_t message_type, mpack_reader_t *reader)
{
    DEBUG("handle serial message\n");
    switch (message_type)
    {
        case MSG_PONG:
            DEBUG("PONG seq=%d\n", mpack_expect_u32(reader));
            return (true);

        case MSG_NAK_CMD:
            ERROR("NAK_CMD type 0x%d\n", mpack_expect_u8(reader));
            return(true);

        case MSG_ACK_CMD:
            INFO("ACK_CMD type 0x%d\n", mpack_expect_u8(reader));
            return(true);

        case MSG_I2C_SCAN_RESULT:            
            return (handle_i2c_scan_result(reader));

        case MSG_HEALTH_UPDATE:
            return (handle_health_update(reader));
            
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
        uint32_t data_size = mpack_reader_remaining(reader, &data_ptr);

        DEBUG("Re-Writing UDP data to serial port data_size:%d\n", data_size);

        if ((ret = write(serial_fd, reader->data, data_size)) == -1)
        {
            ERROR("Can't re-write data to serial \"%s\"\n", strerror(errno));
            return (false);
        }
        usleep((data_size + 25) * 100);
        return (true);
    }
    else
    {
        DEBUG("We should be smart!\n");
        return (true);
    }
}

bool handle_i2c_scan_result(mpack_reader_t *reader)
{
    DEBUG("reading\n");
    uint8_t device_count = mpack_expect_u8(reader);
    DEBUG("device_count=%d\n", device_count);
    for (int i=0 ;i<device_count; i++)
    {
        INFO("I2C device 0x%02X\n", mpack_expect_u8(reader));
    }

    return (true);
}

bool handle_health_update(mpack_reader_t *reader)
{
    DEBUG("reading\n");
    DEBUG("%.2f\n", mpack_expect_float(reader));
    DEBUG("%d\n",mpack_expect_u32(reader));
    DEBUG("%d\n", mpack_expect_u32(reader));
    DEBUG("%d\n", mpack_expect_u32(reader));
    return (true);
}