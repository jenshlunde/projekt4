#include "i2cComms.hpp"

float readTemp(void)
{
  char buffer[2];
  float temp;
    
  int fd = open("/dev/i2c-1", O_RDONLY);
  int err = ioctl(fd, I2C_DEV_SYS, LM75_DEF_ADD); //Sets I2C address

  read(fd, buffer, 2);  
  if (buffer[1] == 1<<7)
  {
    temp = buffer[0] + 0.5;
  }
  else
  {
    temp = buffer[0];
  }

  if(temp > 100)
  {
    temp = temp - 255;
  }
  return temp;
}

void writeTempToTxt(float temp, writeToFile* file_name)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	std::string temp1 = std::to_string(temp);
	
	temp1.append(" - ").append(asctime(timeinfo));
  
  file_name->write(temp1);
}

void logTemp(writeToFile* file_name)
{
  float temp = readTemp();
  writeTempToTxt(temp,file_name);
}