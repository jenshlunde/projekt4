#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main()
{
    char buffer[4];
    int fdLED = open("/sys/class/gpio/gpio20/value", O_RDWR);
    int fdtemp = open("/dev/i2c-1", O_RDONLY);  // Open i2c-dev on i2c bus 1
    int ret = ioctl(fdtemp, 0x0703, 0x48);
    // i2c-dev sys command call (0x0703) to set i2c address 0x48
    
    while (1)
    {
        read(fdtemp, buffer, 1);
        printf("The temperature is: %i\n", buffer[0]);
        if (buffer[0] >= 33) {
            write(fdLED, "1", 1);
            fprintf(stdout, "Overheating!!\n");}
        else
            write(fdLED, "0", 1);
        sleep(1);
    }
}
