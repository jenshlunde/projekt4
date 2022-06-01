#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "writeToFile.hpp"

#define LM75_DEF_ADD 0x48
#define I2C_DEV_SYS 0x0703

float readTemp(void);
void writeTempToTxt(float, writeToFile*);
void logTemp(writeToFile*);
