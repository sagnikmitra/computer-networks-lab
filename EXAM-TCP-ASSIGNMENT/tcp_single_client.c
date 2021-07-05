/*			
TCP Single Client Program
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
#define PORT 4455

//If the Program Shows any error, then it will show the output by using the errno variable
extern int errno;

int main()
{
    //Jekono
    int id;
    struct sockaddr_in ser;
    //
    id = socket(AF_INET, SOCK_STREAM, 0);

    puts(strerror(errno));

    memset(&ser, '\0', sizeof(ser));

    //ASSIGNING IP AND PORT
    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    //SENDING CONNECTION REQUEST
    connect(id, (struct sockaddr *)&ser, sizeof(ser));
    puts(strerror(errno));

    //WRITING STRING 1 TO THE SOCKET
    char a[10];
    strcpy(a, "Sagnik");
    printf("\nTo Server: %s\t", a);
    write(id, (void *)a, strlen(a) + 1);

    //WRITING STRING 2 TO THE SOCKET
    char b[10];
    strcpy(b, "SMitra");
    printf("\nTo Server: %s\t", b);
    write(id, (void *)b, strlen(b) + 1);

    //CLOSING THE SOCKET
    close(id);
}
