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

  return temp;
}

void writeTemptToTxt(float temp, std::string file_name)
{
  writeToFile tempWFile(file_name);
  tempWFile.write(std::to_string(temp));
}

void logTemp()
{
  float temp = readTemp();

  std::string file_name = "temp.txt";

  writeToFile tempWFile(file_name);
  std::string tempStr;
    
  tempStr = std::to_string(temp);
  tempWFile.write(tempStr);
}