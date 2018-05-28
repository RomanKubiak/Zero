#include "config.h"
#include "cwpack.h"

static void udp_server_callback(const int sock, short int which, void *arg)
{
	struct sockaddr_in server_sin;
	socklen_t server_sz = sizeof(server_sin);
	struct sockaddr *addr = (struct sockaddr *) &server_sin;
	char rcv_buf[32];
	/* Recv the data, store the address of the sender in server_sin */
	if (recvfrom(sock, &rcv_buf, sizeof(rcv_buf) - 1, 0, addr, &server_sz) == -1) {
		perror("recvfrom()");
		event_loopbreak();
	}

	DEBUG("got a UDP packet from: %s:%d\n", get_ip_str(addr), get_in_port(addr));
}

int udp_server_register(struct event_base *evbase)
{
	int udp_socket;
	struct event *udp_event = NULL;
	struct sockaddr_in sin;
	

	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(CONFIG_PI_PORT);
	//Start : Set flags in non-blocking mode
	int udp_socket_flags = fcntl(udp_socket, F_GETFL, 0);
	if (udp_socket_flags < 0)
	{
		perror("udp socket fcntl read");
		return -1;
	}

	if (fcntl(udp_socket, F_SETFL, udp_socket_flags | O_NONBLOCK) < 0)
	{
		perror("udp socket fctnl set");
		return -1;
	}

	if (bind(udp_socket, (struct sockaddr *) &sin, sizeof(sin)))
	{
		perror("bind()");
		return -1;
	}
	udp_event = event_new(evbase, udp_socket, EV_READ|EV_PERSIST, udp_server_callback, NULL);

	if (udp_event == NULL)
	{
		perror("event_new");
		return -1;
	}
	event_add(udp_event, NULL);

	return 0;
}