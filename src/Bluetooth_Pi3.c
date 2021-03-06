/*
 * Author: MSOE Team Xi Senior Design 2017
 * Date: 12/2017
 * Description: This file contains all the function prototypes for the Bluetooth Connection on the Pi0W side
 */

#include "Bluetooth_Pi3.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

static char* BluetoothAddr = "B8:27:EB:EF:25:F4";
#define CHANNEL_NUMBER 1
static int sock;

/*
 * Description:
 * @param:
 * @return:
 */
void getBluetoothData(packet_t* receivedPacket){
  memset(receivedPacket,0,sizeof(recievedPacket));
  int bytesRead = 0;
  while(bytesRead < sizeof(recievedPacket)){
    bytesRead += read(sock, receivedPacket,sizeof(recievedPacket));
  }
}

/*
 * Description: Sends data across the Bluetooth connection to the Pi3
 * @param: packetToSend
 * @return:NULL
 */
void sendBluetoothData(packet_t* packetToSend){
  write(sock, packetToSend, sizeof(packetToSend));
}

/*
 * Description: Initializes the connection from the Pi0W to the Pi3
 * @param: NULL
 * @return: NULL
 */
void initBluetooth_Pi3(){
  int d;
  struct sockaddr_rc laddr, raddr;
  struct hci_dev_info di;

  if(hci_devinfo(0, &di) < 0) {
      perror("HCI device info failed");
      exit(1);
  }

  //printf("Local device %s\n", batostr(&di.bdaddr));

  //laddr.rc_family = AF_BLUETOOTH;
  //laddr.rc_bdaddr = di.bdaddr;
  //laddr.rc_channel = 1;

  raddr.rc_family = AF_BLUETOOTH;
  str2ba(BluetoothAddr,&raddr.rc_bdaddr);
  raddr.rc_channel = CHANNEL_NUMBER;

  // Create a Socket to Bind with RFCOMM
  if( (sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0) {
    perror("socket");
  }

  // Connect to the Bluetooth Address using RFCOMM
  if(connect(sock, (struct sockaddr *)&raddr, sizeof(raddr)) < 0) {
     perror("connect");
     exit(1);
  }
}

/*
 * Description: Disconnects Bluetooth, closes socket, and frees receivedAudio
 * @param: NULL
 * @return: NULL
 */
void closeBluetooth_Pi0W(){
	close(sock);
}
