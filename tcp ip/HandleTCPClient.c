#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>

#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()

    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */
   
	memset(echoBuffer, 0, strlen(echoBuffer)); 
	
    /* Receive message from client */
    recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        // TODO: add code to print the received string; use printf()
        echoBuffer[recvMsgSize] = '\0';
        printf("Message received: ");
        int i;
        for(i = 0; i < recvMsgSize; i++)
        {
			printf("%C", echoBuffer[i]);
			
			 // TODO: add code to convert the upper/lower chars of the received string
			if(echoBuffer[i] >= 'a' && echoBuffer[i] <= 'z')
				echoBuffer[i] = toupper(echoBuffer[i]);
			else
				echoBuffer[i] = tolower(echoBuffer[i]);
		}
		printf("\n");   

        delaying ();
        
        /* Echo message back to client */
        if (send (clntSocket, echoBuffer, recvMsgSize, MSG_CONFIRM) != recvMsgSize)
        {
            DieWithError ("send() failed");
        }

        // TODO: add code to display the transmitted string in verbose mode; use info_s()
		
		info_s("Message transmitted: ", echoBuffer);
		memset(echoBuffer, 0, strlen(echoBuffer)); 
		
        // receive next string
        recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
        if (recvMsgSize < 0)
        {
            DieWithError ("recv() failed");
        }
        info_d ("Recv", recvMsgSize);
    }

    close (clntSocket);    /* Close client socket */
    info ("close");
}
