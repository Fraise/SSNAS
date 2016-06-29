#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define SERIAL "0123456789ABCDEF"
#define PORT 12012

int main(void)
{
	SSL_library_init();			/* load encryption & hash algorithms for SSL */                
	SSL_load_error_strings();		/* load the error strings for good error reporting */
	OpenSSL_add_ssl_algorithms();	

	const SSL_METHOD* server_method = SSLv23_server_method();
	SSL_CTX* ctx = SSL_CTX_new(server_method);
	SSL* ssl;
	struct sockaddr_in server_sockaddr;
	int server_socket, client;
	uint sockaddr_len = sizeof(server_sockaddr);

	if (SSL_CTX_use_certificate_file(ctx, "myCert.pem", SSL_FILETYPE_PEM) <= 0)
	{
		fprintf(stderr, "Failed to load certificate.\n");
		return -1;
	}

	if (SSL_CTX_use_PrivateKey_file(ctx, "myKey.pem", SSL_FILETYPE_PEM) <= 0)
	{
		fprintf(stderr, "Failed to load certificate.\n");
		return -1;
	}

	if (!SSL_CTX_check_private_key(ctx))
	{
		fprintf(stderr, "Private key does not match the public certificate.\n");
		return -1;
	}

	ssl = SSL_new(ctx);

	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (server_socket < 0)
	{
		fprintf(stderr, "Failed to create socket.\n");
		return -1;
	}
	 
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sockaddr.sin_port = htons(PORT);
	 
	if (bind(server_socket, (struct sockaddr*)&server_sockaddr,sizeof(server_sockaddr)) < 0)
	{
		fprintf(stderr, "Failed to bind socket.\n");
		return -1;
	}
	 
	/* Receive a TCP connection. */
	if (listen(server_socket, 5) < 0)
	{
		fprintf(stderr, "Failed to listen to TCP connection.\n");
		return -1;
	}

	client = accept(server_socket, (struct sockaddr*)&server_sockaddr, &sockaddr_len);

	if (client < 0)
	{
		fprintf(stderr, "Failed to accept TCP connection.\n");
		return -1;
	}

	SSL_set_fd(ssl, client);

	if (SSL_accept(ssl) <= 0)
	{
		fprintf(stderr, "Failed to initiate SSL handshake.\n");
		return -1;
	}
	else
	{
		SSL_write(ssl, "Echo!\n", strlen("Echo!\n"));
	}

        SSL_free(ssl);
        close(client);

	return 0;
}
