/*			
TCP Multiple Client Server Program
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
#include <pthread.h>
#define PORT 4455
extern int errno;

int sid;

void *task(void *arg)
{
	struct sockaddr_in c;
	socklen_t addr_size;
	//ACCEPTING THE REQUEST
	addr_size = sizeof(c);
	int cid = accept(sid, (struct sockaddr *)&c, &addr_size);
	puts(strerror(errno));
	char b[10];
	read(cid, (void *)b, sizeof(b));
	puts(b);
	close(cid);
}

int main()
{

	struct sockaddr_in ser;

	//SOCKET CREATION
	sid = socket(AF_INET, SOCK_STREAM, 0);

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
	listen(sid, 5);
	puts(strerror(errno));

	//THREAD CREATION

	pthread_t pt[5];

	for (int i = 0; i < 5; i++)
	{
		pthread_create(&pt[i], NULL, task, NULL);
	}
	for (int i = 0; i < 5; i++)
	{
		pthread_join(pt[i], NULL);
	}

	//CLOSE THE SOCKET
	close(sid);
}
