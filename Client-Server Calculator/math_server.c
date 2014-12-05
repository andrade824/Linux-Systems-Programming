/*===================================================================================================
#   FILE:  math_server.c
#
#   DESCRIPTION:  Takes in a string over sockets that represents a mathematical operation, and returns
#                 the result back to the client.
#			
#        AUTHOR:  Devon Andrade, devon.andrade@oit.edu
#       VERSION:  1.0
#       CREATED:  6/8/2014
#===================================================================================================*/

#include "local_sock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signal_catcher(int);

int main()
{
	int orig_sock = 0;              // Original socket in server
	int new_sock = 0;               // New socket from connect

	socklen_t clnt_len;             // Length of client address
	struct sockaddr_in clnt_adr;    // Internet addr client
	struct sockaddr_in serv_adr;    // Internet addr server

    int len = 0;        
    int result = 0;
    int num1, num2;
    char op = '\0';
    char buffer[BUFSIZ];

    // Catch when child terminates
	if (signal(SIGCHLD , signal_catcher) == SIG_ERR)
	{
		perror("SIGCHLD");
		return 1;
	}

    // Create socket
	if((orig_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("generate error");
		return 2;
	}
    
    // Setup socket
	memset (&serv_adr, 0, sizeof(serv_adr));	/* Clear structure */
	serv_adr.sin_family = AF_INET;				/* Set address type */
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);	/* Any interface */
	serv_adr.sin_port = htons(PORT);			/* Use our fake port */

    // Bind to the socket
	if (bind (orig_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
	{
		perror("bind error");
		close(orig_sock);
		return 3;
	}

	/* Listen On The Socket for Clients */
	if (listen(orig_sock, 5) < 0) 
	{
		perror("listen error");
		close (orig_sock);
		return 4;
	}

    // Accept connection from the client
	do 
	{
		clnt_len = sizeof(clnt_adr);
		if ((new_sock = accept(orig_sock, (struct sockaddr *)&clnt_adr,
			(socklen_t *)&clnt_len)) < 0)
		{
			perror("accept error");
			close(orig_sock);
			return 5;
		}

		/* Generate a child Process */
		pid_t process;
		process = fork();  
		if (process == 0 )
		{
            int return_val = 0;

			/* Read The Socket */
			while ((len=read(new_sock, buf, BUFSIZ)) > 0)
			{
                if(buf[0] == '.')
                {
                    return_val = 1;
                    break;
                }

                char * token = strtok(buf, " ");
                num1 = atoi(token);
                
                token = strtok(NULL, " ");
                op = *(token);
                
                token = strtok(NULL, " ");
                num2 = atoi(token);
                
                // perform math based on operator
                switch(op)
                {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    result = num1 / num2;
                    break;
                }

                sprintf(buf, "%d", result);

                /* Write Changed Data Back Out on Socket */
                write(new_sock, buf, strlen(buf) + 1);
			}

			/* In The Child Process */
			close(new_sock);
			return return_val;
		}

		if( process > 0 )
		{	
			int status = 0;
			waitpid(process, &status, 0);
			
            /* In The Parent Process */
			close(new_sock);

            if(WIFEXITED(status) && WEXITSTATUS(status) == 1)
                break;
		}

	} while(1);

	return 0;
}

void signal_catcher(int the_sig)
{
	/* Reset The Signal */
	signal(the_sig, signal_catcher);

	/* Keep the zombies at bay */
	wait(0);
}
