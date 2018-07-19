#include "config.h"

in_port_t get_in_port(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return (((struct sockaddr_in*)sa)->sin_port);
    }

    return (((struct sockaddr_in6*)sa)->sin6_port);
}

char *get_ip_str(const struct sockaddr *sa)
{
	char *buf = (char *)malloc(128);
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),
                    buf, 128);
            break;

        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),
                    buf, 128);
            break;

        default:
            strncpy(buf, "Unknown AF", 128);
            return NULL;
    }

    return buf;
}

void dump_data_as_hex(const char *data, size_t data_size)
{
    DEBUG("\ndump %d bytes to screen---------\n", data_size);
    for (int i=0; i<data_size; i++)
        fprintf(stderr, "0x%X ", data[i]);
        
    fprintf(stderr, "\n");
    DEBUG("\ndump end------------------------\n");
}