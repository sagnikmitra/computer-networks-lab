/*			
UDP Multi Client Server Program
Sagnik Mitra | 1811100002027
Computer Networks Lab Assignment
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#define PORT 6500
extern int errno;
int main()
{
	int sid;
	struct sockaddr_in ser;
	struct sockaddr_in c;
	socklen_t addr_size;
	sid = socket(AF_INET, SOCK_DGRAM, 0);

	//SOCKET CREATION

	puts(strerror(errno));

	memset(&ser, '\0', sizeof(ser));

	//ASSIGNING IP AND PORT
	ser.sin_family = AF_INET;
	ser.sin_port = htons(PORT);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");

	//BINDING SOCKET TO IP
	int val = -1;
	setsockopt(sid, SOL_SOCKET, SO_REUSEADDR, (void *)&val, sizeof(val));
	puts(strerror(errno));
	bind(sid, (struct sockaddr *)&ser, sizeof(ser));
	puts(strerror(errno));

	//WAITING FOR CONNECTION REQUEST

	addr_size = sizeof(c);

	char b[10];
	recvfrom(sid, b, sizeof(b), 0, (struct sockaddr *)&c, &addr_size);
	puts(b);

	//CLOSE THE SOCKET

	close(sid);
}
