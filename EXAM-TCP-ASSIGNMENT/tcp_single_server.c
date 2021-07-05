/*			
TCP Single Client Server Program
Sagnik Mitra | 1811100002027
Computer Networks Lab Assignment
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 4455
extern int errno;

void hammingDist(char str1[], char str2[])
{
    int i = 0, count = 0;
    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    printf("%d\n", count);
}

int main()
{
    int sid, cid;
    struct sockaddr_in ser;
    struct sockaddr_in c;
    socklen_t addr_size;

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

    //waiting for connection request
    listen(sid, 5);
    puts(strerror(errno));

    //Accepting the Rrequest

    addr_size = sizeof(c);
    cid = accept(sid, (struct sockaddr *)&c, &addr_size);
    puts(strerror(errno));
    //}

    char a[10];
    read(cid, (void *)a, sizeof(a));
    puts(a);

    char b[10];
    read(cid, (void *)b, sizeof(b));
    puts(b);

    hammingDist(a, b);
    //Close the Socket

    close(cid);
    close(sid);
}
