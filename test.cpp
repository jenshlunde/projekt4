#include "i2cComms.hpp"
#include "writeToFile.hpp"

int main()
{
    writeToFile temperatureData("temperatureCold.txt");
    while(1)
    {   
        logTemp(&temperatureData);
        sleep(3);        
    }   

    return 0;
}