#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

int main (int argc, char *argv[])
{
    int         sock;                   /* Socket descriptor */
    char *      echoString;             /* String to send to echo server */
    char        echoBuffer[RCVBUFSIZE]; /* Buffer for received string */
    int         echoStringLen;          /* Length of string to echo */
    int         bytesRcvd;              /* Bytes read in single recv() */
    int         i;                      /* counter for data-arguments */
    
    int 		recvMsgSize;

    parse_args (argc, argv);

    sock = CreateTCPClientSocket (argv_ip, argv_port);
        
    for (i = 0; i < argv_nrofdata; i++)
    {
        echoString = argv_data [i];
        echoStringLen = strlen (echoString);          /* Determine input length */

        delaying();
        
        // TODO: add code to send this string to the server; use send()
        send(sock, echoString, echoStringLen, MSG_CONFIRM);
        
        // TODO: add code to display the transmitted string in verbose mode; use info_s()
        info_s("Transmitted string", echoString);
        
        printf("Transmitted String = '%s' with len = %d\n", echoString, echoStringLen);
        
        // TODO: add code to receive & display the converted string from the server
        //       use recv() & printf()
        recvMsgSize = recv(sock, echoBuffer, RCVBUFSIZE-1, 0);
        echoBuffer[recvMsgSize] = '\0';
        printf("Received: ");
        int j;
        for(j = 0; j < recvMsgSize; j++)
        {
			printf("%C", echoBuffer[j]);
		}
    	printf("\n");
        
    }

    delaying ();

    close (sock);
    info ("close & exit");
    exit (0);
}
