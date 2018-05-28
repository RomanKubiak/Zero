#include "config.h"
#include <wiringSerial.h>
#include "mpack/mpack.h"

void serial_event(int serial_fd, short event, void *arg)
{
    char readbuf[128];
    int read_data_size = 0;
    uint8_t msg_type = 0;
    char buf[128];
    mpack_reader_t reader;
    size_t allocated_size;
    
    if ( (read_data_size = read(serial_fd, readbuf, sizeof(readbuf))) == -1)
    {
        ERROR("error reading from serial port \"%s\"\n", strerror(errno));
        return;
    }
    
    mpack_reader_init(&reader, &readbuf[0], sizeof(readbuf), read_data_size);
    if (mpack_expect_array(&reader) == 2) // msg type and data
    {
        DEBUG("unpacked array of 2 elements\n");
        msg_type = mpack_expect_int(&reader);
        if (msg_type == MSG_STATUS)
        {
            DEBUG("got status message\n");
            mpack_expect_bin_max(&reader, sizeof(struct current_status_t));
            mpack_read_bytes(&reader, &buf[0], 68);
            struct current_status_t *status = (struct current_status_t *)&buf;
            DEBUG("%d %d\n", status->body_millis, status->battery_mv);
        }
    }
}

int serial_register(struct event_base *evbase)
{
    int serial_fd;
    struct event *ev;
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
    return 0;
}