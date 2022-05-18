#ifndef i2cCommsDEF
#define i2cCommsDEF

#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "writeToFile.hpp"
#include <iostream>
#include <string>

#define LM75_DEF_ADD 0x48
#define I2C_DEV_SYS 0x0703

float readTemp(void);
void writeTempToTxt(float, std::string);
void logTemp(void);


#endif