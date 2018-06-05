#include "config.h"

struct event_base *evbase = NULL;

int main (int argc, char *argv[])
{
    evbase = event_base_new();
    if (evbase == NULL)
    {
        ERROR("error: failed to initialize libevent\n");
        return -1;
    }

    INFO("starting http server\n");
    if (http_server_register(evbase) == -1)
    {
    	ERROR("http_server_register failed\n");
    	return -1;
    }

    INFO("starting UDP server\n");
    if (udp_server_register(evbase) == -1)
    {
    	ERROR("udp_server_register failed\n");
    	return -1;
    }

    INFO("registering wiringPi components\n");	
    if (wiringPiSetup() == -1)
    {
        ERROR("can't init wiringPi \"%s\"\n", strerror(errno));
        return -1;
    }    

    INFO("registering serial port callback\n");    
    if (serial_register(evbase) == -1)
    {
        ERROR("serial_register failed\n");
        return -1;
    } 
    
    INFO("starting main program loop\n");
    event_base_dispatch(evbase);
    return 0;
}
