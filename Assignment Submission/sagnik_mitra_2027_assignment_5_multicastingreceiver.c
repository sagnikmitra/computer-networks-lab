/*			
MultiCasting Receiver Program
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
#define PORT 7777
extern int errno;
int main()
{
	int sid;
	struct sockaddr_in s, c;

	//OPEN A SOCKET
	sid = socket(AF_INET, SOCK_DGRAM, 0);

	puts(strerror(errno));

	memset(&s, '\0', sizeof(s));

	//ASSIGNING IP AND PORT
	s.sin_family = AF_INET;
	s.sin_port = htons(PORT);
	s.sin_addr.s_addr = htonl(INADDR_ANY);
	int val = -1;
	setsockopt(sid, SOL_SOCKET, SO_REUSEADDR, (void *)&val, sizeof(val));

	bind(sid, (struct sockaddr *)&s, sizeof(s));

	struct ip_mreq m;
	m.imr_multiaddr.s_addr = inet_addr("230.1.1.1");
	m.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(sid, IPPROTO_IP, IP_ADD_MEMBERSHIP, &m, sizeof(m));

	//SENDING CONNECTION REQUEST
	puts(strerror(errno));

	//WRITING DATA TO THE SOCKET
	char a[100];
	int l = sizeof(c);
	recvfrom(sid, a, sizeof(a), 0, (struct sockaddr *)&c, &l);
	//CLOSING THE SOCKET
	puts(a);
	close(sid);
}
