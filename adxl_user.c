#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	int c;
	if (argc == 2)
	{
		int fd1, fd2, fd3;
		int ret_val;
		unsigned int buffer[2048];
		
		while((c = getopt(argc, argv, "xyz")) != -1)
		switch(c)
		{
			case 'x':
			{
				fd1=open("/dev/adxl_x", 0);
				printf("fdx = %d\n", fd1);
				
				if(fd1<0)
				{
					printf("adxl_x Open Failed\n");
					exit(-1);
				}
				
				ret_val=read(fd1,&buffer,4);
				if(ret_val>=0)
					printf("ADXL X Value: %d\n", buffer[0]);
				else
					printf("Device Read Failed\n");
					
				close(fd1);
			}
			break;
				
			case 'y':
			{
				fd2=open("/dev/adxl_y", 0);
				printf("fdy = %d\n", fd2);
				
				if(fd2<0)
				{
					printf("adxl_y Open Failed\n");
					exit(-1);
				}
				
				ret_val=read(fd2,&buffer,4);
				if(ret_val>=0)
					printf("ADXL Y Value: %d\n", buffer[1]);
				else
					printf("Device Read Failed\n");
					
				close(fd2);
			}
			break;
			
			case 'z':
			{
				fd3=open("/dev/adxl_z", 0);
				printf("fdz = %d\n", fd3);
				
				if(fd3<0)
				{
					printf("adxl_z Open Failed\n");
					exit(-1);
				}
				
				ret_val=read(fd3,&buffer,4);
				if(ret_val>=0)
					printf("ADXL Z Value: %d\n", buffer[2]);
				else
					printf("Device Read Failed\n");
				close(fd3);
			}
			break;
		
		}
	}
	else
		printf("Wrong number of arguments\n");
	return 0;
}
