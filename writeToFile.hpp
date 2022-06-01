#ifndef writeToFileDEF
#define writeToFileDEF

#include <fstream>


class writeToFile
{
private:
    std::ofstream file_;
public:
    writeToFile(std::string file_name);
    ~writeToFile();
    
    void write(std::string input);
};


#endif
