#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <iostream>
#include "uart.h"

// Set to 1 to enable debugging mode
#define DEBUG 1

using namespace std;

int main(int argc, char *argv[])
{
    int fd, n, i;
    char buf[64] = "temp text";
    struct termios toptions;

    // Open serial port here
    fd = open("dev/ttyACM0", O_RDWR | O_NOCTTY);
    cout << "fd opened as " << fd << endl;

    // Wait for the arduino to reboot
    usleep(3500000);

    // Get current serial port settings
    tcgetattr(fd, &toptions);
    // Set 9600 baud both ways
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);
    // 8 bits, no parity bits, no stop bits
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // Canonical mode
    toptions.c_lflag |= ICANON;
    // commit the serial port settings
    tcsetattr(fd, TCSANOW, &toptions);

    // Send byte to trigger Arduino to send string back
    write(fd, "0", 1);
    // Receive string from Arduino
    n = read(fd, buf, 64);
    // insert terminating zero in the string
    buf[n] = 0;

    cout << n << " bytes read, buffer contains: " << buf << endl;

    if(DEBUG)
    {
        printf("Printing individual characters in buf as integers...\n\n");
        for(i=0; i<n; i++)
        {
        printf("Byte %i:%i, ",i+1, (int)buf[i]);
        }
        printf("\n");
    }
}