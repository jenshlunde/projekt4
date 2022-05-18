
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "i2cComms.hpp"

float readTempC() {
  float temp = 0;
  uint16_t t = read16(MCP9808_REG_AMBIENT_TEMP);

  if (t != 0xFFFF) {
    temp = t & 0x0FFF;
    temp /= 16.0;
    if (t & 0x1000)
      temp -= 256;
  }

  return temp;
}



int main()
{
    char buffer[2];
    int fd = open("/dev/i2c-1", O_RDONLY);
    //int fdLED = open("/sys/class/gpio/gpio26/value", O_RDWR);
    //int fdWEB = open("/www/pages/index.html", O_RDWR);
    int err = ioctl(fd, 0x0703, MCP9808_I2CADDR_DEFAULT); // i2cdev sys call (0x0703) to set I2C addr
    char string[25];
    float temp;
    while(1)
    {
        read(fd, buffer, 2);  
        printf("%f", buffer[0]);
        if (buffer[1] == 1<<7)
        {
            printf(".5");
            temp = buffer[0] + 0.5;
        }
        else
        {
            temp = buffer[0];
        }
        printf("\n\n");
        /*
        if (buffer[0] >= 33)
        {
            write(fdLED,"1",1);
        }
        else
        {
            write(fdLED,"0",1);
        }
        sprintf(string, "Temperaturen er %.1lf <br>", temp);
        //write(fdWEB, string, 25);
        */

        sleep(1);
    }
    close(fd);
    //close(fdLED);
    //close(fdWEB);
    return 0;
}