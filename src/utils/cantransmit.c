
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

#include "canutils.h"

int main(int argc, char **argv)
{
	printf("CAN Sockets Demo\r\n");

	//Step 1 - Setup a socket and bind it to the vcan interface
	char canInput[] = "vcan0";
	int s = getSocket(canInput); 
	
    //Step 2 - Create data frame that needs to be transimitted
	struct can_frame frame;
	frame.can_id = 0x555;
    //Payload size
	frame.can_dlc = 5;
	sprintf(frame.data, "Hello");

    //Step 3 - Send data
	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		perror("Write");
		return 1;
	}

    //Step 4 - Close socket once data is sent
	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}