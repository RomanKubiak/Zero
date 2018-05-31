#include "config.h"
#include <mpack/mpack.h>

static bool is_client_authorized(mpack_reader_t *reader)
{
	uint8_t auth_type;
	uint32_t auth_token;
	const uint8_t array_size = mpack_expect_array_max(reader, 2);
	
	if (array_size != 2)
	{
		ERROR("Invalid auth header, array_size==%d\n", array_size);
		return (false);
	}
	auth_type = mpack_expect_u8(reader);
	auth_token = mpack_expect_u32(reader);
	
	if (auth_token == CONFIG_AUTH_TOKEN 
		&& auth_type == CONFIG_AUTH_TOKEN_TYPE)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

static void udp_server_callback(const int sock, short int which, void *arg)
{
	struct sockaddr_in server_sin;
	socklen_t server_sz = sizeof(server_sin);
	struct sockaddr *addr = (struct sockaddr *) &server_sin;
	char readbuf[128];
	uint32_t read_data_size, array_size;
	mpack_reader_t reader;
	mpack_error_t error;
	uint8_t message_type;
	
	/* Recv the data, store the address of the sender in server_sin */
	if ((read_data_size = recvfrom(sock, &readbuf, sizeof(readbuf) - 1, 0, addr, &server_sz)) == -1) {
		perror("recvfrom()");
		event_loopbreak();
	}
	
	mpack_reader_init(&reader, &readbuf[0], sizeof(readbuf), read_data_size);
	array_size = mpack_expect_array_max(&reader, 128);
	
	DEBUG("udp data size %d, read %d array size\n", read_data_size, array_size);

	if (!is_client_authorized(&reader))
	{
		ERROR("Remote client is not authorized to send data to us\n");
		event_loopbreak();
		return;
	}
	
	message_type = mpack_expect_u8(&reader);
	
	if (!handle_udp_message(message_type, &reader))
	{
		ERROR("Can't handle UDP message type 0x%x\n", message_type);
		return;
	}
	
	if ((error = mpack_reader_destroy(&reader)) != mpack_ok)
	{
		ERROR("Error \"%s\" occured reading UDP data\n", mpack_error_to_string(error));
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