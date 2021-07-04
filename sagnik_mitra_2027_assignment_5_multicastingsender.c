/*			
MultiCasting Sender Program
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
	int cid;
	struct sockaddr_in ser;

	//OPEN A SOCKET
	cid = socket(AF_INET, SOCK_DGRAM, 0);

	puts(strerror(errno));

	memset(&ser, '\0', sizeof(ser));

	//ASSIGNING IP AND PORT
	ser.sin_family = AF_INET;
	ser.sin_port = htons(PORT);
	ser.sin_addr.s_addr = inet_addr("230.1.1.1");

	//SENDING CONNECTION REQUEST

	//WRITING DATA TO THE SOCKET
	char a[10];
	strcpy(a, "hello");
	printf("\nTo Server: %s\t", a);
	sendto(cid, a, strlen(a) + 1, 0, (struct sockaddr *)&ser, sizeof(ser));
	//CLOSING THE SOCKET
	close(cid);
}
