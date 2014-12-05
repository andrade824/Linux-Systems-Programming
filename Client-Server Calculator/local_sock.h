#ifndef LOCAL_SOCK_H
#define LOCAL_SOCK_H

/* Includes */
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>

/* Defines */
#define _GNU_SOURCE

/* Global Constants */
const  int  PORT=2002;		/* Arbitrary port programmer chooses */
static char buf[BUFSIZ];	/* Buffer for messages */
#endif

