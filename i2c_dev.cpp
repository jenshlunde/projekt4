
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "writeToFile.hpp"
#include <iostream>
#include <string>

int main()
{
    char buffer[2];
    std::string tempStr;
    float temp;
    writeToFile tempWFile("temp.txt");
    
    int fd = open("/dev/i2c-1", O_RDONLY);
    int err = ioctl(fd, 0x0703, 0x48); // i2cdev sys call (0x0703) to set I2C addr
    

    while(1)
    {
        read(fd, buffer, 2);  
        if (buffer[1] == 1<<7)
        {
            temp = buffer[0] + 0.5;
        }
        else
        {
            temp = buffer[0];
        }
        tempStr = std::to_string(temp);
        tempWFile.write(tempStr);

        sleep(1);
    }

    close(fd);    
    return 0;
}