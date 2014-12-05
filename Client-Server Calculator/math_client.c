/*===================================================================================================
#   FILE:  math_client.c
#
#   DESCRIPTION:  Asks the user for a mathematical expression, performs the computation on a server
#                 and prints the results back to the user.
#			
#        AUTHOR:  Devon Andrade, devon.andrade@oit.edu
#       VERSION:  1.0
#       CREATED:  6/8/2014
#===================================================================================================*/

#include "local_sock.h"

int main (int argc, char *argv[])
{
	/* Variables */
	int orig_sock = 0;		/* Original socket in client */
	int len = 0;			/* Misc. counter */
	struct sockaddr_in serv_adr;	/* Internet addr of server */
	struct hostent *host;	/* The host (server) info */

	/* Check cmd line for host name */
	if (argc != 2)
	{
		fprintf (stderr, "Usage: %s <server name>\n", argv[0]);
		return 1;
	}

	/* Obtain host (server) information  */
	host = gethostbyname(argv[1]);
	if (host == (struct hostent *)NULL)
	{
		perror("gethostbyname");
		return 2;
	}

	/* Setup Socket */
	memset (&serv_adr, 0, sizeof( serv_adr));	/* Clear structure */
	serv_adr.sin_family = AF_INET;				/* Set address type */
	memcpy(&serv_adr.sin_addr, host->h_addr, host->h_length);
	serv_adr.sin_port = htons(PORT);			/* Use our fake port */

	/* Create Socket */
	if ((orig_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("generate error");
		return 3;
	}

	/* Connect To Server */
	if (connect(orig_sock,(struct sockaddr *)&serv_adr,
		sizeof(serv_adr)) < 0)
	{
		perror("connect error");
		return 4;
	}

	/* Get Input and send on socket */
	do
    {
        printf("Enter your expression:\n");
        fflush(stdout);
        write(fileno(stdout),"> ", 3);
        if ((len=read(fileno(stdin), buf, BUFSIZ)) > 0)
        {
            write(orig_sock, buf, len);
            if ((len=read(orig_sock, buf, len)) > 0 )
            {
                // result text
                fprintf(stdout, "Output: %s\n", buf);
                fflush(stdout);
            }
        }
    } while(buf[0] != 'q');

	close(orig_sock);
	return 0;
}

