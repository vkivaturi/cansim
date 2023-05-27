/*
Purpose - Simulate a network of devices communicating through virtual CAN interfaces.
Environment is standard Linux with SocketCAN libraries
*/
#include <stdio.h>
#include <stdlib.h>

#include "../utils/cansendreceive.h"

int main(int argc, char **argv)
{
   int i = receiveCANMessage("vcan0");
}