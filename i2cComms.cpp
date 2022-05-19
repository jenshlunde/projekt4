#include "i2cComms.hpp"

float readTemp(void)
{
  char buffer[2];
  float temp;
    
  int fd = open("/dev/i2c-1", O_RDONLY);
  int err = ioctl(fd, I2C_DEV_SYS, LM75_DEF_ADD); //Sets I2C address

  //std::cout<<err<<std::endl;

  read(fd, buffer, 2);  
  if (buffer[1] == 1<<7)
  {
    temp = buffer[0] + 0.5;
    //std::cout<<"if"<<std::endl;
  }
  else
  {
    temp = buffer[0];
    //std::cout<<"else"<<std::endl;
  }
  //std::cout<<temp<<" i readTemp"<<std::endl;

  return temp;
}

void writeTempToTxt(float temp, writeToFile* file_name)
{
  //writeToFile tempWFile(file_name);
  file_name->write(std::to_string(temp));
  std::cout<<temp<<" i writeTempToTxt"<<std::endl; // til test
}
