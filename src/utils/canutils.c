#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "canutils.h"

int getSocket(char * vcanInput) {
	int sockLocal;
	struct sockaddr_can addr;
	struct ifreq ifr;

    //Step 1 - Get the socket
	if ((sockLocal = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

    //Step 2 - Get interface index
	strcpy(ifr.ifr_name, vcanInput );
	ioctl(sockLocal, SIOCGIFINDEX, &ifr);

    //Step 3 - Bind socket to the interface
	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(sockLocal, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}
	return sockLocal;
}
