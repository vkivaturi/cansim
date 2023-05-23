
//Reference - https://github.com/craigpeacock/CAN-Examples/blob/master/cantransmit.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main(int argc, char **argv)
{
	int s; 
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Demo\r\n");

    //Step 1 - Get the socket
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

    //Step 2 - Get interface index
	strcpy(ifr.ifr_name, "vcan0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

    //Step 3 - Bind socket to the interface
	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

    //Step 4 - Create data frame that needs to be transimitted
	frame.can_id = 0x555;
    //Payload size
	frame.can_dlc = 5;
	sprintf(frame.data, "Hello");

    //Step 5 - Send data
	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		perror("Write");
		return 1;
	}

    //Step 6 - Close socket once data is sent
	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}