#include "config.h"

extern struct event_base *evbase;

void http_server_process_request(struct evhttp_request *req, void *arg)
{
    struct stat st;
    int config_fd;
    struct evbuffer *buf = evbuffer_new();
    
    if (buf == NULL)
        return;
    
    DEBUG("got connection from %s:%d\n", req->remote_host, req->remote_port);
    
    evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "text/json");
    
    config_fd = open(CONFIG_PI_JSON_FILE, O_RDONLY);
    if (config_fd < 0)
    {
        ERROR("config file read error %s\n",strerror(errno));
        evbuffer_add_printf(buf, "{\"error\":\"config file read error %s\"}\n", strerror(errno));
        goto err;
    }    
    if (fstat(config_fd, &st) < 0)
    {
        ERROR("config file stat error %s\n",strerror(errno));
        evbuffer_add_printf(buf, "{\"error\":\"config file stat failed %s\"}\n", strerror(errno));
        goto err;
    }

    evbuffer_add_file(buf, config_fd, 0, st.st_size);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    
err:
    evhttp_send_error(req, 500, "Internal server error\n");
}

int http_server_register(struct event_base *evbase)
{
    struct evhttp *httpd = NULL;
    httpd = evhttp_new(evbase);
    
    if (httpd == NULL)
    {
        ERROR("error: failed to initialize built-in httpd\n");
        return -1;
    }
    
    
    if (evhttp_bind_socket(httpd, "0.0.0.0", CONFIG_PI_PORT) != 0)
    {
        ERROR("error: can't listen on 0:%d\n", CONFIG_PI_PORT);
        return -1;
    }
    else
    {
        INFO("http server started on 0.0.0.0:%d\n", CONFIG_PI_PORT);
    }	
    evhttp_set_gencb(httpd, http_server_process_request, NULL);
    
    return 0;
}