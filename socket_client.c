#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#define PORT 49152

typedef struct hostent hostent;
typedef union {
  uint32_t l;
  unsigned char c[4];
} EndianTest;

char* getIPByHostent(hostent* hostObj){
    char** pptr;
    char buf[1024];
    char* res = malloc(sizeof(char) * 1024);

    pptr = hostObj->h_addr_list;
    // for(pptr = hostObj->h_addr_list; *pptr != NULL; pptr++)
    // {
        // printf("IP Address: %s\n", inet_ntop(hostObj->h_addrtype, *pptr, buf, sizeof buf));
    // }
    inet_ntop(hostObj->h_addrtype, *pptr, buf, sizeof buf);
    strcpy(res, buf);
    printf("%s\n", res);
    return res;
}


int main(int argc, char const* argv[])
{
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	char* hello = "Hello from client";
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

    char* ip_addr = getIPByHostent(gethostbyname("assignment.jigentec.com"));
    
	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}
    free(ip_addr);

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

    char buffer[65535] = {0};
    uint32_t num = (uint32_t*)&buffer;

    valread = read(sock, buffer, 65535);

    uint32_t a = (uint32_t)buffer[0] << 32
    printf("0x%X\n", (uint32_t)buffer[0]);
    printf("0x%X\n", (uint32_t)buffer[1]);
    printf("0x%X\n", (uint32_t)buffer[2]);
    printf("0x%X\n", (uint32_t)buffer[3]);

	// closing the connected socket
	close(client_fd);
	return 0;
}

