#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "ssl.h"

#define SERIAL "0123456789ABCDEF"
#define DEFAULT_PORT 12012

#define ERROR -1

int main(int argc, char* argv[])
{
	SSL_library_init();						//Load encryption & hash algorithms for SSL
	SSL_load_error_strings();					//Load the error strings for good error reporting
	OpenSSL_add_ssl_algorithms();	

	const SSL_METHOD* server_method = SSLv23_server_method();
	SSL_CTX* ctx = SSL_CTX_new(server_method);
	SSL* ssl;
	struct sockaddr_in server_sockaddr;
	int server_socket, client, opt, port = 0;
	uint sockaddr_len = sizeof(server_sockaddr);
	char r_buffer[32], w_buffer[32];

	if ((opt = getopt(argc, argv, "p:")) != -1)
	{
		switch (opt)
		{
			case 'p':
				port = atoi(optarg);
				break;
			case '?':
				if (optopt == 'p')
				{
					printf("No port specified, using port %d.\n", DEFAULT_PORT);
					port = DEFAULT_PORT;
				}
				break;
			default:
				break;
		}
	}

	if (port == 0)
	{
		printf("No port specified, using port %d.\n", DEFAULT_PORT);
		port = DEFAULT_PORT;
	}

	//Creating ssl context

	ssl = create_ssl_context(ctx);

	if (ssl == NULL)
	{
		fprintf(stderr, "Failed to create ssl context.\n");
		return ERROR;
	}

	//Creating server socket

	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (server_socket < 0)
	{
		fprintf(stderr, "Failed to create socket.\n");
		return ERROR;
	}
		 
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sockaddr.sin_port = htons(port);

	//Binding server socket
		 
	if (bind(server_socket, (struct sockaddr*)&server_sockaddr,sizeof(server_sockaddr)) < 0)
	{
		fprintf(stderr, "Failed to bind socket.\n");
		return ERROR;
	}

	if (listen(server_socket, 5) < 0)
	{
		fprintf(stderr, "Failed to listen to TCP connection.\n");
		return ERROR;
	}
		
	while (1)
	{
		client = accept(server_socket, (struct sockaddr*)&server_sockaddr, &sockaddr_len);

		if (client < 0)
		{
			fprintf(stderr, "Failed to accept TCP connection.\n");
			return ERROR;
		}

		//Creating SSL socket

		SSL_set_fd(ssl, client);

		if (SSL_accept(ssl) <= 0)
		{
			fprintf(stderr, "Failed to complete SSL handshake.\n");
			return ERROR;
		}
		else
		{
			SSL_read(ssl, r_buffer, 32);
			printf("Received : %s\n", r_buffer);
			strcpy(w_buffer, r_buffer);
			SSL_write(ssl, w_buffer, strlen(w_buffer));
		}

		close(client);
	}

	SSL_free(ssl);

	return 0;
}
