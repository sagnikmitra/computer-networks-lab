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

//Erro show korar jnno ekta variable
extern int errno;

//Let's say Sagnik and SMitra are two strings. Now, I have to convert SAgnik to SMitra, how many changes I need to make / substituion I need to make in the Sagnik Strings, so that I will reach to SMitra
//The minimum number of changes we need to do convert Sagnik to SMitra
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
    //sid is the server_id and cid is the client id
    int sid, cid;
    /* Structure describing an Internet socket address .*/
    struct sockaddr_in ser;
    /* Structure describing an Internet socket address for Client.  */
    struct sockaddr_in c;
    socklen_t addr_size;

    //SOCKET CREATION
    /* Create a new socket of type TYPE in domain DOMAIN, using
    protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
    Returns a file descriptor for the new socket, or -1 for errors.  */
    sid = socket(AF_INET, SOCK_STREAM, 0);
    /* Return a string describing the meaning of the `errno' code in ERRNUM.  */
    puts(strerror(errno));
    //For assigning to a block memory
    memset(&ser, '\0', sizeof(ser));

    //ASSIGNING IP AND PORT
    ser.sin_family = AF_INET;
    /* Port number. htons -> host to network short*/
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    //BINDING SOCKET TO IP
    int val = -1;
    /* Set socket FD's option OPTNAME at protocol level LEVEL
    to *OPTVAL (which is OPTLEN bytes long).
    Returns 0 on success, -1 for errors.  */
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
