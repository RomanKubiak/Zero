#include "config.h"
#include <wiringSerial.h>
#include "mpack/mpack.h"

void serial_event(int serial_fd, short event, void *arg)
{
    char readbuf[128];
    int read_data_size = 0;
    uint32_t array_size;
    mpack_reader_t reader;
    uint8_t message_type;
    mpack_error_t error;
    
    if ( (read_data_size = read(serial_fd, readbuf, sizeof(readbuf))) == -1)
    {
        ERROR("error reading from serial port \"%s\"\n", strerror(errno));
        return;
    }
    
    mpack_reader_init(&reader, &readbuf[0], sizeof(readbuf), read_data_size);
    array_size = mpack_expect_array_max(&reader,16);
    
    DEBUG("serial data size %d, read %d array size\n", read_data_size, array_size);
    
    message_type = mpack_expect_u8(&reader);
    
    if (!handle_message(message_type, &reader))
    {
        ERROR("Can't handle message: %d\n", message_type);
    }
    
    mpack_done_array(&reader);
    
    if ((error = mpack_reader_destroy(&reader)) != mpack_ok)
    {
        ERROR("Error \"%s\" occured reading data!\n", mpack_error_to_string(error));
    }
}

void ping_timer_callback(int serial_fd, short event, void *arg)
{
    char *data;
    size_t size;
    int ret;
    mpack_writer_t writer;
    
    mpack_writer_init_growable(&writer, &data, &size);
    mpack_start_array(&writer, 2);
    mpack_write_uint(&writer, MSG_PING);
    mpack_write_u8(&writer, 13);
    mpack_finish_array(&writer);
    
    if (mpack_writer_destroy(&writer) != mpack_ok)
    {
        ERROR("an error occured encoding ping data\n");
        return;
    }
    if ((ret = write(serial_fd, data, size)) == -1)
    {
        ERROR("can't write to serial port: %s\n", strerror(errno));
        return;
    }
    DEBUG("written %d out of %d bytes to serial port\n", ret, size);
}

int serial_register(struct event_base *evbase)
{
    int serial_fd;
    struct event *ev;
    struct timeval tv;
    tv.tv_sec   = 0;
    tv.tv_usec  = 950000;
    
    if ((serial_fd = serialOpen(CONFIG_PI_SERIAL, CONFIG_SERIAL_SPEED)) < 0)
    {
        ERROR("can't open serial device %s %dbps\n", CONFIG_PI_SERIAL, CONFIG_SERIAL_SPEED);
        return -1;
    }
    DEBUG("opened serial port %s %dbps\n", CONFIG_PI_SERIAL, CONFIG_SERIAL_SPEED);    
    ev = event_new(evbase, serial_fd, EV_READ|EV_PERSIST, serial_event, NULL);
    
    if (ev == NULL)
    {
        ERROR("can't create new event\n");
        return -1;
    }
    
    event_add(ev, NULL);
    ev = event_new(evbase, serial_fd, EV_PERSIST, ping_timer_callback, NULL);
    event_add(ev, &tv);
    return 0;
}