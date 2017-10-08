/*
 ============================================================================
 Name        : miscroEmuGUI.c
 Author      : Roman A. Paramonov
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


#include "../../miscroF411/Inc/gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int fd; /* Файловый дескриптор для порта */
char buf[512];/*размер зависит от размера строки принимаемых данных*/
int outa=0;
int iIn;
char rxbuf[512];

Host2DevCmd	cmd;
InputsData	inputs;

int main(void)
{
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC); /*'open_port()' - Открывает последовательный порт */
	if (fd == -1){
		printf("error port\n");
		perror("open_port: Unable to open /dev/ttyUSBn - ");
		return 0;
	}
	else{
		printf("fd = %d\n", fd);
		struct termios options;
		memset(&options, 0, sizeof(options));
		tcgetattr(fd, &options);
		if(tcgetattr (fd, &options) != 0){
			printf("error %d from tcgetattr\n", errno);
		    return -1;
		 }

		cfsetispeed(&options, B460800);
		cfsetospeed(&options, B460800);

		options.c_oflag &= ~OPOST;


		tcsetattr(fd, TCSANOW, &options);

		options.c_cflag = (options.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
		// disable IGNBRK for mismatched speed tests; otherwise receive break
		// as \000 chars
		options.c_iflag &= ~IGNBRK;         // disable break processing
		options.c_lflag = 0;                // no signaling chars, no echo,
		                                    // no canonical processing
		options.c_oflag = 0;                // no remapping, no delays
		options.c_cc[VMIN]  = sizeof(InputsData);           // read doesn't block
		options.c_cc[VTIME] = 0;            // 0.5 seconds read timeout

		options.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

		options.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
		                                        // enable reading
		options.c_cflag &= ~(PARENB | PARODD);      // shut off parity
		//options.c_cflag |= parity;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CRTSCTS;

		if(tcsetattr (fd, TCSANOW, &options) != 0){
		    printf("error %d from tcsetattr\n", errno);
		    return -1;
		}
	}

	drawPanel();

	//wrap_st7735FillRect(100, 100, 20, 20, LCD_BLUE);
	//wrap_st7735FillRect(70, 70, 20, 20, LCD_RED);


	cmd.cmd_type = TYPE_FILL_RECT;
	cmd.flags = 15;
	cmd.fillrect.x = 20;
	cmd.fillrect.y = 20;
	cmd.fillrect.width = 40;
	cmd.fillrect.height = 40;
	cmd.fillrect.color	=	0xFFFF;
	//iIn = write(fd, &cmd, sizeof(cmd));
	uint32_t n;
    //n = read(fd, &inputs, sizeof(inputs));
    printf("trace report: %d %d\n", sizeof(Host2DevCmd), sizeof(CmdType));
	printf("send %d bytes\n receive %d bytes\n", iIn, n);
	return EXIT_SUCCESS;


}
